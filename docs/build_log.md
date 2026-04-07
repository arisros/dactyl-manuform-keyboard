# 🔧 Build Log — Dactyl Manuform Custom Keyboard

Catatan kronologis proses build, debug, dan rekonstruksi firmware.

---

## Entry Format

```
[YYYY-MM-DD] <Fase/Tag> — <Apa yang dikerjakan>
Hasil: <Berhasil / Gagal / Partial>
Catatan: <Hal penting, error, temuan>
```

---

## Log

### [2026-04-07] Project Init — Repo created, reconstruction plan documented
**Hasil:** Berhasil  
**Catatan:** Repo `arisjirat/dactyl-manuform-keyboard` dibuat public. QMK firmware scaffold sudah ada tapi masih placeholder — pin dan matrix belum dikonfirmasi fisik.

---

## Status per Fase

| Fase | Nama | Status |
| --- | --- | --- |
| 1 | Reverse keymap dari firmware yang ada | ⬜ Not Started |
| 2 | Struktur project QMK | ⬜ Not Started |
| 3 | File konfigurasi (config.h, info.json) | ⬜ Not Started |
| 4 | Template keymap (keymap.c + layers) | ⬜ Not Started |
| 5 | Konfirmasi MASTER_RIGHT vs EE_HANDS | ⬜ Not Started |
| 6 | Flashing aman ke kedua sisi | ⬜ Not Started |
| 7 | Debugging matrix via qmk console | ⬜ Not Started |

---

## Parts List

| Komponen | Qty | Catatan |
| --- | --- | --- |
| Pro Micro (ATmega32U4) | 2 | Satu per sisi |
| Dioda 1N4148 | ~72 | Per switch |
| TRRS Jack (PJ-320A) | 2 | Satu per sisi |
| Kabel TRRS | 1 | Penghubung split |
| MX / Choc Switch | ~72 | Sesuai layout |
| Keycaps | ~72 | |
| TRRS ke USB-C adapter | 1 | Jika perlu |

---

## Wiring Notes

> *Isi setelah konfirmasi fisik dari skema keyboard*

### Row Pins (per sisi)
- Sisi kiri: TBD
- Sisi kanan: TBD

### Col Pins (per sisi)
- Sisi kiri: TBD
- Sisi kanan: TBD

### TRRS / Serial Pin
- Serial data pin: TBD (D0 atau D1)

### Diode Direction
- TBD (COL2ROW atau ROW2COL — cek orientasi dioda fisik)
