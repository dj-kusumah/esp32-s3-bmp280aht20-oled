#include "OledDisplay.h"

OledDisplay::OledDisplay(uint8_t width, uint8_t height, uint8_t address)
    : _display(width, height, &Wire, -1), _address(address), _width(width), _height(height) {}

bool OledDisplay::begin(int sdaPin, int sclPin) {
    Wire.begin(sdaPin, sclPin);

    if (!_display.begin(SSD1306_SWITCHCAPVCC, _address)) {
        Serial.println("[ERROR] OLED tidak ditemukan! Cek pin & alamat I2C.");
        return false;
    }

    _display.clearDisplay();
    _display.setTextColor(SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println("ESP32-S3 Sensor");
    _display.println("Menginisialisasi...");
    _display.display();

    Serial.println("[INFO] OLED berhasil diinisialisasi");
    return true;
}

void OledDisplay::showSensorData(float tempC, float humidity, float pressure) {
    _display.clearDisplay();

    // Judul
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println("=== Sensor Data ===");
    _display.drawLine(0, 10, _width, 10, SSD1306_WHITE);

    // Suhu
    _display.setCursor(0, 14);
    _display.print("Suhu    : ");
    _display.print(tempC, 1);
    _display.println(" C");

    // Kelembaban
    _display.setCursor(0, 28);
    _display.print("Lembab  : ");
    _display.print(humidity, 1);
    _display.println(" %");

    // Tekanan
    _display.setCursor(0, 42);
    _display.print("Tekanan : ");
    _display.print(pressure / 100.0F, 1);
    _display.println(" hPa");

    _display.display();
}

void OledDisplay::showMessage(const char* line1, const char* line2) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.println(line1);
    if (line2 != nullptr) {
        _display.setCursor(0, 16);
        _display.println(line2);
    }
    _display.display();
}

void OledDisplay::clear() {
    _display.clearDisplay();
    _display.display();
}

Adafruit_SSD1306& OledDisplay::getDisplay() {
    return _display;
}
