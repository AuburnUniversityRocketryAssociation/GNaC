#ifndef LOGMANAGER_H
#define LOGMANGER_H

#include "Sensors/SensorReport.h"
#include "logEntry.h"
#include <SD.h>
#define FlashFS LittleFS_QSPIFlash

const uint32_t LOG_INTERVAL = 100; // milliseconds
const size_t MAX_LOG_SIZE = 5100;  // Max entries before stopping

// bool begin(uint8_t csPin);

// void log(const String& message);

// void logCSV(const String& tag, float value);

void logToMemory(float data);

// void logToSD();

int logManager(SensorReport report);

#endif