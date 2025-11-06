#include "SDLogger.h"

// return 0 on success
int SDLogger::begin(const char* FileLog, const char* FileEvent) {
  this->FileLog = FileLog;
  this->FileEvent = FileEvent;

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("[Error] SD card initialization failed.");
    return 1;
  }

  File root = SD.open("/");
  this->listFiles(root, 0);
  root.close();

  // Handle Flight Log
  if (SD.exists(this->FileLog)) {
    if (!Serial) {
      SD.remove(this->FileLog);
    } else {
      Serial.println("[Warning] Flight log exists. Overwrite? (y/n)");
      while (true) {
        if (Serial.available()) {
          char resp = Serial.read();
          if (resp == 'y' || resp == 'Y') {
            SD.remove(this->FileLog);
            Serial.println("Overwriting flight log.");
            break;
          } else if (resp == 'n' || resp == 'N') {
            Serial.println("Appending to existing flight log.");
            break;
          } else {
            Serial.println("Invalid response. Enter 'y' or 'n'.");
          }
        }
      }
    }
  }

  // Handle Event Log
  if (SD.exists(this->FileEvent)) {
    if (!Serial) {
      SD.remove(this->FileEvent);
    } else {
      Serial.println("[Warning] Event log exists. Overwrite? (y/n)");
      while (true) {
        if (Serial.available()) {
          char resp = Serial.read();
          if (resp == 'y' || resp == 'Y') {
            SD.remove(this->FileEvent);
            Serial.println("Overwriting event log.");
            break;
          } else if (resp == 'n' || resp == 'N') {
            Serial.println("Appending to existing event log.");
            break;
          } else {
            Serial.println("Invalid response. Enter 'y' or 'n'.");
          }
        }
      }
    }
  }

  // Initialize flight log with header
  logFile = SD.open(this->FileLog, FILE_WRITE);
  if (logFile) {
    logFile.println("timestamp,sensReport_ms,accelX,accelY,accelZ,roll,pitch,yaw,altitude,Baro_Temp,CPU_Temp,RTC");
    logFile.flush();
    logFile.close();
  } else {
    Serial.println("[Error] Failed to open flight log for writing.");
    return 2;
  }

  eventFile = SD.open(this->FileEvent, FILE_WRITE);
  if (eventFile) {
    eventFile.println("Event log started at timestamp: " + String(millis()) + " milliseconds");
    eventFile.flush();
    eventFile.close();
  } else {
    Serial.println("[Error] Failed to open event log for writing.");
    return 3;
  }

  return 0;
}


void SDLogger::log(String line) {
  if (!logFile) {
    logFile = SD.open("flight_log.csv", FILE_WRITE);
  }
  logFile.println(line);
  logFile.flush();
  logFile.close();
}


void SDLogger::logEvent(String event) {
  // consider a memory buffer to prevent wear on sd card
  
  if (!eventFile) {
    eventFile = SD.open(FileEvent, FILE_WRITE);
  }
  eventFile.println(event);
  eventFile.flush();
  eventFile.close();
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