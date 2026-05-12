#include "SensorEnv.h"

SensorEnv::SensorEnv()
    : _temperature(0), _humidity(0), _pressure(0), _ahtOk(false), _bmpOk(false) {}

bool SensorEnv::begin(int sdaPin, int sclPin) {
    Wire.begin(sdaPin, sclPin);

    _ahtOk = _aht.begin();
    if (!_ahtOk) {
        Serial.println("[ERROR] AHT20 tidak ditemukan! Cek koneksi.");
    } else {
        Serial.println("[INFO] AHT20 berhasil diinisialisasi");
    }

    _bmpOk = _bmp.begin(0x76);
    if (!_bmpOk) {
        // Coba alamat alternatif 0x77
        _bmpOk = _bmp.begin(0x77);
    }
    if (!_bmpOk) {
        Serial.println("[ERROR] BMP280 tidak ditemukan! Cek koneksi.");
    } else {
        _bmp.setSampling(
            Adafruit_BMP280::MODE_NORMAL,
            Adafruit_BMP280::SAMPLING_X2,
            Adafruit_BMP280::SAMPLING_X16,
            Adafruit_BMP280::FILTER_X16,
            Adafruit_BMP280::STANDBY_MS_500
        );
        Serial.println("[INFO] BMP280 berhasil diinisialisasi");
    }

    return _ahtOk || _bmpOk;
}

bool SensorEnv::read() {
    bool ok = false;

    if (_ahtOk) {
        sensors_event_t humidity, temp;
        _aht.getEvent(&humidity, &temp);
        _temperature = temp.temperature;
        _humidity = humidity.relative_humidity;
        ok = true;
    }

    if (_bmpOk) {
        _pressure = _bmp.readPressure();
        // Gunakan suhu BMP280 jika AHT20 tidak tersedia
        if (!_ahtOk) {
            _temperature = _bmp.readTemperature();
        }
        ok = true;
    }

    return ok;
}

float SensorEnv::getTemperature() { return _temperature; }
float SensorEnv::getHumidity()    { return _humidity; }
float SensorEnv::getPressure()    { return _pressure; }
