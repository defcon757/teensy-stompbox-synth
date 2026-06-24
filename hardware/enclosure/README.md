# Enclosure

3D printed — design in Fusion 360, Tinkercad, or OpenSCAD.

## Hole sizes

| Component | Hole diameter |
|---|---|
| 3PDT footswitch | 12mm |
| 1/4" mono jack | 9.5mm |
| KY-040 encoder shaft | 7mm |
| 5.5mm DC barrel jack | 12mm |

## Dimensions (approximate — measure your PCB layout first)

- Recommended: ~120mm × 70mm × 50mm (similar to a 1590BB pedal enclosure)
- Top face thickness: 4mm minimum (footswitch stress)
- Side wall thickness: 3mm minimum

## Print settings

- Material: PETG (better impact resistance than PLA for a pedal)
- Layer height: 0.2mm
- Infill: 30%+
- Support: needed for jack and switch holes if printing face-down

## RF shielding

Line the inside of the enclosure with copper tape. Connect the tape to the circuit GND with a short wire. This reduces RF interference and hum — important since PLA/PETG offers no inherent shielding unlike aluminum enclosures.

## PCB mounting

Use M3 brass standoffs (10mm height) to mount the PCB off the enclosure floor. Leave at least 5mm clearance above the Teensy for airflow.
