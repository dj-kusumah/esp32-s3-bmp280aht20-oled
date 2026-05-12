# Latihan3

Project PlatformIO untuk ESP32-S3 DevKitC-1 yang membaca data lingkungan dari sensor AHT20 dan BMP280, lalu menampilkannya ke OLED SSD1306 melalui bus I2C.

## Fitur

1. Inisialisasi OLED SSD1306 128x64 di alamat `0x3C`.
2. Pembacaan suhu dan kelembapan dari AHT20.
3. Pembacaan tekanan udara dari BMP280.
4. Tampilan data sensor ke OLED.
5. Logging data ke Serial Monitor.

## Hardware yang dipakai

1. ESP32-S3 DevKitC-1
2. Modul BMP280 + AHT20 berbasis I2C
3. OLED SSD1306 I2C 128x64
4. Breadboard dan jumper

## Pin dan wiring

Project ini memakai satu bus I2C bersama:

1. `GPIO 8` untuk `SDA`
2. `GPIO 9` untuk `SCL`

Koneksi OLED:

1. `VCC` -> `3.3V`
2. `GND` -> `GND`
3. `SDA` -> `GPIO 8`
4. `SCL` -> `GPIO 9`

Koneksi BMP280 + AHT20:

1. `VCC` -> `3.3V`
2. `GND` -> `GND`
3. `SDA` -> `GPIO 8`
4. `SCL` -> `GPIO 9`

Alamat I2C yang dipakai:

1. AHT20: `0x38`
2. BMP280: `0x76` atau `0x77`
3. OLED SSD1306: `0x3C`

## Struktur inti project

```text
Latihan3/
|- platformio.ini
|- lib/
|  |- Logger/
|  |- OledDisplay/
|  |- SensorEnv/
|- src/
|  |- main.cpp
```

## Dependency utama

Dependency eksternal yang digunakan:

1. `adafruit/Adafruit SSD1306`
2. `adafruit/Adafruit GFX Library`
3. `adafruit/Adafruit AHTX0`
4. `adafruit/Adafruit BMP280 Library`

Library lokal yang dipakai oleh project:

1. `Logger`
2. `OledDisplay`
3. `SensorEnv`

## Cara build dan upload

Jalankan dari folder project ini:

```powershell
pio run
pio run -t upload
pio device monitor
```

Kalau port serial sering berubah, jangan hardcode `upload_port` dan `monitor_port` kecuali memang dibutuhkan. Biarkan PlatformIO auto-detect.

## Perilaku program saat ini

Saat board menyala:

1. OLED diinisialisasi lebih dulu.
2. Sensor AHT20 dan BMP280 diinisialisasi di bus I2C yang sama.
3. Program membaca data setiap 2 detik.
4. Suhu, kelembapan, dan tekanan ditampilkan ke OLED.
5. Nilai yang sama juga dikirim ke Serial Monitor.

Contoh data yang ditampilkan:

```text
=== Sensor Data ===
Suhu    : 29.4 C
Lembab  : 72.1 %
Tekanan : 1008.6 hPa
```

## Troubleshooting singkat

1. Kalau OLED tidak tampil, cek alamat `0x3C`, power, dan wiring I2C.
2. Kalau sensor tidak terbaca, cek koneksi `SDA` dan `SCL`, lalu pastikan modul benar memakai alamat `0x76` atau `0x77` untuk BMP280.
3. Kalau upload gagal, tutup aplikasi lain yang mungkin sedang memakai port serial.
4. Kalau log serial aneh, cek baud rate `115200`.