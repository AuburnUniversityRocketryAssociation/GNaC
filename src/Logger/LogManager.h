#ifndef LOGMANAGER_H
#define LOGMANGER_H

#include "FlashLogger.h"
#include "SDLogger.h"
#include "Sensor/SensorReport.h"
#include "Rocket.h"



class LogManager {
public:
  uint32_t LOG_INTERVAL = 50; // milliseconds

  // Methods
  void begin();
  bool update(Rocket rocket, bool GND_link, String FlightState); // returns log time
  void tryDumpFlashToSD();

private:
  FlashLogger flashLogger;
  SDLogger sdLogger;
  bool hasDumped = false;
};
#endif