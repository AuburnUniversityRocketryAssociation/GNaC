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
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
    Adafruit_BMP3XX bmp;
    RTC_DS3231 rtc;
    void begin();
    SensorReport read(bool GND_link);
};
#endif