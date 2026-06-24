# Wavetables

Place your `.wav` wavetable files here. They are excluded from git.

## Getting wavetables

- Free single-cycle waveforms: https://www.adventurekid.se/akrt/waveforms/adventure-kid-waveforms/
- Free wavetables: https://waveeditonline.com/
- Flute samples for conversion: https://freesound.org (search "flute single note")

## Format requirements

- Single-cycle or short looped samples
- 16-bit PCM WAV
- 44100 Hz sample rate
- Mono

## Conversion to Teensy wavetable format

Use the AudioSynthWavetable tool included with Teensyduino:
`File → Examples → Audio → WaveformWavetable`

This converts a `.wav` to a C header file you can include in `synth_engine.cpp`.
