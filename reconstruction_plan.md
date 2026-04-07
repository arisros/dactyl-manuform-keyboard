# 🎹 QMK Dactyl Manuform — Reconstruction Plan

> **Tujuan:** Mereconstruct keymap dari firmware yang ada, rebuild project QMK dari nol, dan mengubah konfigurasi master dari kiri ke kanan.

---

## 📋 Overview

| Item          | Detail                                 |
| ------------- | -------------------------------------- |
| Keyboard      | Dactyl Manuform (split)                |
| MCU           | Pro Micro / Elite-C (ATmega32U4)       |
| Firmware      | QMK                                    |
| Koneksi Split | TRRS                                   |
| Target Master | Kanan (`MASTER_RIGHT` atau `EE_HANDS`) |

---

## FASE 1 — Reverse Keymap dari Firmware yang Ada

### 1.1 Install Tools

```bash
# Install QMK CLI
pip install qmk
qmk setup

# macOS: install hidapi untuk HID listen
brew install hidapi
```

### 1.2 Observasi Key secara Manual

Cara paling reliable tanpa source code:

```bash
# Gunakan keyboard tester online
# https://www.keyboardtester.com/

# Buat spreadsheet, tekan tiap key, catat outputnya
# Tandai per posisi fisik (baris × kolom)
```

### 1.3 Baca Matrix dari Skema Fisik

Dari foto skema:

- **Left hand:** ~6 kolom × 6 baris + thumb cluster
- **Right hand:** mirror dari kiri
- **Warna label** (kuning/merah/biru/hitam) = penanda layer atau finger assignment

> ⚠️ Konfirmasi jumlah baris × kolom yang tepat sebelum lanjut ke Fase 2.

---

## FASE 2 — Struktur Project QMK

### 2.1 Struktur Folder

```
qmk_firmware/
└── keyboards/
    └── handwired/
        └── dactyl_manuform_custom/
            ├── dactyl_manuform_custom.h
            ├── dactyl_manuform_custom.c
            ├── config.h
            ├── info.json
            └── keymaps/
                └── default/
                    ├── keymap.c
                    └── config.h
```

### 2.2 Buat Project Baru via CLI

```bash
qmk new-keyboard
# Ikuti prompt:
#   keyboard name  : handwired/dactyl_manuform_custom
#   microcontroller: atmega32u4
#   layout         : handwired
```

---

## FASE 3 — File Konfigurasi

### 3.1 `config.h` (keyboard root)

```c
#pragma once
#include "config_common.h"

/* USB Device Descriptor */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER "Custom"
#define PRODUCT      "Dactyl Manuform"

/* Matrix — sesuaikan dengan skema */
#define MATRIX_ROWS 12       // 6 baris kiri + 6 baris kanan
#define MATRIX_COLS 6        // maksimum kolom

/* Pin Assignment Pro Micro — sesuaikan dari skema */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B6, D4 }
#define DIODE_DIRECTION COL2ROW   // konfirmasi dari orientasi dioda fisik

/* Split Keyboard */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D0        // pin TRRS data, biasanya D0 atau D1

// ===== PILIH SALAH SATU =====
#define MASTER_RIGHT              // Opsi A: master tetap di kanan
// #define EE_HANDS               // Opsi B: master ditentukan saat flash

/* Lainnya */
#define DEBOUNCE 5
#define SPLIT_USB_DETECT
```

### 3.2 `info.json`

```json
{
  "keyboard_name": "Dactyl Manuform Custom",
  "maintainer": "you",
  "usb": {
    "vid": "0xFEED",
    "pid": "0x0000",
    "device_version": "0.0.1"
  },
  "matrix_pins": {
    "rows": ["B0", "B1", "B2", "B3", "B4", "B5"],
    "cols": ["F4", "F5", "F6", "F7", "B6", "D4"]
  },
  "diode_direction": "COL2ROW",
  "split": { "enabled": true },
  "layouts": {
    "LAYOUT": { "layout": [] }
  }
}
```

---

## FASE 4 — Template Keymap

### 4.1 Layout Visual

```
Left Hand                          Right Hand
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │         │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│TAB│ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │ \ │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ESC│ A │ S │ D │ F │ G │         │ H │ J │ K │ L │ ; │ ' │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│SFT│ Z │ X │ C │ V │ B │         │ N │ M │ , │ . │ / │SFT│
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│CTL│GUI│ALT│ [ │ ] │   │         │   │ ← │ ↓ │ ↑ │ → │CTL│
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
                    ┌───┬───┐ ┌───┬───┐
                    │ENT│SPC│ │BSP│DEL│
                    ├───┼───┤ ├───┼───┤
                    │LOW│   │ │   │RAI│
                    └───┴───┘ └───┴───┘
```

### 4.2 `keymap.c`

```c
#include QMK_KEYBOARD_H

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    // Left hand
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LBRC, KC_RBRC,
                                        KC_ENT,  KC_SPC,
                                        LOWER,   KC_NO,
    // Right hand
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
    KC_BSPC, KC_DEL,
    KC_NO,   RAISE
),

[_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                        _______, _______,
                                        _______, _______,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, KC_F12,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______,
    _______, _______,
    _______, _______
),

[_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                        _______, _______,
                                        _______, _______,
    _______, _______, _______, _______, _______, _______,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
             _______, _______, _______, _______, _______,
    _______, _______,
    _______, _______
),

[_ADJUST] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,
                                        _______, _______,
                                        _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______,
    _______, _______,
    _______, _______
)

};

// Auto-generate ADJUST layer saat LOWER + RAISE aktif bersamaan
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
```

---

## FASE 5 — MASTER_RIGHT vs EE_HANDS

### Perbandingan

| Metode         | Kelebihan                                             | Kekurangan                                   |
| -------------- | ----------------------------------------------------- | -------------------------------------------- |
| `MASTER_RIGHT` | Simple, tidak perlu flash ulang jika tidak ganti sisi | Master hardcoded, tidak fleksibel            |
| `EE_HANDS`     | Bisa ganti master kapan saja                          | Perlu flash **dua kali** dengan flag berbeda |

### Cara Flash dengan EE_HANDS

```bash
# 1. Flash sisi KANAN dulu (sambungkan kanan ke PC)
qmk flash -kb handwired/dactyl_manuform_custom \
           -km default \
           -e SETTING_EE_HANDS=right

# 2. Cabut, sambungkan sisi KIRI
qmk flash -kb handwired/dactyl_manuform_custom \
           -km default \
           -e SETTING_EE_HANDS=left
```

### Cara Flash dengan MASTER_RIGHT

```bash
# Flash firmware yang sama ke kedua sisi
qmk flash -kb handwired/dactyl_manuform_custom -km default
# Ulangi untuk sisi satunya — tidak ada perbedaan flag
```

---

## FASE 6 — Checklist Flashing Aman ✅

```bash
# 1. Cek environment QMK
qmk doctor

# 2. Compile dulu, jangan langsung flash
qmk compile -kb handwired/dactyl_manuform_custom -km default

# 3. Cek output binary
ls .build/
# Harus ada file .hex atau .bin

# 4. Flash dengan konfirmasi
qmk flash -kb handwired/dactyl_manuform_custom -km default
# Tekan tombol Reset pada Pro Micro saat diminta

# 5. Ulangi untuk sisi kedua
```

> ⚠️ **PENTING:** Jangan colok atau cabut kabel TRRS saat keyboard dalam keadaan menyala (USB tersambung). Selalu matikan dulu (cabut USB) sebelum menyambung/melepas TRRS.

---

## FASE 7 — Debugging Matrix

### Aktifkan Debug Mode

Tambahkan di `keymaps/default/config.h`:

```c
#pragma once
#define DEBUG_MATRIX_SCAN_RATE
```

### Monitor via QMK Console

```bash
# Install dependency
pip install pyusb

# Jalankan console — tekan tombol dan lihat output posisi matrix
qmk console

# Contoh output:
# r:0 c:2 → baris 0, kolom 2 aktif
```

### Key Tidak Respon?

```c
// Tambahkan di config.h untuk skip pin yang tidak terpakai
#define MATRIX_MASKED

// Atau cek: apakah DIODE_DIRECTION sudah benar?
// COL2ROW  → arus dari kolom ke baris
// ROW2COL  → arus dari baris ke kolom
```

---

## 📌 Checklist Hal yang Perlu Dikonfirmasi

- [ ] Jumlah baris × kolom yang tepat (misal 5×6 atau 6×6)
- [ ] Pin assignment aktual dari skema fisik
- [ ] Arah dioda (`COL2ROW` atau `ROW2COL`)
- [ ] Pin TRRS data (`D0` atau `D1`)
- [ ] Pilihan metode master: `MASTER_RIGHT` atau `EE_HANDS`
- [ ] Apakah ada encoder/rotary knob?
- [ ] Apakah ada RGB/underglow?

---

## 📚 Referensi

| Resource            | Link                                                                                |
| ------------------- | ----------------------------------------------------------------------------------- |
| QMK Docs            | https://docs.qmk.fm                                                                 |
| QMK Split Keyboard  | https://docs.qmk.fm/#/feature_split_keyboard                                        |
| Pro Micro Pinout    | https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide                 |
| Dactyl Manuform QMK | https://github.com/qmk/qmk_firmware/tree/master/keyboards/handwired/dactyl_manuform |
| Keyboard Tester     | https://www.keyboardtester.com                                                      |

---

_Setelah konfirmasi matrix size dan pin assignment, template `LAYOUT` macro dan seluruh konfigurasi bisa di-generate ulang secara lebih akurat._
