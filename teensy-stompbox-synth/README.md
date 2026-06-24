# Teensy Stompbox Synthesizer

A guitar-input pitch-tracking synthesizer pedal built around the **Teensy 4.1** and **Teensy Audio Shield Rev D**. Play into it and it tracks your pitch in real time, synthesizing a flute (or any wavetable/FM voice) at the detected frequency — with true bypass, OLED display, RGB LEDs, and three rotary encoders for parameter control.

---

## Features

- Real-time monophonic pitch detection via autocorrelation
- Wavetable synthesis (flute default) with swappable voices from microSD
- FM synthesis mode as an alternative voice
- ADSR envelope following the guitar's dynamics
- True bypass via 3PDT footswitch
- Wet/dry mix, octave shift, and synth type selection via rotary encoders
- SSD1306 OLED display showing current note, mode, and octave
- WS2812B RGB LED strip for visual feedback (active note color)
- 3 SPST stomp buttons for preset A/B/C switching
- 9V pedalboard power (buck-regulated to 5V internally)
- 3D-printed enclosure

---

## Hardware

| Component | Part | Purpose |
|---|---|---|
| MCU | Teensy 4.1 | Main processing (600MHz ARM M7) |
| Audio codec | Teensy Audio Shield Rev D | ADC/DAC, I2S bus |
| Input buffer | 2N5457 JFET + TL072 | High-Z guitar input |
| Display | SSD1306 0.96" OLED | Note / mode display |
| LEDs | WS2812B (5-LED strip) | Note color feedback |
| Encoders | KY-040 ×3 | Synth type, octave, wet/dry |
| Buttons | SPST momentary ×3 | Preset A/B/C |
| Bypass | 3PDT footswitch | True bypass switching |
| Power | DROK buck converter | 9V → 5V |
| Storage | 8GB microSD | Wavetable samples |
| Jacks | 1/4" mono ×2 | Guitar in / out |
| Enclosure | 3D printed (PLA/PETG) | Custom housing |

Full bill of materials with prices: [`docs/BOM.md`](docs/BOM.md)

---

## Repository Structure

```
teensy-stompbox-synth/
├── src/
│   ├── main.ino                  # Arduino sketch entry point
│   ├── pitch_detector.h/cpp      # Autocorrelation pitch detection
│   ├── synth_engine.h/cpp        # Wavetable + FM synthesis
│   ├── envelope.h/cpp            # ADSR envelope follower
│   ├── controls.h/cpp            # Encoders, buttons, debounce
│   ├── display.h/cpp             # OLED SSD1306 UI
│   ├── leds.h/cpp                # WS2812B FastLED control
│   └── presets.h/cpp             # Preset save/load (SD card)
├── hardware/
│   ├── schematics/
│   │   └── stompbox_schematic.pdf   # Full wiring schematic
│   ├── enclosure/
│   │   └── README.md                # 3D print notes + dimensions
├── docs/
│   ├── BOM.md                    # Bill of materials
│   ├── WIRING.md                 # Pin-by-pin wiring reference
│   ├── BUILD_ORDER.md            # Step-by-step build guide
│   └── ROADMAP.md                # Development roadmap
├── assets/
│   └── wavetables/               # Place .wav wavetable files here
│       └── README.md
├── lib/
│   └── README.md                 # Third-party library notes
└── README.md
```

---

## Dependencies

Install these via the Arduino Library Manager or download manually:

| Library | Purpose |
|---|---|
| [Teensy Audio Library](https://github.com/PaulStoffregen/Audio) | Core DSP — bundled with Teensyduino |
| [FastLED](https://github.com/FastLED/FastLED) | WS2812B LED control |
| [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) | OLED display |
| [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) | Graphics primitives for OLED |
| [Encoder](https://github.com/PaulStoffregen/Encoder) | KY-040 rotary encoder reading |
| [Bounce2](https://github.com/thomasfredericks/Bounce2) | Button debouncing |

---

## Quick Start

1. Install [Teensyduino](https://www.pjrc.com/teensy/td_download.html)
2. Clone this repo
3. Install all libraries listed above
4. Open `src/main.ino` in Arduino IDE
5. Set board to **Teensy 4.1**, USB type to **Serial**, CPU speed to **600MHz**
6. Flash and test audio passthrough before wiring the full circuit

Full build guide: [`docs/BUILD_ORDER.md`](docs/BUILD_ORDER.md)

---

## Wiring Summary

See [`docs/WIRING.md`](docs/WIRING.md) for the full pin reference.

Quick encoder map:

| Encoder | Parameter | CLK | DT | SW |
|---|---|---|---|---|
| 1 | Synth type | Pin 0 | Pin 1 | Pin 2 |
| 2 | Octave | Pin 3 | Pin 4 | Pin 5 |
| 3 | Wet/dry mix | Pin 7 | Pin 8 | Pin 9 |

---

## Roadmap

See [`docs/ROADMAP.md`](docs/ROADMAP.md) for the full development plan.

---

## License

[Business Source License 1.1](LICENSE)

Free to use, modify, and share for personal and non-commercial purposes. Commercial use is restricted until 2029-01-01, after which this project converts to the MIT License. See `LICENSE` for full terms.

To use this commercially before that date, contact the author for a separate license.
