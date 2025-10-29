#include "LogManager.h"

/*
given
    MAX_LOG_TIME = size(LOG_BYTE) * LOG_INTERVAL
    MAX_LOG_SIZE = size(LOG_BYTE) * MAX_LOG_COUNT
if 
    each log is 100 bytes 
then 
    max size is 1.6 MB
    time is 16 minutes
*/ 


void LogManager::begin() {
  bool GND_link;
  if(Serial){
    GND_link = true;
    Serial.println("Beginning Log Manger");
  }

  // Flash
  if (flashLogger.begin()){
    if (GND_link) Serial.println("[ERROR] Flash Logger init failed!");
    while (1);
  }
  if(GND_link) Serial.println("Flash Initialized");
  
  // SD Card
  if (sdLogger.begin()){
    if (GND_link) Serial.println("[ERROR] SD Logger init failed!");
    while (1);
  }
  if(GND_link) {
    Serial.println("Flash Initialized");
    Serial.println("Log Manager Initialized Sucessfully");
  }
};



bool LogManager::update(Rocket Rocket, bool GND_link, String FlightState) {
  uint32_t current_time = millis();
  uint32_t deltaLogTime = current_time - Rocket.lastLogTimestamp;
  if ( ( deltaLogTime >= LOG_INTERVAL)){

    String line = String(current_time/1000) + "," +                                                                                          // log timestamp
                String(Rocket.report.timestamp_ms) + "," +                                                                              // Sensor Report timestamp
                String(Rocket.report.accel[0]) + "," + String(Rocket.report.accel[1]) + "," + String(Rocket.report.accel[2]) + "," +    // Accerlerometer
                String(Rocket.report.gyro[0]) + "," + String(Rocket.report.gyro[1]) + "," + String(Rocket.report.gyro[2]) + "," +       // gyroscopes
                String(Rocket.report.altitude) + "," +                                                                                  // Baraometer pressure
                String(Rocket.report.tempature) + "," +                                                                                 // Barometer tempature
                String(Rocket.FC_temp) + "," +                                                                                          // Teensy  tempature
                String(Rocket.position[0]) + "," + String(Rocket.position[1]) + "," + String(Rocket.position[2]) + "," +                // estimated postion
                String(Rocket.velocity[0]) + "," + String(Rocket.velocity[1]) + "," + String(Rocket.velocity[2]) + "," +                // estimated velcoity
                String(Rocket.accel[0]) + "," + String(Rocket.accel[1]) + "," + String(Rocket.accel[2]);                                //estimated acceleration

    if(FlightState == "LANDED"){
      if (!hasDumped) {
        tryDumpFlashToSD();
        hasDumped = true;
      }else{
        sdLogger.log(line);
      }
    } else {
      flashLogger.log(line);
    }

    //if(GND_link) Serial.println(line);  // great for debug
  };
  Rocket.lastLogTimestamp = current_time;
  return true;
}

void LogManager::tryDumpFlashToSD() {
  File sdFile = SD.open("flash_dump.csv", FILE_WRITE);
  if (sdFile) {
    flashLogger.dumpToSD(sdFile);
    sdFile.close();
  }
}