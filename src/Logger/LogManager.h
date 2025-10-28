#ifndef LOGMANAGER_H
#define LOGMANGER_H

#include "Sensors/SensorReport.h"
#include <SD.h>
#include <LittleFS.h>

// uint32_t LOG_INTERVAL = 30; // milliseconds

#include "FlashLogger.h"
#include "SDLogger.h"



class LogManager {
public:
  uint32_t LOG_INTERVAL = 50; // milliseconds
  void begin();
  void update(const SensorReport& report);
  void tryDumpFlashToSD();

private:
  FlashLogger flashLogger;
  SDLogger sdLogger;
  ILogBackend* activeLogger;
  bool hasDumped = false;
};
#endif