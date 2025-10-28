#ifndef FLASHLOGGER_H
#define FLASHLOGGER_H


#include <string>
#include "SensorReport.h"
#include <LittleFS.h>

class FlashLogger {
public:
  LittleFS_QSPIFlash flash;
  int begin();
  void log(String line);
  bool dumpToSD(File& sdFile);

private:
  static constexpr size_t MAX_ENTRIES = 1000;
  size_t writeIndex = 0;
  String buffer[MAX_ENTRIES];
};

#endif