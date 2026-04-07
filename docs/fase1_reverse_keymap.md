# 🔍 Fase 1 — Panduan Detail: Reverse Keymap & Matrix

> **Goal:** Temukan 5 hal yang belum diketahui tanpa source code asli:
> 1. Keymap (key apa yang ada di posisi fisik mana)
> 2. Matrix size (berapa baris × kolom)
> 3. Pin assignment (row/col pakai pin Pro Micro yang mana)
> 4. Diode direction (COL2ROW atau ROW2COL)
> 5. Serial/TRRS data pin (D0 atau D1)

---

## Overview: 3 Jalur Investigasi

```
┌─────────────────────────────────────────────────────┐
│  Jalur A — Software (keyboard masih hidup & jalan)  │
│  Jalur B — Fisik (multimeter, tracing kabel)        │
│  Jalur C — HID Sniffing (baca raw USB report)       │
└─────────────────────────────────────────────────────┘
```

Lakukan **semua jalur** — saling verifikasi satu sama lain.

---

## Jalur A — Software: Keymap Mapping

### A1. Key Output Testing

**Keyboard yang dipakai:** keyboard custom (yang mau di-reverse)  
**Tools:** keyboard tester online atau terminal

```bash
# Cara 1: Buka keyboard tester di browser
open https://www.keyboardtester.com

# Cara 2: Gunakan terminal dengan xev (macOS pakai wev atau karabiner)
# Atau cukup buka text editor kosong dan ketik tiap key
```

**Prosedur:**
1. Buka spreadsheet atau text file baru
2. Tekan setiap switch **satu per satu** dari kiri atas ke kanan bawah
3. Catat output di tabel ini (copy-paste ke file):

```
PHYSICAL MAP — LEFT HAND
========================
Row\Col  C0    C1    C2    C3    C4    C5
R0       ???   ???   ???   ???   ???   ???
R1       ???   ???   ???   ???   ???   ???
R2       ???   ???   ???   ???   ???   ???
R3       ???   ???   ???   ???   ???   ???
R4       ???   ???   ???   ???   ???   (empty)
THUMB    ???   ???   ???   ???

PHYSICAL MAP — RIGHT HAND
=========================
Row\Col  C0    C1    C2    C3    C4    C5
R0       ???   ???   ???   ???   ???   ???
R1       ???   ???   ???   ???   ???   ???
R2       ???   ???   ???   ???   ???   ???
R3       ???   ???   ???   ???   ???   ???
R4       (empty) ???  ???   ???   ???   ???
THUMB    ???   ???   ???   ???
```

> ⚠️ Jika key tidak respond: skip dulu, catat posisi fisik, tandai merah. Bisa jadi key break atau ghost.

### A2. Identifikasi Layer

Firmware yang sudah di-flash mungkin punya beberapa layer. Cek apakah ada modifier key yang mengaktifkan layer:

```bash
# Tekan setiap key di thumb cluster dan inner column
# Biasanya ada key LOWER/RAISE/FN di sana
# Setelah tahan modifier, tekan key lain → catat output layer 2, 3, dst
```

**Template layer mapping:**

```
LAYER 1 (hold ???):
Row\Col  C0    C1    C2    C3    C4    C5
R0       ???   ...

LAYER 2 (hold ???):
...
```

---

## Jalur B — Fisik: Matrix & Pin Tracing

> Butuh: multimeter dengan mode continuity (bunyi beep)

### B1. Identifikasi Matrix Size

Buka casing keyboard. Hitung secara fisik:

```
[ ] Hitung jumlah baris kabel yang keluar dari switch matrix ke Pro Micro
[ ] Hitung jumlah kolom kabel
[ ] Foto hasil penghitungan (referensi di docs/images/)
```

**Cara cepat hitung tanpa tracing:**
```
Total switch = jumlah fisik switch yang kamu pasang
Jika total = 72 keys (36 per sisi) → kemungkinan 6×6 = 36 atau 5×7 = 35
Jika total = 62 keys → kemungkinan 5×6 + 2 thumb = 32 per sisi
```

### B2. Tracing Row Pins

**Setup multimeter:** mode continuity (atau resistance)

```
Prosedur per baris:
1. Sentuh probe satu ke pin Pro Micro (cek pinout di bawah)
2. Tekan switch di baris yang diduga
3. Jika bunyi beep → pin itu terhubung ke baris ini
4. Tandai: ROW[n] = Pin[X]
```

**Pro Micro ATmega32U4 Pinout:**
```
                Pro Micro
               ┌─────────┐
           TXO─┤         ├─RAW
           RXI─┤         ├─GND
           GND─┤         ├─RST
           GND─┤         ├─VCC
           SDA─┤ 2     A3├─F4
           SCL─┤ 3     A2├─F5
             4─┤ 4     A1├─F6
             5─┤ 5     A0├─F7
             6─┤ 6    SCK├─B1/15
             7─┤ 7   MISO├─B3/14
             8─┤ 8   MOSI├─B2/16
             9─┤ 9     10├─B6
               └─────────┘

Pin mapping QMK name → physical:
B0 = pin 17    B1 = pin 15    B2 = pin 16
B3 = pin 14    B4 = pin 8     B5 = pin 9
B6 = pin 10    D0 = pin TXO   D1 = pin RXI
D4 = pin 4     F4 = pin A3    F5 = pin A2
F6 = pin A1    F7 = pin A0
```

**Template catat hasil:**
```
ROW PINS (kiri):
  Row 0 → Pro Micro pin: ___  (QMK name: ___)
  Row 1 → Pro Micro pin: ___  (QMK name: ___)
  Row 2 → Pro Micro pin: ___  (QMK name: ___)
  Row 3 → Pro Micro pin: ___  (QMK name: ___)
  Row 4 → Pro Micro pin: ___  (QMK name: ___)
  Row 5 → Pro Micro pin: ___  (QMK name: ___)
```

### B3. Tracing Column Pins

Sama seperti row, tapi trace dari sisi kolom. Column biasanya dihubungkan melalui dioda.

```
Prosedur:
1. Probe satu ke pin Pro Micro
2. Probe lain ke kaki dioda (sisi kolom)
3. Beep → pin ini adalah kolom tersebut

COL PINS (kiri):
  Col 0 → Pro Micro pin: ___  (QMK name: ___)
  Col 1 → Pro Micro pin: ___  (QMK name: ___)
  Col 2 → Pro Micro pin: ___  (QMK name: ___)
  Col 3 → Pro Micro pin: ___  (QMK name: ___)
  Col 4 → Pro Micro pin: ___  (QMK name: ___)
  Col 5 → Pro Micro pin: ___  (QMK name: ___)
```

### B4. Identifikasi Diode Direction

Lihat secara visual arah dioda (ada garis/tanda di badan dioda):

```
Jika dioda dipasang: Switch → | → Col wire  = ROW2COL
                               ^
                             dioda (garis = katoda)

Jika dioda dipasang: Row wire → | → Switch  = COL2ROW
```

**Cara cepat dengan multimeter:**
```
Mode dioda test:
1. Probe merah ke satu kaki switch, probe hitam ke kabel matrix
2. Jika bunyi: dioda arahnya dari switch ke kabel itu
3. Tentukan: kabel itu row atau col? → itu menentukan direction
```

### B5. Identifikasi TRRS Serial Pin

```
Cek kabel yang menghubungkan Pro Micro kiri ke TRRS jack:
- Biasanya 4 kabel: VCC, GND, DATA, (kadang DATA2)
- Data pin hampir selalu D0 (TXO) atau D1 (RXI)
- Trace kabel dari TRRS jack ke Pro Micro pin → itulah SOFT_SERIAL_PIN

SERIAL PIN: ___
```

---

## Jalur C — HID Sniffing (Advanced)

Baca raw USB HID report untuk decode keymap secara programatik.

### C1. Install Tools

```bash
# macOS
brew install hidapi
pip install hid

# Atau pakai hidviz (GUI)
brew install hidviz
```

### C2. Capture HID Report

```python
#!/usr/bin/env python3
"""
Script untuk capture raw HID keypress dari QMK keyboard.
Jalankan, lalu tekan tiap key dan lihat output raw report.
"""
import hid
import time

# Ganti dengan VID/PID keyboard kamu
# Cek dengan: system_profiler SPUSBDataType | grep -A5 "Keyboard"
VENDOR_ID  = 0xFEED   # default QMK VID
PRODUCT_ID = 0x0000   # ubah sesuai keyboard

def find_keyboard():
    for device in hid.enumerate():
        if device['vendor_id'] == VENDOR_ID:
            print(f"Found: {device['product_string']} "
                  f"(usage: {device['usage']}, usage_page: {device['usage_page']})")
            if device['usage_page'] == 0x01 and device['usage'] == 0x06:
                return device['path']
    return None

def main():
    path = find_keyboard()
    if not path:
        print("Keyboard not found! Check VID/PID")
        return

    d = hid.Device(path=path)
    print("Listening... tekan key (Ctrl+C untuk berhenti)")
    print("Format: [modifier, reserved, key1, key2, key3, key4, key5, key6]")

    try:
        while True:
            report = d.read(8, timeout_ms=100)
            if report and any(report):
                keys = [f"0x{b:02X}" for b in report]
                print(f"Report: {keys}")
    except KeyboardInterrupt:
        pass
    finally:
        d.close()

if __name__ == "__main__":
    main()
```

```bash
# Jalankan
python3 hid_capture.py
```

**Decode keycode:**
- Report byte[0] = modifier bitmask (Ctrl/Shift/Alt/GUI)
- Report byte[2..7] = keycodes (lihat HID Usage Tables)
- Keycode → key name: https://usb.org/document-library/hid-usage-tables-15

### C3. Cek VID/PID Aktual

```bash
# macOS: cek USB devices
system_profiler SPUSBDataType | grep -A 10 "Keyboard"

# Atau
ioreg -p IOUSB -l | grep -i keyboard
```

---

## Jalur D — QMK Console (Jika Firmware Punya Debug)

Jika firmware yang di-flash adalah QMK dengan CONSOLE_ENABLE:

```bash
# Install
pip install pyusb

# Jalankan QMK console — tekan key dan lihat matrix position
qmk console
```

**Output yang diharapkan:**
```
r:0 c:2 pressed   → row 0, col 2 aktif saat key ditekan
r:0 c:2 released
```

Ini langsung kasih matrix coordinate → paling akurat.

---

## Checklist Output Fase 1

Setelah semua jalur selesai, kamu harus punya:

```
[ ] Keymap table lengkap (setiap switch → key output)
[ ] Matrix size: ___ baris × ___ kolom per sisi
[ ] ROW PINS: { ___, ___, ___, ___, ___, ___ }
[ ] COL PINS: { ___, ___, ___, ___, ___, ___ }
[ ] Diode direction: COL2ROW / ROW2COL
[ ] SOFT_SERIAL_PIN: D0 / D1
[ ] Jumlah layer terdeteksi: ___
[ ] Key yang tidak respon (broken): ___
```

Setelah semua terisi → update `firmware/qmk/dactyl_manuform_custom/config.h` dengan nilai aktual dan lanjut ke **Fase 2**.

---

## Update config.h Setelah Konfirmasi

```c
// Ganti semua TODO placeholder dengan nilai aktual:

#define MATRIX_ROWS 12       // sesuaikan jika bukan 6+6
#define MATRIX_COLS 6        // sesuaikan

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }  // ← ganti dengan hasil trace
#define MATRIX_COL_PINS { F4, F5, F6, F7, B6, D4 }  // ← ganti dengan hasil trace

#define DIODE_DIRECTION COL2ROW   // ← ganti jika ROW2COL

#define SOFT_SERIAL_PIN D0        // ← ganti jika D1
```

Setelah ini, firmware siap di-compile:
```bash
qmk compile -kb handwired/dactyl_manuform_custom -km default
```
