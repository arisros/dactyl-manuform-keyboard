#include QMK_KEYBOARD_H

/*
 * Keymap exported from QMK Configurator (setup.json)
 * Keyboard: handwired/dactyl_manuform/4x6
 * Keymap:   arisjirat
 *
 * Layer key positions (52 keys per layer):
 *
 * Left Hand (rows 0-3, 6 cols each + 2 thumb)   Right Hand (mirror)
 * ┌─────┬───┬───┬───┬───┬───┐                   ┌───┬───┬───┬───┬───┬─────┐
 * │L00  │L01│L02│L03│L04│L05│                   │R00│R01│R02│R03│R04│R05  │
 * ├─────┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼─────┤
 * │L10  │L11│L12│L13│L14│L15│                   │R10│R11│R12│R13│R14│R15  │
 * ├─────┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼─────┤
 * │L20  │L21│L22│L23│L24│L25│                   │R20│R21│R22│R23│R24│R25  │
 * ├─────┼───┼───┼───┼───┼───┤                   ├───┼───┼───┼───┼───┼─────┤
 * │L30  │L31│L32│L33│L34│L35│                   │R30│R31│R32│R33│R34│R35  │
 * └─────┴───┴───┴───┴───┴───┘                   └───┴───┴───┴───┴───┴─────┘
 *                     ┌─────┬─────┐ ┌─────┬─────┐
 *                     │L40  │L41  │ │R40  │R41  │
 *                     └─────┴─────┘ └─────┴─────┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Layer 0 — Base (QWERTY)
[0] = LAYOUT(
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_LGUI, KC_SPC,    KC_ENT,  KC_HOME, KC_LSFT, KC_ESC,  KC_BSPC, KC_RSFT,
                                        MO(1),   KC_LALT,   KC_RALT, MO(2)
),

// Layer 1 — Numpad + Media (hold MO(1) / left thumb inner)
[1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC,   KC_RBRC, KC_P7,   KC_P8,   KC_P9,   QK_BOOT, KC_PLUS,
    KC_TRNS, KC_NO,   KC_LCTL, KC_LALT, KC_LGUI, KC_LPRN,   KC_RPRN, KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_PIPE,
    KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_TRNS,   KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_EQL,  KC_UNDS,
    KC_VOLD, KC_VOLU, KC_TRNS, KC_P0,   KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
),

// Layer 2 — Navigation + Media (hold MO(2) / right thumb inner)
[2] = LAYOUT(
    KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC,   KC_RBRC, KC_TRNS, KC_NUM,  KC_INS,  KC_SCRL, KC_MUTE,
    KC_TRNS, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_LPRN,   KC_RPRN, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
    KC_VOLD, KC_VOLU, KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
)

};
