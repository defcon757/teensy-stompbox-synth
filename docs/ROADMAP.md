# Development Roadmap

## Phase 1 — Hardware foundation (complete when you have parts)

- [ ] Set buck converter output to exactly 5V (verify with multimeter before connecting Teensy)
- [ ] Stack Audio Shield onto Teensy 4.1
- [ ] Flash Teensy with Audio Shield passthrough test sketch
- [ ] Confirm audio in → audio out works over USB serial monitor
- [ ] Build JFET + TL072 input buffer on prototype PCB
- [ ] Test buffer output with multimeter or audio interface
- [ ] Wire 3PDT footswitch (bypass + effect send/return)
- [ ] Wire input and output 1/4" jacks
- [ ] Confirm full signal path: guitar in → buffer → Audio Shield → output jack

## Phase 2 — Core firmware (v0.1)

- [ ] Implement pitch detection using `AudioAnalyzeNoteFrequency` (Teensy Audio Library built-in)
- [ ] Implement basic wavetable synthesis using `AudioSynthWavetable`
- [ ] Load a flute wavetable `.wav` from microSD
- [ ] Synthesize a tone at the detected pitch
- [ ] Implement ADSR envelope follower tracking guitar amplitude
- [ ] Wet/dry mix using `AudioMixer4`
- [ ] Confirm flute sound tracks guitar pitch in real time

## Phase 3 — Controls (v0.2)

- [ ] Wire all 3 KY-040 encoders with debounce
- [ ] Encoder 1: cycle through synth voices (flute, FM, sine, sawtooth...)
- [ ] Encoder 2: octave shift (−2 to +2)
- [ ] Encoder 3: wet/dry mix (0.0 to 1.0)
- [ ] Wire 3 SPST buttons with INPUT_PULLUP + Bounce2 debounce
- [ ] Buttons: save/recall preset A, B, C from microSD

## Phase 4 — Display + LEDs (v0.3)

- [ ] Wire OLED SSD1306 on I2C (pins 18/19)
- [ ] Display: detected note name (C4, G#3, etc.)
- [ ] Display: current synth mode
- [ ] Display: octave offset and wet/dry value
- [ ] Wire WS2812B LED strip (pin 6, 300Ω series)
- [ ] LED color = musical note (C=red, D=orange, E=yellow... chromatic wheel)
- [ ] LED brightness = signal amplitude

## Phase 5 — Presets + polish (v0.4)

- [ ] Preset system: save encoder positions + voice to microSD JSON
- [ ] Preset recall on button press
- [ ] Startup splash screen on OLED
- [ ] Tuner mode: hold button 1 + button 2 simultaneously to enter chromatic tuner view
- [ ] OLED shows cent deviation from nearest note in tuner mode

## Phase 6 — Enclosure (v0.5)

- [ ] Design enclosure in Fusion 360 / Tinkercad / OpenSCAD
- [ ] Minimum wall thickness 3mm, top face 4mm+
- [ ] 12mm hole for 3PDT footswitch
- [ ] 9.5mm holes for 1/4" jacks
- [ ] 7mm holes for encoder shafts
- [ ] Mounting posts for PCB (M3 standoffs)
- [ ] Vent slots near Teensy
- [ ] Line interior with copper tape connected to GND (RF shielding)
- [ ] Print, test fit, iterate

## Phase 7 — Stretch goals (v1.0+)

- [ ] Polyphonic mode: detect up to 2 simultaneous pitches (experimental)
- [ ] MIDI output: send detected pitch as MIDI note over USB
- [ ] More wavetable voices: violin, cello, oboe, pad
- [ ] Reverb / delay send using Teensy Audio Library effects
- [ ] Expression pedal input (TRS jack) for real-time parameter sweep
- [ ] Custom PCB designed in KiCad (replace prototype boards)
- [ ] Publish KiCad files + Gerbers in `hardware/pcb/`

---

## Current status

**Phase 1 in progress** — parts ordered, enclosure being designed.
