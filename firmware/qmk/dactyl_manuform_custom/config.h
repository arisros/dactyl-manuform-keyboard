#pragma once
#include "config_common.h"

/* USB Device Descriptor */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER "ArisJirat"
#define PRODUCT      "Dactyl Manuform Custom"

/* Matrix Size
 * TODO: Confirm exact row/col count from physical schematic
 * Left hand: 6 rows × 6 cols + thumb cluster
 * Right hand: mirror of left
 */
#define MATRIX_ROWS 12       // 6 rows left + 6 rows right
#define MATRIX_COLS 6        // max columns

/* Pin Assignment — Pro Micro
 * TODO: Confirm actual pins from physical wiring/schematic
 * These are placeholder values based on common Dactyl Manuform builds
 */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B6, D4 }

/* Diode Direction
 * TODO: Confirm from physical diode orientation
 * COL2ROW = current flows column → row
 * ROW2COL = current flows row → column
 */
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard */
#define USE_SERIAL

/* TODO: Confirm TRRS data pin (D0 or D1) from physical wiring */
#define SOFT_SERIAL_PIN D0

/* Master side: right hand is connected to USB
 * Alternative: use EE_HANDS (requires flashing each side separately with different flags)
 */
#define MASTER_RIGHT

/* Misc */
#define DEBOUNCE 5
#define SPLIT_USB_DETECT
