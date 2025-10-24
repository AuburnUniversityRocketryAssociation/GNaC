#include "initalizeFC.h"
#include "readSensors.h"
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include "objectsGlobal.h"

int initalizeFC(){
    
    
    int IMU_I2C_Address = 0x28;
    int RTC_I2C_Address = 0x68;
    int Barometer_I2C_Address = 0x77;

    // attempt serial through USB
    Serial.begin(115200);
    Serial.println("Beginning Start up Procedure");

    // Establish wire with sensors
    Wire.begin();

    if (!bno.begin()) {
        Serial.println("Failed to initialize BNO055!");
        while (1);
    };
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy

    // Create rocket object
    State initalState;
    Rocket rocket1 = Rocket();
    rocket1.init(initalState, IMU_I2C_Address, RTC_I2C_Address, Barometer_I2C_Address);

    Serial.println("Setup complete. Beginning framerate-driven procedure.");
    return 0;
}