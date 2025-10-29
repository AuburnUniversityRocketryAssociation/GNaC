#ifndef FLASHLOGGER_H
#define FLASHLOGGER_H


#include <string>
#include <LittleFS.h>
#include "Sensor/SensorReport.h"

class FlashLogger {
public:
  LittleFS_QSPIFlash flash;
  int begin();
  void log(String line);
  bool dumpToSD(File& sdFile);

private:
  static constexpr size_t MAX_ENTRIES = 10000;
  size_t writeIndex = 0;
  String buffer[MAX_ENTRIES];
};

#endif