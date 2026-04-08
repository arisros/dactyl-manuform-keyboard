# Dactyl Manuform 5x6 — Wiring & Matrix Reference

## Hardware

| Component       | Spec                          |
|-----------------|-------------------------------|
| Keyboard        | Handwired Dactyl Manuform 5x6 |
| MCU             | ATmega32U4 (Pro Micro)        |
| Bootloader      | Caterina                      |
| Diode direction | COL2ROW                       |
| Split protocol  | Serial (half-duplex)          |
| USB master      | Left side (MASTER_LEFT)       |
| USB VID/PID     | 0x444D / 0x3536               |

## Matrix Pins

### Left Side (master)

| Row | Pin | Physical keys              |
|-----|-----|----------------------------|
| 0   | D4  | ` 1 2 3 4 5 (number)       |
| 1   | C6  | TAB Q W E R T              |
| 2   | D7  | LSFT A S D F G             |
| 3   | E6  | LCTL Z X C V B             |
| 4   | B4  | [ ] GUI SPC (thumb inner)  |
| 5   | B5  | MO(1) LALT LSFT ESC (thumb)|

| Col | Pin | Position (left→right) |
|-----|-----|-----------------------|
| 0   | F4  | 1st (leftmost)        |
| 1   | F5  | 2nd                   |
| 2   | F6  | 3rd                   |
| 3   | F7  | 4th                   |
| 4   | B1  | 5th                   |
| 5   | B2  | 6th (rightmost)       |

### Right Side (slave)

Same row pins as left. Columns are **mirrored** (reversed order):

| Col | Pin | Position (left→right) |
|-----|-----|-----------------------|
| 0   | B2  | 1st (leftmost)        |
| 1   | B1  | 2nd                   |
| 2   | F7  | 3rd                   |
| 3   | F6  | 4th                   |
| 4   | F5  | 5th                   |
| 5   | F4  | 6th (rightmost)       |

### Serial Communication

| Setting | Value |
|---------|-------|
| Pin     | D0    |
| Type    | Half-duplex serial |
| Cable   | TRRS (4-pole 3.5mm) |

## Flash Procedure (Caterina bootloader)

Both sides use the same `.hex` file.

```
1. CABUT USB
2. TAHAN RST pin ke GND
3. COLOK USB (sambil tahan RST)
4. LEPAS RST → bootloader active ~8 detik
5. avrdude -p atmega32u4 -c avr109 -P /dev/cu.usbmodemXXXXXX \
     -b 57600 -D -U flash:w:firmware.hex:i -F
```

Flash left first, then right. Connect USB to left + TRRS between halves.

## QMK Configuration

**Keyboard definition:** `handwired/dactyl_manuform/5x6`  
**Keymap:** `arisjirat_56`  
**Layout macro:** `LAYOUT_5x6`

Key files:
- `~/qmk_firmware/keyboards/handwired/dactyl_manuform/5x6/keyboard.json` — pin config
- `~/setup/keyboard/arisjirat_56.json` — QMK Configurator export (keymap source)

Compile:
```bash
qmk compile arisjirat_56.json
```

## Discovery Notes

- Official 4x6 default pins are completely wrong for this build
- Physical wiring was reverse-engineered using custom pin scanner firmware
- Left and right sides have mirrored column wiring (common in handwired splits)
- Keyboard originally worked as 4x6 but is actually 5x6 (4 alpha rows + 2 thumb rows per side)
- Serial pin D0 confirmed working (D2 did not work)
