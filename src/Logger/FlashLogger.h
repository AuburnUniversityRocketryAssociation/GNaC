#ifndef FLASHLOGGER_H
#define FLASHLOGGER_H

#include "ILogBackend.h"
#include <LittleFS.h>



class FlashLogger : public ILogBackend {
public:
  LittleFS_QSPIFlash flash;
  void begin();
  void log(const SensorReport& report);
  bool dumpToSD(File& sdFile);

private:
  static constexpr size_t MAX_ENTRIES = 1000;
  size_t writeIndex = 0;
  String buffer[MAX_ENTRIES];
};

#endif