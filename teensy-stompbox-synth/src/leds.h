// leds.h / leds.cpp
// WS2812B RGB LEDs on Teensy pin 6 via FastLED
// Color encodes musical note (chromatic wheel), brightness = signal level

#pragma once
#include <FastLED.h>

#define LED_PIN    6
#define NUM_LEDS   5
#define LED_TYPE   WS2812B
#define COLOR_ORDER GRB

extern CRGB leds[NUM_LEDS];

void ledsInit();
void ledsUpdate(String note, int memUsage);
