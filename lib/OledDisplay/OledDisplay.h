#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * Library OLED SSD1306 untuk ESP32-S3
 * 
 * Koneksi (4 pin):
 * - VCC -> 3.3V
 * - GND -> GND  
 * - SCL -> GPIO 9
 * - SDA -> GPIO 8
 */
class OledDisplay {
public:
    OledDisplay(uint8_t width = 128, uint8_t height = 64, uint8_t address = 0x3C);

    bool begin(int sdaPin = 8, int sclPin = 9);

    void showMessage(const char* line1, const char* line2 = nullptr);
    void showSensorData(float tempC, float humidity, float pressure);
    void clear();

    Adafruit_SSD1306& getDisplay();

private:
    Adafruit_SSD1306 _display;
    uint8_t _address;
    uint8_t _width;
    uint8_t _height;
};

#endif
