#ifndef SENSORENV_H
#define SENSORENV_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

/**
 * Library untuk modul kombinasi AHT20 + BMP280
 * 
 * Modul ini menggunakan I2C:
 * - AHT20  : alamat 0x38 (suhu + kelembaban)
 * - BMP280 : alamat 0x76 atau 0x77 (suhu + tekanan)
 * 
 * Koneksi:
 * - VCC -> 3.3V
 * - GND -> GND
 * - SCL -> GPIO 9
 * - SDA -> GPIO 8
 */
class SensorEnv {
public:
    SensorEnv();

    // Inisialisasi sensor, kembalikan true jika berhasil
    bool begin(int sdaPin = 8, int sclPin = 9);

    // Baca semua sensor (panggil sebelum getter)
    bool read();

    float getTemperature();   // Suhu dari AHT20 (°C)
    float getHumidity();      // Kelembaban dari AHT20 (%)
    float getPressure();      // Tekanan dari BMP280 (Pa)

private:
    Adafruit_AHTX0 _aht;
    Adafruit_BMP280 _bmp;

    float _temperature;
    float _humidity;
    float _pressure;

    bool _ahtOk;
    bool _bmpOk;
};

#endif
