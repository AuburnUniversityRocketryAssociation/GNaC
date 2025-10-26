#include "initializeFC.h"
#include "Sensors/readSensors.h"
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include "objectsGlobal.h"

int initializeFC(){
    //Sensors and rocket object are declared in objectsGlobal.cpp but not created

    State initialState;

    initialState.time = millis();
    initialState.positionX= 0;
    initialState.positionY= 0;
    initialState.positionZ= 0;
    initialState.velocityX= 0;
    initialState.velocityY= 0;
    initialState.velocityZ= 0; 
    initialState.accelX= 0;
    initialState.accelY= 0;
    initialState.accelZ= 0; 

    //Euler angles would be better than row, yaw, pitch
    
    initialState.roll        = 0;
    initialState.pitch       = 0;
    initialState.yaw         = 0;
    initialState.latitude    = 0;
    initialState.longitude   = 0;
    initialState.altitude    = 0;
    initialState.logic       = UNARMED;
    
    // attempt serial through USB
    Serial.begin(115200);
    initialState.GND_link = false;
    if(Serial){
        initialState.GND_link = true;
    };
    
    Wire.begin();
    Serial.println("Beginning Start up Procedure");   

    // Initialize IMU 
    const int IMU_I2C_Address = 0x28;
    const int IMU_Sensor_ID = 55;
    Adafruit_BNO055 bno = Adafruit_BNO055(IMU_Sensor_ID,IMU_I2C_Address, &Wire);

    if (!bno.begin()) {
        if(initialState.GND_link){
            Serial.println("[ERROR] Failed to initialize BNO055!");
        };
        while (1);
    };
    delay(2000); // wait 2 secconds for BNO to stablize
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy


    // Initialize Baramoeter
    const int Barometer_I2C_Address = 0x77;
    if (!bmp.begin_I2C(Barometer_I2C_Address, &Wire)) {
        if(initialState.GND_link){
            Serial.println("[ERROR] Failed to initialize IMU!");
        };
        while (1);
    }
    Serial.print("Configuring BMP...");
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    Serial.println("DONE.");


    // Initialize RTC
    if (!rtc.begin(&Wire)) {    // Fixed RTC_I2C_Address = 0x68;
        if(initialState.GND_link){
            Serial.println("[ERROR] Failed to initialize RTC!");
        };
        while (1);
    }    

    if (! rtc.initialized() || rtc.lostPower()) {
        if(initialState.GND_link){
            Serial.println("RTC is NOT initialized, let's set the time!");
        };
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        //
        // Note: allow 2 seconds after inserting battery or applying external power
        // without battery before calling adjust(). 
        if(initialState.GND_link){
            Serial.print("Date set to: ");
            Serial.println(rtc.now().timestamp(DateTime::TIMESTAMP_FULL));
        };
    }
    rtc.start();
    initialState.date = rtc.now();

    // initialize rocket object
    rocket.init(initialState);

    if(initialState.GND_link){
            Serial.println("Initialization complete. Beginning framerate-driven procedure.");
    };
    return 0;
}