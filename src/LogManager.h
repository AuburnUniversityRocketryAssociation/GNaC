#ifndef LOGMANAGER_H
#define LOGMANGER_H

#include "FlashLogger.h"
#include "SDLogger.h"
#include "Sensors/SensorReport.h"
#include "Rocket.h"



class LogManager {
public:
  uint32_t LOG_INTERVAL = 50; // milliseconds
  bool begin(bool GND_link);
  uint32_t update(const SensorReport& report, Rocket Rocket); // returns log time
  void tryDumpFlashToSD();

private:
  FlashLogger flashLogger;
  SDLogger sdLogger;
  bool hasDumped = false;
};
#endif