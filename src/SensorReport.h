#ifndef SensorReport_H
#define SensorReport_H

struct SensorReport {
    unsigned int timestamp;         // Unix timestamp in milliseconds
    float accelX, accelY, accelZ;   // IMU accelerometer
    float gyroX, gyroY, gyroZ;      // IMU gyroscope
    double latitude, longitude;     // GPS coordinates
    float altitude;                 // Barometer altitude
};

#endif