// Teensy Stompbox Synthesizer
// Main entry point
// Board: Teensy 4.1 | USB: Serial | CPU: 600MHz

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <FastLED.h>
#include <Encoder.h>
#include <Bounce2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "pitch_detector.h"
#include "synth_engine.h"
#include "envelope.h"
#include "controls.h"
#include "display.h"
#include "leds.h"
#include "presets.h"

// ── Audio objects ────────────────────────────────────────────
AudioInputI2S            audioIn;
AudioAnalyzeNoteFrequency pitchDetect;
AudioSynthWavetable      wavetable;
AudioMixer4              wetDryMix;
AudioOutputI2S           audioOut;
AudioControlSGTL5000     codec;

// Connections
AudioConnection patchIn(audioIn, 0, pitchDetect, 0);     // guitar → pitch detector
AudioConnection patchDry(audioIn, 0, wetDryMix, 0);      // guitar → dry channel
AudioConnection patchWet(wavetable, 0, wetDryMix, 1);    // synth → wet channel
AudioConnection patchOutL(wetDryMix, 0, audioOut, 0);
AudioConnection patchOutR(wetDryMix, 0, audioOut, 1);

// ── Encoders (CLK, DT) ──────────────────────────────────────
Encoder encSynthType(0, 1);
Encoder encOctave(3, 4);
Encoder encWetDry(7, 8);

// ── Buttons (SW pins + 3 stomp buttons) ─────────────────────
Bounce btnSynthSW  = Bounce();
Bounce btnOctaveSW = Bounce();
Bounce btnWetDrySW = Bounce();
Bounce btnPresetA  = Bounce();
Bounce btnPresetB  = Bounce();
Bounce btnPresetC  = Bounce();

// ── State ────────────────────────────────────────────────────
int    synthTypeIndex = 0;         // 0=flute, 1=FM, 2=sine, 3=saw
int    octaveShift    = 0;         // -2 to +2
float  wetDryRatio    = 0.5f;      // 0.0 dry … 1.0 wet
float  detectedHz     = 0.0f;
String detectedNote   = "--";

// ── Setup ────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  AudioMemory(64);

  // Codec init
  codec.enable();
  codec.inputSelect(AUDIO_INPUT_LINEIN);
  codec.volume(0.8);
  codec.lineInLevel(5);

  // Pitch detector threshold (0.0–1.0, lower = more sensitive)
  pitchDetect.begin(0.15);

  // Mix defaults
  wetDryMix.gain(0, 1.0f - wetDryRatio);   // dry
  wetDryMix.gain(1, wetDryRatio);           // wet

  // Buttons
  btnSynthSW.attach(2,  INPUT_PULLUP);  btnSynthSW.interval(10);
  btnOctaveSW.attach(5, INPUT_PULLUP);  btnOctaveSW.interval(10);
  btnWetDrySW.attach(9, INPUT_PULLUP);  btnWetDrySW.interval(10);
  btnPresetA.attach(10, INPUT_PULLUP);  btnPresetA.interval(10);
  btnPresetB.attach(11, INPUT_PULLUP);  btnPresetB.interval(10);
  btnPresetC.attach(12, INPUT_PULLUP);  btnPresetC.interval(10);

  // Subsystems
  displayInit();
  ledsInit();
  sdInit();
  synthEngineInit(synthTypeIndex);

  displaySplash();
  delay(1000);
}

// ── Loop ─────────────────────────────────────────────────────
void loop() {
  // Read controls
  readEncoders();
  readButtons();

  // Pitch detection
  if (pitchDetect.available()) {
    detectedHz  = pitchDetect.read();
    detectedNote = hzToNoteName(detectedHz);
    float targetHz = applyOctaveShift(detectedHz, octaveShift);
    synthEngineSetPitch(targetHz);
  }

  // Update wet/dry mix
  wetDryMix.gain(0, 1.0f - wetDryRatio);
  wetDryMix.gain(1, wetDryRatio);

  // Update display + LEDs (~30fps)
  static elapsedMillis displayTimer;
  if (displayTimer > 33) {
    displayUpdate(detectedNote, synthTypeIndex, octaveShift, wetDryRatio);
    ledsUpdate(detectedNote, AudioMemoryUsageMax());
    displayTimer = 0;
  }
}

// ── Helpers ──────────────────────────────────────────────────
void readEncoders() {
  static long lastSynthType = 0, lastOctave = 0, lastWetDry = 0;
  const char* synthNames[] = {"Flute", "FM", "Sine", "Saw"};

  long s = encSynthType.read() / 4;
  if (s != lastSynthType) {
    synthTypeIndex = constrain(synthTypeIndex + (int)(s - lastSynthType), 0, 3);
    lastSynthType = s;
    synthEngineInit(synthTypeIndex);
  }

  long o = encOctave.read() / 4;
  if (o != lastOctave) {
    octaveShift = constrain(octaveShift + (int)(o - lastOctave), -2, 2);
    lastOctave = o;
  }

  long w = encWetDry.read() / 4;
  if (w != lastWetDry) {
    wetDryRatio = constrain(wetDryRatio + (w - lastWetDry) * 0.05f, 0.0f, 1.0f);
    lastWetDry = w;
  }
}

void readButtons() {
  btnSynthSW.update();
  btnOctaveSW.update();
  btnWetDrySW.update();
  btnPresetA.update();
  btnPresetB.update();
  btnPresetC.update();

  if (btnOctaveSW.fell())  octaveShift = 0;           // reset octave on click
  if (btnWetDrySW.fell())  wetDryRatio = 0.5f;        // reset mix on click
  if (btnPresetA.fell())   loadPreset(0);
  if (btnPresetB.fell())   loadPreset(1);
  if (btnPresetC.fell())   loadPreset(2);
}

String hzToNoteName(float hz) {
  if (hz < 20.0f) return "--";
  const char* notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
  int midi = (int)round(12.0f * log2f(hz / 440.0f) + 69.0f);
  int octave = midi / 12 - 1;
  return String(notes[midi % 12]) + String(octave);
}

float applyOctaveShift(float hz, int shift) {
  return hz * powf(2.0f, (float)shift);
}

void sdInit() {
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card not found — wavetable loading disabled");
  }
}
