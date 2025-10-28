#ifndef State_H
#define State_H

#include "logicState.h"
#include "RTClib.h"

struct State {

    //  Global Frame 
    unsigned int time;                      // timestamp in milliseconds
    float positionX, positionY, positionZ;  // rocket Position
    float velocityX, velocityY, velocityZ;  // rocket Velocity
    float accelX, accelY, accelZ;           // rocket Acceleration

    //  Euler angles would be better than row, yaw, pitch
    
    float roll, yaw, pitch;                 // rocket 
    double latitude, longitude;             // GPS coordinates
    float altitude;                         // Barometer altitude 
    logicState logic;                       // Logic state of vehicle
    DateTime date;                          // Date from Real Time Clock
};

#endif