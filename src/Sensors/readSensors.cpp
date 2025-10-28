#include "readSensors.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <bmp3.h>
#include <Adafruit_BNO055.h>
#include "objectsGlobal.h"
#include "RTClib.h"

// Parm time: last sensor reading time
SensorReport readSensors(uint32_t time){
    
    SensorReport report;
    float pressure;
    report.timestamp = millis();
    uint32_t deltaTime = (report.timestamp - time) / 1000; // converted from milliSeconds to Seconds 
    report.deltaTime = deltaTime;
    
    // read IMU
    sensors_event_t event;
    bno.getEvent(&event);   


    // gets orientation in sensor frame
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    report.yaw = euler.x();
    report.roll = euler.y();
    report.pitch = euler.z();

    imu::Vector<3> test = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    
    imu::Quaternion q = bno.getQuat();
    
    // gets acceration and then maps it to global frame
    imu::Vector<3> linAccel = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    
    imu::Vector<3> globalAccel = q.rotateVector(linAccel);

    report.accelX = globalAccel.x();
    report.accelY = globalAccel.y();
    report.accelZ = globalAccel.z();


    // read Barometer
    if (! bmp.performReading()) {
        if(rocket.GND_link){
            Serial.println("Failed to perform reading BMP :"); 
        }
    }
    else {
        report.tempature =(bmp.temperature);
        pressure = (bmp.pressure / 100.0);

        // Simple formula assuming sea level pressure = 1013.25 hPa
        report.altitude = 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));
    }

    // Teensy CPU temp
    report.CPU_temp = tempmonGetTemp();
    
    // readRTC
    report.Date = rtc.now();

    return report;
}