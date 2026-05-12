#include <Arduino.h>
#include <SensorEnv.h>
#include <OledDisplay.h>
#include <Logger.h>

// Pin I2C (OLED & sensor pakai bus yang sama)
#define I2C_SDA_PIN 8
#define I2C_SCL_PIN 9

// Interval baca sensor (ms)
#define READ_INTERVAL_MS 2000

SensorEnv sensor;
OledDisplay oled(128, 64, 0x3C);

unsigned long lastReadTime = 0;

void setup() {
    Logger::begin(115200);
    Logger::printChipInfo();

    // Inisialisasi OLED
    oled.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    delay(500);

    // Inisialisasi sensor (Wire sudah diinit oleh oled.begin)
    if (!sensor.begin(I2C_SDA_PIN, I2C_SCL_PIN)) {
        oled.showMessage("ERROR!", "Sensor tidak ada");
        Logger::info("ERROR: Sensor tidak ditemukan!");
    } else {
        oled.showMessage("Sensor OK", "Mulai membaca...");
        Logger::info("Sensor siap. Membaca setiap 2 detik...");
    }

    delay(1000);
}

void loop() {
    unsigned long now = millis();

    if (now - lastReadTime >= READ_INTERVAL_MS) {
        lastReadTime = now;

        if (sensor.read()) {
            float temp     = sensor.getTemperature();
            float humidity = sensor.getHumidity();
            float pressure = sensor.getPressure();

            // Tampilkan di OLED
            oled.showSensorData(temp, humidity, pressure);

            // Log ke Serial Monitor
            String log = "Suhu: " + String(temp, 1) + " C | "
                       + "Lembab: " + String(humidity, 1) + " % | "
                       + "Tekanan: " + String(pressure / 100.0F, 1) + " hPa";
            Logger::info(log);
        } else {
            oled.showMessage("Baca gagal!", "Cek sensor...");
            Logger::info("ERROR: Gagal membaca sensor");
        }
    }
}