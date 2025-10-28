#include "SDLogger.h"

int SDLogger::begin() {
  SD.begin(BUILTIN_SDCARD);
  // write header for CSV log file
  logFile = SD.open("flight_log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("timestamp,accelX,accelY,accelZ,roll,pitch,yaw,altitude,baroTemp,CPU_Temp,positionX,positionY,positionZ,velocityX,velocityY,velocityZ,estAccelX,estAccelY,estAccelZ");
    logFile.flush();
    logFile.close();
  }
  return 0;
}

void SDLogger::log(String line) {
  if (!logFile) {
    logFile = SD.open("flight_log.csv", FILE_WRITE);
  }
  logFile.println(line);
  logFile.flush();
}

File SDLogger::getLogFile() {
  return logFile;
}