#ifndef LOGMANAGER_H
#define LOGMANGER_H

#include "Sensors/SensorReport.h"
#include "logEntry.h"
#include <SD.h>

int logManager(SensorReport report);

#endif