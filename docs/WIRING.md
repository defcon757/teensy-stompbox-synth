# Wiring Reference

## Power

| From | To | Notes |
|---|---|---|
| 9V DC jack + | Buck IN+ | |
| 9V DC jack − | Buck IN− | |
| Buck OUT+ | Teensy VUSB | Set to 5V before connecting |
| Buck OUT− | Common GND | |
| Teensy 3.3V | OLED VCC, encoder VCCs | |
| Teensy 5V | WS2812B 5V | |
| Common GND | All component GNDs | One shared ground point |

## Input buffer

### 2N5457 JFET (TO-92 — flat face forward: G, S, D left to right)
| Pin | Connection |
|---|---|
| GATE | Input jack TIP (shielded cable) |
| DRAIN | 9V via 10kΩ resistor |
| SOURCE | GND via 1kΩ resistor; buffered signal taken here |

### TL072 op-amp (DIP-8)
| Pin | Connection |
|---|---|
| 1 (OUT A) | To 3PDT Pole 2 top lug |
| 2 (IN− A) | Feedback: 100kΩ to pin 1 |
| 3 (IN+ A) | JFET SOURCE |
| 4 (V−) | GND |
| 8 (V+) | 9V |
| — | 100nF cap between pin 8 and GND |

## 3PDT footswitch (9 lugs, 3×3 grid)

```
        Pole 1          Pole 2          Pole 3
Top:    Input jack TIP  Input jack TIP  LED anode → 4.7kΩ → 5V
Mid:    Output jack TIP TL072 OUT       LED cathode → GND
Bot:    Output jack TIP Audio Shield IN (unused)
```

Effect ON: Guitar → TL072 → Audio Shield → processed → output jack
Effect OFF: Guitar → directly to output jack (true bypass)

## Teensy 4.1 pin assignments

| Pin | Function |
|---|---|
| 0 | Encoder 1 CLK (synth type) |
| 1 | Encoder 1 DT |
| 2 | Encoder 1 SW |
| 3 | Encoder 2 CLK (octave) |
| 4 | Encoder 2 DT |
| 5 | Encoder 2 SW |
| 6 | WS2812B DIN (via 300Ω) |
| 7 | Encoder 3 CLK (wet/dry) |
| 8 | Encoder 3 DT |
| 9 | Encoder 3 SW |
| 10 | Button 1 (preset A) |
| 11 | Button 2 (preset B) |
| 12 | Button 3 (preset C) |
| 18 | OLED SDA (I2C) |
| 19 | OLED SCL (I2C) |
| VUSB | 5V from buck converter |
| 3.3V | Encoder VCCs, OLED VCC |
| 5V | WS2812B 5V |
| GND | Common ground |

## Audio Shield connections

| Terminal | Connection |
|---|---|
| LINE IN L | From 3PDT Pole 2 bottom lug |
| LINE IN GND | GND |
| LINE OUT L | 10µF cap (DC block) → Output jack TIP |
| LINE OUT GND | Output jack SLEEVE |

## KY-040 encoders (all three identical wiring pattern)

| KY-040 pin | Connection |
|---|---|
| VCC | Teensy 3.3V |
| GND | GND |
| CLK | Teensy pin (see table above) |
| DT | Teensy pin |
| SW | Teensy pin |

Use `INPUT_PULLUP` on all CLK, DT, SW pins. Use the `Encoder` library by Paul Stoffregen.

## SPST stomp buttons

One leg → Teensy pin (10, 11, or 12). Other leg → GND.
Use `INPUT_PULLUP` in code. Use Bounce2 library for debounce (10ms interval).

## OLED SSD1306

| OLED pin | Connection |
|---|---|
| VCC | Teensy 3.3V |
| GND | GND |
| SDA | Teensy pin 18 |
| SCL | Teensy pin 19 |

I2C address: `0x3C`. Library: Adafruit SSD1306 + Adafruit GFX.

## WS2812B LED strip

| LED terminal | Connection |
|---|---|
| 5V | Teensy 5V (or buck 5V directly) |
| GND | GND |
| DIN | 300–500Ω resistor → Teensy pin 6 |

Add 100µF electrolytic capacitor across 5V and GND at the strip. Library: FastLED, `#define LED_PIN 6`, `#define NUM_LEDS 5`.

## Output jack

| Terminal | Connection |
|---|---|
| TIP | Audio Shield LINE OUT L via 10µF electrolytic cap |
| SLEEVE | GND |

Use shielded cable for this run.
