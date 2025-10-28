#include "logManager.h"
#include "objectsGlobal.h"
#include "State.h"

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
  flashLogger.begin();
  sdLogger.begin();
  activeLogger = &flashLogger;
}

void LogManager::update(const SensorReport& report) {
  uint32_t current_time = millis();
  uint32_t deltaLogTime = current_time - rocket.lastLogTime;
  if ( ( deltaLogTime >= LOG_INTERVAL)){

        if(rocket.isLanded){
          activeLogger = &sdLogger;
          if (!hasDumped) {
            tryDumpFlashToSD();
            hasDumped = true;
          }
        } else {
          activeLogger = &flashLogger;
        }
        activeLogger->log(report);

       if(rocket.GND_link){
           Serial.print("Seconds from start: "+ String(report.timestamp/1000));
           Serial.print("\t Alt: " + String(report.altitude));
           Serial.print("\t X: " + String(report.accelX)+ "\t  Y: "+ String(report.accelY) + "\t  Z: " + String(report.accelZ));
           Serial.print("\t Roll: "+ String(report.roll)+ "\t Pitch: "+ String(report.pitch)+ "\t Yaw: "+ String(report.yaw));
           Serial.print("\t Log Cycle time [ms]: "+ String(deltaLogTime));
           Serial.println("");
        };
        rocket.lastLogTime = current_time;
    };  
}

void LogManager::tryDumpFlashToSD() {
  File sdFile = SD.open("flash_dump.csv", FILE_WRITE);
  if (sdFile) {
    flashLogger.dumpToSD(sdFile);
    sdFile.close();
  }
}