#ifndef READSENSORS_H
#define READSENSORS_H

#include "SensorReport.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <Adafruit_BMP3XX.h>
#include <Adafruit_BNO055.h>
#include <RTClib.h>

class SensorManager {
public:
    // Methods
    void begin();
    SensorReport read();
};
#endif