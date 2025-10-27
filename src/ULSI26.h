// inlclude list to help keep main cleaner

#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include <SD.h>

#include "Managers/logEntry.h"
#include "RTClib.h"
#include "logicState.h"
#include "State.h"
#include "Sensors/SensorReport.h"
#include "Rocket.h"
#include "objectsGlobal.h"

#include "Managers/logManager.h"
#include "Managers/ledManager.h"
#include "initializeFC.h"
#include "Sensors/readSensors.h"