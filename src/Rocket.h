#ifndef Rocket_H
#define Rocket_H

#include "SensorReport.h"
#include "Rocket.h"
#include "State.h"
#include "readSensors.h"




class Rocket {
private:
public:
    int IMU_I2C_Address;
    int GPS_I2C_Address;
    int RTC_I2C_Address;
    int Barometer_I2C_Address;
    State state;

    // Default constructor
    Rocket(); // Do not use 

    // Methods
    void init(State initialState, int IMU_I2C_Address, int RTC_I2C_Address, int Barometer_I2C_Address);
};

#endif