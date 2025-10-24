#ifndef OBJECTSGLOBAL_H
#define OBJECTSGLOBAL_H

#include "Rocket.h"
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP3XX.h>
#include "RTClib.h"

extern Rocket rocket;
extern Adafruit_BNO055 bno;
extern Adafruit_BMP3XX bmp;
extern RTC_PCF8523 rtc;

#endif