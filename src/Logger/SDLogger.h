#include "ILogBackend.h"
#include <SD.h>

class SDLogger : public ILogBackend {
public:
  void begin();
  void log(const SensorReport& report);
  File getLogFile();

private:
  File logFile;
};