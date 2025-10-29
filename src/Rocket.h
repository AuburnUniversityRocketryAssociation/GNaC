#ifndef ROCKET_H
#define ROCKET_H

#include "Sensor/SensorReport.h"
#include "RTClib.h"

class Rocket{
public:
    float position[3];      // [x, y, z]
    float velocity[3];      // [x, y, z]
    float accel[3];         // [x, y, z]
    float orientation[3];   // euler angles (yaw pitch roll)
    SensorReport report;    // last sensor report
    DateTime date;          // UTC ish date
    uint32_t lastLogTimestamp;
    float batteryVoltage; 
    float FC_temp;

   
private:


};

#endif