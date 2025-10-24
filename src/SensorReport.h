#ifndef SensorReport_H
#define SensorReport_H

#include "RTClib.h"

struct SensorReport {
    uint32_t timestamp;         // Unix timestamp in milliseconds
    float accelX, accelY, accelZ;   // IMU Acceleromter
    float heading, roll, pitch;     // IMU Magnometer
    double latitude, longitude;     // GPS coordinates
    float altitude;                 // Barometer altitude
    float tempature;                // Barometer tempaure
    DateTime Date;                  // RTC date
};

#endif