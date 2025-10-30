#ifndef FLASHLOGGER_H
#define FLASHLOGGER_H


#include <string>
#include <LittleFS.h>
#include "Sensor/SensorReport.h"

class FlashLogger {
public:
  LittleFS_QSPIFlash flash;
  int begin(const char* FileLog, const char* FileEvent);
  void log(String line);
  void logEvent(String event);
  File getFile(const char* filename);

private:
  const char* FileLog;
  const char* FileEvent;
  File flashLog; 
  File flashEventLog;
  static constexpr size_t MAX_ENTRIES = 10000;
  size_t writeIndex = 0;
  String buffer[MAX_ENTRIES];
};

#endif