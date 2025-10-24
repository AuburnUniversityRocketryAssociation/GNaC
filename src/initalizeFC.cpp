#include "initalizeFC.h"
#include "readSensors.h"
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include "objectsGlobal.h"

int initalizeFC(){
    //Sensors and rocket object are declared in objectsGlobal.cpp but not created

    // attempt serial through USB
    Serial.begin(115200);
    Wire.begin();
    Serial.println("Beginning Start up Procedure");
    

    // Initalize IMU 
    const int IMU_I2C_Address = 0x28;
    const int IMU_Sensor_ID = 55;
    Adafruit_BNO055 bno = Adafruit_BNO055(IMU_Sensor_ID,IMU_I2C_Address, &Wire);

    if (!bno.begin()) {
        Serial.println("[ERROR] Failed to initialize BNO055!");
        while (1);
    };
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy


    // Initialize Baramoeter
    const int Barometer_I2C_Address = 0x77;
    if (!bmp.begin_I2C(Barometer_I2C_Address, &Wire)) {  
        Serial.println("[ERROR] Failed to initialize IMU!");
        while (1);
    }
    Serial.print("Configuring BMP #1...");
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    Serial.println("DONE.");


    // Initalize RTC
    const int RTC_I2C_Address = 0x68;
    if (!rtc.begin(&Wire)) {
        Serial.println("[ERROR] Failed to initialize RTC!");
        Serial.flush();
    }    

    if (! rtc.initialized() || rtc.lostPower()) {
        Serial.println("RTC is NOT initialized, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        //
        // Note: allow 2 seconds after inserting battery or applying external power
        // without battery before calling adjust(). This gives the PCF8523's
        // crystal oscillator time to stabilize. If you call adjust() very quickly
        // after the RTC is powered, lostPower() may still return true.
    }
    rtc.start();


    // initalize rocket object
    State initalState;
    rocket.init(initalState, IMU_I2C_Address, RTC_I2C_Address, Barometer_I2C_Address);

    Serial.println("Setup complete. Beginning framerate-driven procedure.");
    return 0;
}