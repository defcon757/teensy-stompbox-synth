// synth_engine.h
// Handles voice selection and pitch setting for the synthesis layer

#pragma once
#include <Audio.h>

extern AudioSynthWavetable wavetable;

// Voice indices
#define VOICE_FLUTE  0
#define VOICE_FM     1
#define VOICE_SINE   2
#define VOICE_SAW    3

void synthEngineInit(int voiceIndex);
void synthEngineSetPitch(float hz);
const char* synthEngineName(int voiceIndex);
