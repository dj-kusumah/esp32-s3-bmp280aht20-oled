#include "Logger.h"

void Logger::begin(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial) {
        delay(10);
    }
    Serial.println();
    Serial.println("=================================");
    Serial.println("   ESP32-S3 Logger Started!");
    Serial.println("=================================");
}

void Logger::info(const char* message) {
    Serial.print("[INFO] ");
    Serial.println(message);
}

void Logger::info(const String& message) {
    Serial.print("[INFO] ");
    Serial.println(message);
}

void Logger::error(const char* message) {
    Serial.print("[ERROR] ");
    Serial.println(message);
}

void Logger::debug(const char* message) {
    Serial.print("[DEBUG] ");
    Serial.println(message);
}

void Logger::printChipInfo() {
    Serial.println("\n--- Chip Info ---");
    Serial.printf("Chip Model: %s\n", ESP.getChipModel());
    Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
    Serial.printf("CPU Cores: %d\n", ESP.getChipCores());
    Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("PSRAM Size: %d bytes\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
    Serial.println("-----------------\n");
}
