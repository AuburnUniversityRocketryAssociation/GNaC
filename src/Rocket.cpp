#include "Rocket.h"

// Constructor
Rocket::Rocket(){};

// Methods
void Rocket::init(){
    // Initialize serial communication and sensors
    Serial.begin(115200);

    if(Serial){
        this->GND_link = true;
        Serial.println("Beginning Start up Procedure"); 
    };
    
    Wire.begin();

    // logger.begin();

    // Initialize IMU 
    const int IMU_I2C_Address = 0x28;
    const int IMU_Sensor_ID = 55;
    Adafruit_BNO055 bno = Adafruit_BNO055(IMU_Sensor_ID,IMU_I2C_Address, &Wire);

    if (!bno.begin()) {
        if(this->GND_link){
            Serial.println("[ERROR] Failed to initialize BNO055!");
        };
        while (1);
    };
    delay(2000); // wait 2 secconds for BNO to stablize
    bno.setExtCrystalUse(true);  // Optional: use external crystal for better accuracy
    if(this->GND_link){
            Serial.println("IMU initialized!");
    };


    // Initialize Baramoeter
    const int Barometer_I2C_Address = 0x77;
    if (!bmp.begin_I2C(Barometer_I2C_Address, &Wire)) {
        if(this->GND_link){
            Serial.println("[ERROR] Failed to initialize IMU!");
        };
        while (1);
    }
     
    // Serial.print("Configuring BMP...");
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    // Serial.println("DONE.");

    if(this->GND_link){
        Serial.println("Baramoeter initialized!");
    }

    // Initialize RTC
    if (!rtc.begin(&Wire)) {    // Fixed RTC_I2C_Address = 0x68;
        if(rocket.GND_link){
            Serial.println("[ERROR] Failed to initialize RTC!");
        };
        while (1);
    }    

    if (! rtc.initialized() || rtc.lostPower()) {
        if(this->GND_link){
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
        if(this->GND_link){
            Serial.print("Date set to: ");
            Serial.println(rtc.now().timestamp(DateTime::TIMESTAMP_FULL));
        };
    } 
    rtc.start();

    if(this->GND_link){
        Serial.println("Real Time Clock initialized!");
    };  

    // logManger
    if(logger.begin(this->GND_link)){
        if(this->GND_link){
            Serial.println("Log Manager initialized!");
        };
    } else {
        if(this->GND_link){
            Serial.println("[ERROR] Failed to initialize Log Manager!");
        };
        while (1);
    }


};

void Rocket::setLogicState(logicState lState){
    this->logic = lState;
};