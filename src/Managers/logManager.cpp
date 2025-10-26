#include "logManager.h"
#include "objectsGlobal.h"

/*
given
max log time = 1000 seconds ~ 16 minutes
if 
each log is 16 bytes 
then 
max size is 0.16 MB
*/ 


const uint32_t LOG_INTERVAL = 10; // milliseconds
const size_t MAX_LOG_SIZE = 10000;  // Max entries before stopping
// example ---
size_t logIndex = 0;
bool loggingActive = true;

LogEntry logBuffer[MAX_LOG_SIZE];

void logToMemory(float data) {
    if (!loggingActive) return;

    if (logIndex < MAX_LOG_SIZE) {
        logBuffer[logIndex++] = {data};
    } else {
        loggingActive = false;  // Stop logging
        if(rocket.state.GND_link){
            Serial.println("[WARNING] Log limit reached. Logging stopped.");
        };
    };
};

// example ---

int logManager(SensorReport report){
    /*              --- TO DO ---
    - [ ] define important events like pastAppogee
    - [ ] Also need to check for major events
    - [ ] refine max log size
    */ 
   
   uint32_t current_time = millis();
   
   // Log rocket state if its been longer than the log interval
   if ( ( rocket.lastLogTime - current_time >= LOG_INTERVAL)){
        rocket.lastLogTime = current_time;

        if(rocket.state.GND_link){
            Serial.print("Seconds from start: "+ String(report.timestamp/1000));
            Serial.print("\t Alt: " + String(report.altitude));
            Serial.print("\t X: " + String(report.accelX)+ "\t  Y: "+ String(report.accelY) + "\t  Z: " + String(report.accelZ));
        };
    };

    return 0;
}