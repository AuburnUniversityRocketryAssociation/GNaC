// inlclude list to help keep main cleaner

#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include <SD.h>
#include <LittleFS.h>

#include "Logger/loggy.h"

#include "RTClib.h"
#include "logicState.h"
#include "State.h"
#include "Sensors/SensorReport.h"
#include "Rocket.h"
#include "objectsGlobal.h"

#include "LED/ledManager.h"
#include "initializeFC.h"
#include "Sensors/readSensors.h"