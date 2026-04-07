#pragma once
#include "config_common.h"

/* USB Device Descriptor */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER "ArisJirat"
#define PRODUCT      "Dactyl Manuform Custom"

/* Matrix Size
 * Layout: handwired/dactyl_manuform/4x6
 * 4 finger rows × 6 cols per side + 2 thumb keys per side = 26 keys × 2 sides = 52 total
 * Physical matrix uses 6 rows per side (rows 4-5 = thumb cluster positions)
 */
#define MATRIX_ROWS 12       // 6 rows left + 6 rows right
#define MATRIX_COLS 6

/* Pin Assignment — Pro Micro (ATmega32U4)
 * Based on: Official QMK handwired/dactyl_manuform/4x6 default config
 * ⚠️ Adjust these if your physical wiring differs — use multimeter to verify
 */
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { F5, F4, B5, B4, D7, C6 }

/* Diode Direction — confirmed COL2ROW from schematic */
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard */
#define USE_SERIAL

/* Serial pin — official QMK 4x6 default
 * ⚠️ Adjust if your TRRS data wire connects to a different pin (D0 or D1)
 */
#define SOFT_SERIAL_PIN D2

/* Master side: right hand is connected to USB
 * Alternative: use EE_HANDS (requires flashing each side separately with different flags)
 */
#define MASTER_RIGHT

/* Misc */
#define DEBOUNCE 5
#define SPLIT_USB_DETECT
