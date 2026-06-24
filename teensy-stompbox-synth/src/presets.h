// presets.h / presets.cpp
// Save and load presets to microSD as simple CSV files
// Preset 0 = PRESET_A.TXT, Preset 1 = PRESET_B.TXT, Preset 2 = PRESET_C.TXT

#pragma once

void loadPreset(int slot);
void savePreset(int slot, int voiceIndex, int octave, float wetDry);
