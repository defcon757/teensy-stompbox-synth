# Build Order

Work through these phases in sequence. Each phase ends with a test — don't move on until it passes.

---

## Phase 1 — Power

1. Wire 9V DC jack to buck converter IN
2. Adjust buck converter trim pot until multimeter reads exactly 5.0V on OUT terminals
3. Do not connect Teensy yet — verify voltage first
4. Connect buck OUT+ to Teensy VUSB, buck OUT− to GND
5. **Test:** Teensy LED blinks on power-up ✓

---

## Phase 2 — Audio passthrough

1. Stack Audio Shield onto Teensy 4.1
2. Connect Teensy to computer via USB
3. Flash the passthrough test sketch (File → Examples → Audio → PassThroughStereo)
4. Plug guitar into Audio Shield LINE IN (3.5mm for testing), headphones to LINE OUT
5. **Test:** Guitar signal passes through cleanly with no distortion ✓

---

## Phase 3 — Input buffer

1. Socket TL072 in DIP-8 socket
2. Build buffer circuit on prototype PCB:
   - 2N5457 JFET: drain → 10kΩ → 9V, source → 1kΩ → GND
   - TL072: IN+ from JFET source, 100kΩ feedback (pins 1–2), V+ to 9V, V− to GND
   - 100nF decoupling cap on TL072 V+
3. Connect input jack TIP → JFET gate (shielded cable)
4. **Test:** Plug guitar into jack, probe TL072 pin 1 with audio interface or oscilloscope — clean signal ✓

---

## Phase 4 — 3PDT bypass

1. Wire 3PDT per WIRING.md lug diagram
2. Wire input jack and output jack
3. Wire TL072 output to 3PDT send
4. Wire 3PDT return to Audio Shield LINE IN (3.5mm → TRS adapter or direct solder)
5. **Test:**
   - Effect OFF: guitar signal passes from input jack directly to output jack (dry bypass) ✓
   - Effect ON: signal routes through buffer → Audio Shield ✓

---

## Phase 5 — OLED display

1. Wire SSD1306 OLED: VCC → 3.3V, GND, SDA → pin 18, SCL → pin 19
2. Flash OLED test sketch (Adafruit SSD1306 → ssd1306_128x64_i2c example)
3. **Test:** "Hello World" displays on OLED ✓

---

## Phase 6 — Encoders

1. Wire Encoder 1 (pins 0/1/2), Encoder 2 (pins 3/4/5), Encoder 3 (pins 7/8/9)
2. All encoder VCCs → 3.3V, all GNDs → GND
3. Flash encoder test sketch to print values to serial monitor
4. **Test:** Turning each encoder prints incrementing/decrementing values ✓
5. **Test:** Pressing each encoder SW button prints button press ✓

---

## Phase 7 — Buttons

1. Wire buttons to pins 10, 11, 12 with one leg to GND
2. Use INPUT_PULLUP in code
3. **Test:** Each button press registers in serial monitor ✓

---

## Phase 8 — WS2812B LEDs

1. Wire LED strip: 5V → Teensy 5V, GND, DIN → 300Ω → pin 6
2. Add 100µF cap across 5V/GND at the strip
3. Flash FastLED test sketch (rainbow example)
4. **Test:** LED strip cycles through colors ✓

---

## Phase 9 — Pitch detection + synthesis

1. Open `src/main.ino`
2. Format microSD as FAT32, copy a flute wavetable `.wav` to root
3. Flash main firmware
4. **Test:** Play single notes on guitar — OLED displays detected note name ✓
5. **Test:** Synthesized flute tone audible at output jack, tracking pitch ✓
6. **Test:** Turning Encoder 3 blends wet/dry mix ✓

---

## Phase 10 — Enclosure

1. Print enclosure (PETG recommended for durability)
2. Check all hole sizes before assembly:
   - 3PDT footswitch: 12mm
   - 1/4" jacks: 9.5mm
   - Encoder shafts: 7mm
   - DC jack: 12mm
3. Line inside walls with copper tape, connect tape to GND
4. Mount PCB on M3 standoffs
5. Leave gap or vent slots near Teensy
6. **Final test:** full signal path with enclosure closed ✓

---

## Troubleshooting

**Hum or buzz:** Check that all GNDs share a single common point. Ensure input cable to JFET gate is shielded. Check copper tape grounding in enclosure.

**No detected pitch:** Confirm signal level into Audio Shield LINE IN is within range (not clipping). Adjust TL072 gain if needed.

**LEDs flickering:** Add or increase the 100µF cap at the LED strip power input. Check the 300Ω series resistor on DIN.

**OLED not showing anything:** Check I2C address (try 0x3D if 0x3C fails). Confirm SDA/SCL not swapped.
