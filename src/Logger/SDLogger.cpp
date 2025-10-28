#include "SDLogger.h"
#include "objectsGlobal.h"

void SDLogger::begin() {
  SD.begin(BUILTIN_SDCARD);
  logFile = SD.open("flight_log.csv", FILE_WRITE);
}

void SDLogger::log(const SensorReport& report) {
  if (!logFile) return;

  String line = String(report.timestamp) + "," + // sensor timestamp
                String(report.accelX) + "," + String(report.accelY) + "," + String(report.accelZ) + "," +   // Accerlerometer
                String(report.roll) + "," + String(report.pitch) + "," + String(report.yaw) + "," + // gyroscopes
                String(report.altitude) + "," + // Baraometer
                String(report.tempature) + "," + //barometer tempature
                String(rocket.CPU_Temp) + "," + // Teensy CPU tempature
                String(rocket.state.positionX) + "," + String(rocket.state.positionY) + "," + String(rocket.state.positionZ) + // estimated postion
                String(rocket.state.velocityX) + "," + String(rocket.state.velocityY) + "," + String(rocket.state.velocityZ) + // estimated velcoity
                String(rocket.state.accelX) + "," + String(rocket.state.accelY) + "," + String(rocket.state.accelZ);   //estimated acceleration
  logFile.println(line);
  logFile.flush();
}

File SDLogger::getLogFile() {
  return logFile;
}