#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    static void begin(unsigned long baudRate = 115200);
    static void info(const char* message);
    static void info(const String& message);
    static void error(const char* message);
    static void debug(const char* message);
    static void printChipInfo();
};

#endif
