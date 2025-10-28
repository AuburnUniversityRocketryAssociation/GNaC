#include "FlashLogger.h"
#include "objectsGlobal.h"
#include <LittleFS.h>

void FlashLogger::begin() {
  flash.begin();
}

void FlashLogger::log(const SensorReport& report) {
  String line = String(report.timestamp) + "," + // sensor timestamp
                String(report.accelX) + "," + String(report.accelY) + "," + String(report.accelZ) + "," +   // Accerlerometer
                String(report.roll) + "," + String(report.pitch) + "," + String(report.yaw) + "," + // gyroscopes
                String(report.altitude) + "," + // Baraometer
                String(report.tempature) + "," + //barometer tempature
                String(rocket.CPU_Temp) + "," + // Teensy CPU tempature
                String(rocket.state.positionX) + "," + String(rocket.state.positionY) + "," + String(rocket.state.positionZ) + // estimated postion
                String(rocket.state.velocityX) + "," + String(rocket.state.velocityY) + "," + String(rocket.state.velocityZ) + // estimated velcoity
                String(rocket.state.accelX) + "," + String(rocket.state.accelY) + "," + String(rocket.state.accelZ);   //estimated acceleration
  buffer[writeIndex] = line;
  writeIndex = (writeIndex + 1) % MAX_ENTRIES;
}

bool FlashLogger::dumpToSD(File& sdFile) {
  if (!sdFile) return false;
  for (size_t i = 0; i < MAX_ENTRIES; ++i) {
    size_t idx = (writeIndex + i) % MAX_ENTRIES;
    if (buffer[idx].length() > 0) {
      sdFile.println(buffer[idx]);
    }
  }
  sdFile.flush();
  return true;
}