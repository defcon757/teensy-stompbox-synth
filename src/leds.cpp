// leds.cpp

#include "leds.h"

CRGB leds[NUM_LEDS];

// Maps note name (C, C#, D ... B) to a hue on the chromatic color wheel
// 12 notes evenly spaced across 0–255 hue
static uint8_t noteToHue(String note) {
  const char* names[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
  for (int i = 0; i < 12; i++) {
    if (note.startsWith(names[i])) return (uint8_t)(i * 21);  // 255/12 ≈ 21
  }
  return 0;
}

void ledsInit() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
  FastLED.clear();
  FastLED.show();
}

void ledsUpdate(String note, int memUsage) {
  if (note == "--") {
    // No signal — all off
    FastLED.clear();
    FastLED.show();
    return;
  }

  uint8_t hue = noteToHue(note);
  // Brightness scales with memory usage as a proxy for signal activity
  uint8_t brightness = constrain(map(memUsage, 0, 64, 30, 220), 30, 220);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 220, brightness);
  }
  FastLED.show();
}
