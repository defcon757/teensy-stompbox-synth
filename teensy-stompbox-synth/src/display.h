// display.h + display.cpp (combined for clarity)
// OLED SSD1306 UI via I2C on Teensy pins 18 (SDA) / 19 (SCL)

#pragma once
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

extern Adafruit_SSD1306 display;

void displayInit();
void displaySplash();
void displayUpdate(String note, int voiceIndex, int octave, float wetDry);
