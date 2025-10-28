#ifndef SensorReport_H
#define SensorReport_H

#include "RTClib.h"

struct SensorReport {
    uint32_t timestamp_ms;  
    float accel[3];         
    float gyro[3];          
    float mag[3];           
    double latitude, longitude;    
    float altitude;                 
    float tempature;                
    float CPU_temp;                 
    DateTime Date;                  
};

#endif