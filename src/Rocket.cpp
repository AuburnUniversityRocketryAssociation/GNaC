#include "Rocket.h"
#include "ULSI26.h"

// Constructor
Rocket::Rocket(){};

// Methods
void Rocket::init(State initialState, int IMU_I2C_Address, int RTC_I2C_Address, int Barometer_I2C_Address){
    this-> state = initialState;
    this-> IMU_I2C_Address = IMU_I2C_Address;
    this-> RTC_I2C_Address = RTC_I2C_Address;
    this-> Barometer_I2C_Address = Barometer_I2C_Address;
}