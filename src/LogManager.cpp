#include "logManager.h"

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


void LogManager::begin(bool GND_link) {
  // flashLogger.begin();
  if (flashLogger.begin()){
    if (GND_link) {
    Serial.println("[ERROR] Flash Logger init failed!");
    }
    while (1);
  }
  
  // throws error if sd card not found
  if (sdLogger.begin()){
    if (GND_link) {
    Serial.println("[ERROR] SD Logger init failed!");
    }
    while (1);
  }
};

bool LogManager::update(Rocket* &Rocket) {
  uint32_t current_time = millis();
  uint32_t deltaLogTime = current_time - &Rocket.lastLogTime;
  if ( ( deltaLogTime >= LOG_INTERVAL)){

    String line = String(report.timestamp) + "," + // sensor timestamp
                String(report.accelX) + "," + String(report.accelY) + "," + String(report.accelZ) + "," +   // Accerlerometer
                String(report.roll) + "," + String(report.pitch) + "," + String(report.yaw) + "," + // gyroscopes
                String(report.altitude) + "," + // Baraometer
                String(report.tempature) + "," + //barometer tempature
                String(Rocket.CPU_Temp) + "," + // Teensy CPU tempature
                String(Rocket.state.positionX) + "," + String(Rocket.state.positionY) + "," + String(Rocket.state.positionZ) + // estimated postion
                String(Rocket.state.velocityX) + "," + String(Rocket.state.velocityY) + "," + String(Rocket.state.velocityZ) + // estimated velcoity
                String(Rocket.state.accelX) + "," + String(Rocket.state.accelY) + "," + String(Rocket.state.accelZ);   //estimated acceleration

    if(Rocket.isLanded){
      if (!hasDumped) {
        tryDumpFlashToSD();
        hasDumped = true;
      }else{
        sdLogger.log(line);
      }
    } else {
      flashLogger.log(line);
    }

    if(Rocket.GND_link){
      Serial.println(line);
    };
  };
  this->current_time;  
  return true;
}

void LogManager::tryDumpFlashToSD() {
  File sdFile = SD.open("flash_dump.csv", FILE_WRITE);
  if (sdFile) {
    flashLogger.dumpToSD(sdFile);
    sdFile.close();
  }
}