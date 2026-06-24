// presets.cpp

#include "presets.h"
#include <SD.h>
#include <Arduino.h>

// These are the live state variables declared in main.ino
extern int   synthTypeIndex;
extern int   octaveShift;
extern float wetDryRatio;

static const char* slotName(int slot) {
  switch (slot) {
    case 0: return "PRESET_A.TXT";
    case 1: return "PRESET_B.TXT";
    case 2: return "PRESET_C.TXT";
    default: return nullptr;
  }
}

void savePreset(int slot, int voiceIndex, int octave, float wetDry) {
  const char* fname = slotName(slot);
  if (!fname) return;
  if (SD.exists(fname)) SD.remove(fname);
  File f = SD.open(fname, FILE_WRITE);
  if (!f) { Serial.println("Save failed"); return; }
  f.print(voiceIndex); f.print(",");
  f.print(octave);     f.print(",");
  f.println(wetDry, 3);
  f.close();
  Serial.printf("Saved preset %d\n", slot);
}

void loadPreset(int slot) {
  const char* fname = slotName(slot);
  if (!fname) return;
  if (!SD.exists(fname)) { Serial.println("No preset saved"); return; }
  File f = SD.open(fname, FILE_READ);
  if (!f) return;
  String line = f.readStringUntil('\n');
  f.close();

  int v, o; float w;
  sscanf(line.c_str(), "%d,%d,%f", &v, &o, &w);
  synthTypeIndex = constrain(v, 0, 3);
  octaveShift    = constrain(o, -2, 2);
  wetDryRatio    = constrain(w, 0.0f, 1.0f);
  Serial.printf("Loaded preset %d: voice=%d oct=%d wet=%.2f\n", slot, v, o, w);
}
