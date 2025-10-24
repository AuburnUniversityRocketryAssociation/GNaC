#include "readSensors.h"
#include "ULSI26.h"

SensorReport readSensors(int IMU_I2C_Address, int RTC_I2C_Address, int Barometer_I2C_Address){
    SensorReport report;
    float pressure = -1.0f; // placeholder for initalization
        
    report.timestamp = millis();

    // readIMU(IMU_I2C_Address);
    sensors_event_t event;
    bno.getEvent(&event);
    
    // readBarometer(baroFile, report);
    // readRTC(_RTC_I2C_Address);

    // Simple formula assuming sea level pressure = 1013.25 hPa
    report.altitude = 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));

    return report;
}