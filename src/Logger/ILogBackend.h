#ifndef ILOGBACKEND_H
#define ILOGBACKEND_H

#include "Sensors/SensorReport.h"

class ILogBackend {
public:
  virtual void begin() = 0;
  virtual void log(const SensorReport& report) = 0;
  virtual ~ILogBackend() {}
};

#endif