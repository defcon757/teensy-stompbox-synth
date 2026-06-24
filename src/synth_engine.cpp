// synth_engine.cpp

#include "synth_engine.h"
#include <SD.h>

static int currentVoice = VOICE_FLUTE;
static float currentHz  = 440.0f;

const char* synthEngineName(int voiceIndex) {
  switch (voiceIndex) {
    case VOICE_FLUTE: return "Flute";
    case VOICE_FM:    return "FM";
    case VOICE_SINE:  return "Sine";
    case VOICE_SAW:   return "Saw";
    default:          return "???";
  }
}

void synthEngineInit(int voiceIndex) {
  currentVoice = voiceIndex;

  // TODO Phase 2: load wavetable from SD for VOICE_FLUTE
  // Example:
  //   AudioSynthWavetable::instrument_data inst;
  //   // load from "flute.wav" on SD and parse into inst
  //   wavetable.setInstrument(inst);

  // For now, use a basic sine approximation at current pitch
  synthEngineSetPitch(currentHz);
}

void synthEngineSetPitch(float hz) {
  if (hz < 20.0f || hz > 8000.0f) return;
  currentHz = hz;

  // AudioSynthWavetable uses MIDI note numbers
  // Convert Hz to MIDI: midi = 69 + 12*log2(hz/440)
  float midi = 69.0f + 12.0f * log2f(hz / 440.0f);
  int midiNote = constrain((int)round(midi), 0, 127);

  wavetable.playNote(midiNote, 100);  // note, velocity 0-127
}
