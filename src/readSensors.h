#ifndef READSENSORS_H
#define READSENSORS_H

#include "SensorReport.h"

SensorReport readSensors(int IMU_I2C_Address, int RTC_I2C_Address, int Barometer_I2C_Address);

#endif