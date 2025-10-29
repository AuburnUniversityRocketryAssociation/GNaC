#include "SensorManager.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55);
Adafruit_BMP3XX bmp;
RTC_PCF8523 rtc;

void SensorManager::begin(){

    bool GND_link = false;
    if(Serial){
        GND_link = true;
        Serial.println("Beginning Sensor Start up Procedure"); 
    };

    Wire.begin();

    // Initialize IMU 
    const int IMU_I2C_Address = 0x28;
    const int IMU_Sensor_ID = 55;
    bno = Adafruit_BNO055(IMU_Sensor_ID, IMU_I2C_Address, &Wire);

    if (!bno.begin()) {
        if(GND_link){
            Serial.println("[ERROR] Failed to initialize IMU!");
        };
        while (1);
    };
    delay(2000); // wait 2 secconds for BNO to stablize
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy
    
    if(GND_link){
        Serial.println("IMU initialized!");
    }

    // Barometer
    const int BAROMETER_I2C_Address = 0x77;
    
    if (!bmp.begin_I2C(BAROMETER_I2C_Address, &Wire)){
        if (GND_link){
            Serial.println("[ERROR] Failed to initialize Barometer!");
        }
        while(1);
    }
    // Serial.print("Configuring BMP...");
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    // Serial.println("DONE.");

    if(GND_link){
        Serial.println("Baramoeter initialized!");
    }



    // Fixed RTC_I2C_Address = 0x68;
    if (!rtc.begin(&Wire)){
        Serial.println("[ERROR] Failed to initialize Real Time Clock!");
        while(1);
    }
    if (! rtc.initialized() || rtc.lostPower()) {
        
        Serial.println("RTC is NOT initialized, let's set the time!");
        
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
        //
        // Note: allow 2 seconds after inserting battery or applying external power
        // without battery before calling adjust(). 
        
        Serial.print("Date set to: ");
        Serial.println(rtc.now().timestamp(DateTime::TIMESTAMP_FULL));
        
    } 
    rtc.start();

    if(GND_link){
        Serial.println(rtc.now().timestamp(DateTime::TIMESTAMP_FULL));
        Serial.println("Real Time Clock initialized!");
        Serial.println("All sensors initialized");
    }
}



SensorReport SensorManager::read(){

    SensorReport report;

    bool GND_link;
    if(Serial){
        GND_link = true;
    }
    
    report.timestamp_ms = millis();

    // read IMU
    imu::Vector<3> a = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> g = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Vector<3> m = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    // report.accel[0] = a.x(); report.accel[1] = a.y(); report.accel[2] = a.z();
    report.gyro[0] = g.x();  report.gyro[1] = g.y();  report.gyro[2] = g.z();
    // report.mag[0] = m.x();   report.mag[1] = m.y();   report.mag[2] = m.z();

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    imu::Quaternion q = bno.getQuat();

    // gets acceration and then maps it to global frame
    imu::Vector<3> linAccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
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