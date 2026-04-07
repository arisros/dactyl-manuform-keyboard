#pragma once
#include "quantum.h"

/*
 * LAYOUT macro — maps physical key positions to matrix positions
 * Keyboard: handwired/dactyl_manuform/4x6
 * Total keys: 52 (26 per side: 4 rows × 6 cols + 2 thumb keys)
 *
 * Physical layout (top view):
 *
 * Left Hand                              Right Hand
 * ┌───┬───┬───┬───┬───┬───┐             ┌───┬───┬───┬───┬───┬───┐
 * │L00│L01│L02│L03│L04│L05│             │R00│R01│R02│R03│R04│R05│  row 0
 * ├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
 * │L10│L11│L12│L13│L14│L15│             │R10│R11│R12│R13│R14│R15│  row 1
 * ├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
 * │L20│L21│L22│L23│L24│L25│             │R20│R21│R22│R23│R24│R25│  row 2
 * ├───┼───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┼───┤
 * │L30│L31│L32│L33│L34│L35│             │R30│R31│R32│R33│R34│R35│  row 3
 * └───┴───┴───┴───┴───┴───┘             └───┴───┴───┴───┴───┴───┘
 *                     ┌───┬───┐   ┌───┬───┐
 *                     │L40│L41│   │R40│R41│  thumb
 *                     └───┴───┘   └───┴───┘
 *
 * Matrix rows 0-5  = left hand  (row pins: F6, F7, B1, B3, B2, B6)
 * Matrix rows 6-11 = right hand
 * Matrix cols 0-5  = both hands (col pins: F5, F4, B5, B4, D7, C6)
 *
 * ⚠️ Pin assignment uses official QMK 4x6 default — adjust if custom wiring differs
 */
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,  R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,  R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,  R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35,  R30, R31, R32, R33, R34, R35, \
                        L40, L41,  R40, R41                        \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { L30, L31, L32, L33, L34, L35 }, \
    { L40, L41, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, R33, R34, R35 }, \
    { R40, R41, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
