#ifndef State_H
#define State_H

#include <string>

struct State {
    unsigned int time;                      // timestamp in milliseconds
    float positionX, positionY, positionZ;  // rocket Position
    float velocityX, velocityY, velocityZ;  // rocket Velocity
    float accelX, accelY, accelZ;           // rocket Acceleration
    float roll, yaw, pitch;                 // rocket 
    double latitude, longitude;             // GPS coordinates
    float altitude;                         // Barometer altitude 
    std::string logic;                      // Logic state TODO(convert to enum) 
};

#endif