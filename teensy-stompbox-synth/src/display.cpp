// display.cpp

#include "display.h"
#include "synth_engine.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void displayInit() {
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 not found — check wiring (pins 18/19, address 0x3C)");
    return;
  }
  display.clearDisplay();
  display.display();
}

void displaySplash() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(4, 10);
  display.print("StompSynth");
  display.setTextSize(1);
  display.setCursor(20, 42);
  display.print("Teensy 4.1 + Audio");
  display.display();
}

void displayUpdate(String note, int voiceIndex, int octave, float wetDry) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Large note name top-left
  display.setTextSize(3);
  display.setCursor(0, 4);
  display.print(note);

  // Voice name top-right
  display.setTextSize(1);
  display.setCursor(76, 4);
  display.print(synthEngineName(voiceIndex));

  // Octave row
  display.setCursor(76, 20);
  display.print("Oct: ");
  if (octave > 0) display.print("+");
  display.print(octave);

  // Wet/dry bar
  display.setCursor(0, 50);
  display.print("Wet");
  int barW = (int)(wetDry * 80);
  display.fillRect(26, 52, barW, 8, SSD1306_WHITE);
  display.drawRect(26, 52, 80, 8, SSD1306_WHITE);

  // Memory usage hint (bottom right)
  display.setCursor(108, 57);
  display.print(AudioMemoryUsageMax());

  display.display();
}
