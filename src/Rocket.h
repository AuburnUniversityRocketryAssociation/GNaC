#ifndef Rocket_H
#define Rocket_H

#include "Sensors/SensorReport.h"
#include "State.h"
// #include "Sensors/readSensors.h"
#include "Logger/LogManager.h"
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP3XX.h>
#include <bmp3.h>
#include <Arduino.h>




class Rocket {
private:
    SensorReport sensorReport;
    LogManager logger;
    Adafruit_BNO055 bno;
    Adafruit_BMP3XX bmp;
    RTC_PCF8523 rtc;
 

public:
    
    unsigned int time;                      // timestamp in milliseconds
    State state;                            // rocket State
    float voltage;                          // battery voltage
    double latitude, longitude;             // GPS coordinates
    float altitude;                         // Barometer altitude 
    logicState logic;                       // Logic state of vehicle
    DateTime date;                          // Date from Real Time Clock
    uint32_t lastLogTime;
    bool isLanded;
    bool GND_link;                          // is connected to USB
    float CPU_Temp;

    // int speed;
    // int G_force;

    // Default constructor
    Rocket(); 

    void init(); // initializes serial communication and sensors

    void setLogicState(logicState lState); // sets rocket logic state

    void readSensors(); // updates sensorReport with new sensor data

    void logManager(); // calls logger to log current rocket state and sensor report

    void timeStepUpdate(); // handles timing for framerate consistency

};

#endif