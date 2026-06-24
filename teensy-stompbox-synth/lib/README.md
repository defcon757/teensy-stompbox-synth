# Libraries

Install all of these before building. Use Arduino Library Manager (Sketch → Include Library → Manage Libraries) except where noted.

| Library | Install via | Search term |
|---|---|---|
| Teensy Audio Library | Bundled with Teensyduino | (automatic) |
| FastLED | Library Manager | `FastLED` |
| Adafruit SSD1306 | Library Manager | `Adafruit SSD1306` |
| Adafruit GFX | Library Manager | `Adafruit GFX` (dependency of SSD1306) |
| Encoder | Library Manager | `Encoder` by Paul Stoffregen |
| Bounce2 | Library Manager | `Bounce2` |

## Wavetable files

Place `.wav` wavetable files in `assets/wavetables/` locally. They are excluded from git via `.gitignore` due to size.

Free flute wavetables: https://www.adventurekid.se/akrt/waveforms/adventure-kid-waveforms/

The Teensy Audio Library includes a wavetable conversion tool at:
`File → Examples → Audio → WaveformWavetable`
