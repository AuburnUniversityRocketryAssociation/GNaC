#include "SDLogger.h"

// return 0 on success
int SDLogger::begin(const char* FileLog, const char* FileEvent) {

  this->FileLog = FileLog;
  this->FileEvent = FileEvent;

  SD.begin(BUILTIN_SDCARD);


  File root = SD.open("/");
  this->listFiles(root, 0);
  root.close();
  

  // need to handle if there is no SD card present

  // need to check if files already exsist and handle appending vs overwriting
  if (SD.exists("/flight_log.csv")) {
    Serial.println("[Warning] Flight log exists. Do you wish to overwrite? (y/n)");
    while (true) {
      if (Serial.available()) {
        char resp = Serial.read();
        if (resp == 'y' || resp == 'Y') {
          Serial.println("Overwriting flight_log.csv");
          SD.remove("/flight_log.csv");
          break;
        } else if (resp == 'n' || resp == 'N') {
          Serial.println("Appending to existing flight_log.csv");
          break;
        } else {
          Serial.println("Invalid response. Please enter 'y' or 'n'.");
        }
      }
    }
  }

  logFile = SD.open("flight_log.csv", FILE_WRITE);
  if (logFile) {
    // write header for CSV log file
    logFile.println("timestamp,sensReport_ms,accelX,accelY,accelZ,roll,pitch,yaw,altitude,Baro_Temp,CPU_Temp");
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


void SDLogger::logEvent(String event) {
  File eventFile = SD.open(FileEvent, FILE_WRITE);
  if (eventFile) {
    eventFile.println(event);
    eventFile.flush();
    eventFile.close();
  }
}

File SDLogger::getFile(const char* filename) {
  return SD.open(filename, FILE_READ);
}

void SDLogger::listFiles(File dir, int numTabs) {
  while (true) {
      File entry = dir.openNextFile();
      if (!entry) break;

      for (int i = 0; i < numTabs; i++) Serial.print('\t');
      Serial.print(entry.name());
      if (entry.isDirectory()) {
          Serial.println("/");
          listFiles(entry, numTabs + 1);
      } else {
          Serial.print("\tSize: ");
          Serial.println(entry.size());
      }
      entry.close();
  }
}