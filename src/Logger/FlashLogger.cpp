#include "FlashLogger.h"

#include <LittleFS.h>

// Return 0 on success, 1 on log file creation failure, 2 on event file creation failure
int FlashLogger::begin(const char* FileLog, const char* FileEvent) {
  
  if (!flash.begin()) {
    Serial.println("[ERROR] FlashLogger: Failed to mount LittleFS");
    return -1;
  } 

  this->FileLog = FileLog;
  this->FileEvent = FileEvent;

  //log file
  flashLog = flash.open(this->FileLog, FILE_WRITE);
  if (!flashLog) {
    Serial.println("[ERROR] FlashLogger: Failed to create log file");
    return 1;
  }
  flashLog.flush();
  flashLog.close();

  // Event file
  flashEventLog  = flash.open(this->FileEvent, FILE_WRITE);
  if (!flashEventLog) {
    Serial.println("[ERROR] FlashLogger: Failed to create event file");
    return 2;
  } 
  flashEventLog.println("FlashLogger started at " + String(millis()) + " milliseconds");
  flashEventLog.flush();
  flashEventLog.close();
  return 0;
}


void FlashLogger::log(String line) {
  flashLog = flash.open(FileLog, FILE_WRITE);
  flashLog.seek(flashLog.size()); // Move to end for appending
  flashLog.println(line);
  flashLog.flush();
  flashLog.close();
}


File FlashLogger::getFile(const char* filename) {
  return flash.open(filename, FILE_READ);
}


void FlashLogger::logEvent(String event) {
  String timestampedEvent = String(millis() / 1000) + "," + event;
  flashEventLog = flash.open(FileEvent, FILE_WRITE);
  flashEventLog.seek(flashEventLog.size()); // Move to end for appending
  flashEventLog.println(timestampedEvent);
  flashEventLog.flush();
  flashEventLog.close();
}