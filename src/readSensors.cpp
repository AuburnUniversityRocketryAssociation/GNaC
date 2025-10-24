#include "readSensors.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include "objectsGlobal.h"
#include "RTClib.h"

SensorReport readSensors(){
    
    SensorReport report;
    float pressure;
    
    report.timestamp = millis();
    
    // readIMU(IMU_I2C_Address);
    sensors_event_t event;
    bno.getEvent(&event);   

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    report.heading = euler.x();
    report.roll = euler.y();
    report.pitch = euler.z();

    imu::Vector<3> linAccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    report.accelX = linAccel.x();
    report.accelY = linAccel.y();
    report.accelZ = linAccel.z();


    // readBarometer(baroFile, report);
    if (! bmp.performReading()) {
        if(rocket.state.GND_test){
            Serial.println("Failed to perform reading BMP :"); 
        }
    }
    else {
        report.tempature =(bmp.temperature);
        pressure = (bmp.pressure / 100.0);

        // Simple formula assuming sea level pressure = 1013.25 hPa
        report.altitude = 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));
    }
    

    // readRTC(_RTC_I2C_Address);
    report.Date = rtc.now();

    return report;
}