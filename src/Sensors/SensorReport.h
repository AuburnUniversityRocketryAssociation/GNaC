#ifndef SensorReport_H
#define SensorReport_H

#include "RTClib.h"

struct SensorReport {
    uint32_t timestamp;             // Unix timestamp in milliseconds
    uint32_t deltaTime;             // time since last sensor report
    float accelX, accelY, accelZ;   // IMU Acceleromter
    float yaw, roll, pitch;         // IMU Magnometer
    double latitude, longitude;     // GPS coordinates
    float altitude;                 // Barometer altitude
    float tempature;                // Barometer tempaure
    float CPU_temp;                 
    DateTime Date;                  // RTC date
};

#endif