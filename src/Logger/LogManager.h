#ifndef LOGMANAGER_H
#define LOGMANGER_H

//#include "FlashLogger.h"
#include "SDLogger.h"
#include "Sensor/SensorReport.h"
#include "Rocket.h"


class LogManager {
public:

  // Methods
  void begin();
  bool update(Rocket rocket, bool GND_link, String FlightState);
  bool logEvent(String event, String FlightState);
  // void dumpFlashToSD();

private:
  const int LOG_INTERVAL = 50; // milliseconds
  const char* FileLog = "log.csv";
  const char* FileEvent = "events.txt";
  //FlashLogger flashLogger;
  SDLogger sdLogger;
  bool hasDumped = false;
};
#endif