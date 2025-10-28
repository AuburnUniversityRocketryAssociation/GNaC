#include "SensorManager.h"


void SensorManager::begin(){



    // Initialize IMU 
    const int IMU_I2C_Address = 0x28;
    const int IMU_Sensor_ID = 55;
    bno = Adafruit_BNO055(IMU_Sensor_ID,IMU_I2C_Address, &Wire);

    if (!bno.begin()) {
        //if(rocket.GND_link){
            Serial.println("[ERROR] Failed to initialize BNO055!");
        //};
        while (1);
    };
    delay(2000); // wait 2 secconds for BNO to stablize
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy
    
    Serial.println("IMU initialized!");
    
}



SensorReport SensorManager::read(bool GND_link){

    SensorReport report;
    
    report.timestamp_ms = millis();

    // read IMU
    imu::Vector<3> a = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> g = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> m = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    report.accel[0] = a.x(); report.accel[1] = a.y(); report.accel[2] = a.z();
    report.gyro[0] = g.x();  report.gyro[1] = g.y();  report.gyro[2] = g.z();
    report.mag[0] = m.x();   report.mag[1] = m.y();   report.mag[2] = m.z();

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    imu::Quaternion q = bno.getQuat();

    // gets acceration and then maps it to global frame
    imu::Vector<3> linAccel = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    imu::Vector<3> globalAccel = q.rotateVector(linAccel);
    report.accel[0] = globalAccel.x();
    report.accel[1] = globalAccel.y();
    report.accel[2] = globalAccel.z();
    // Assuming no GPS available
    report.latitude = 0.0;
    report.longitude = 0.0;
    

    // read Barometer
    if (! bmp.performReading()) {
        if(GND_link){
            Serial.println("Failed to perform reading BMP :"); 
        }
    }
    else {
        report.tempature =(bmp.temperature);
        float pressure = (bmp.pressure / 100.0);

        // Simple formula assuming sea level pressure = 1013.25 hPa
        report.altitude = 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));
    }

    // Teensy CPU temp
    report.CPU_temp = tempmonGetTemp();

    // readRTC
    report.Date = rtc.now();

    return report;
}













// SensorReport readSensors(uint32_t time){
  
//     imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//     report.yaw = euler.x();
//     report.roll = euler.y();
//     report.pitch = euler.z();

//     imu::Vector<3> test = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    
//     imu::Quaternion q = bno.getQuat();
    
//     // gets acceration and then maps it to global frame
//     imu::Vector<3> linAccel = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    
//     imu::Vector<3> globalAccel = q.rotateVector(linAccel);

//     report.accelX = globalAccel.x();
//     report.accelY = globalAccel.y();
//     report.accelZ = globalAccel.z();


//     // read Barometer
//     if (! bmp.performReading()) {
//         if(rocket.GND_link){
//             Serial.println("Failed to perform reading BMP :"); 
//         }
//     }
//     else {
//         report.tempature =(bmp.temperature);
//         pressure = (bmp.pressure / 100.0);

//         // Simple formula assuming sea level pressure = 1013.25 hPa
//         report.altitude = 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));
//     }

//     // Teensy CPU temp
//     report.CPU_temp = tempmonGetTemp();
    
//     // readRTC
//     report.Date = rtc.now();

//     return report;
// }