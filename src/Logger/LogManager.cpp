#include "LogManager.h"

void LogManager::begin() {
  bool GND_link;
  if(Serial){
    GND_link = true;
    Serial.println("\t Beginning Log Manger");
  }

  // Flash
  // if (flashLogger.begin(FileLog, FileEvent)){
  //   if (GND_link) Serial.println("[ERROR] Flash Logger init failed!");
  //   while (1);
  // }
  // if(GND_link) Serial.println("Flash Initialized");
  
  // SD Card
  if (sdLogger.begin(FileLog, FileEvent)){
    if (GND_link) Serial.println("[ERROR] SD Logger init failed!");
    while (1);
  }
  if(GND_link) {
    Serial.println("Flash Initialized");
    Serial.println("\t Log Manager Initialized Sucessfully");
  }
};


bool LogManager::logEvent(String event, String FlightState) {
  
  // if(FlightState == "LANDED"){
    sdLogger.logEvent(event);
  // } else {
  //   flashLogger.logEvent(event);
  // }
  return true;
}


bool LogManager::update(Rocket Rocket, bool GND_link, String FlightState) {
  
  // if mission complete, stop logging
  if(FlightState == "COMPLETE") {
    // check if sd log file is open
    if (!sdLogger.getFile(FileLog)) {
      // close sd log file 
      sdLogger.getFile(FileLog).flush();
      sdLogger.getFile(FileLog).close();
    }
    return true;
  }


  uint32_t current_time = millis();
  uint32_t deltaLogTime = current_time - Rocket.lastLogTimestamp;
  if ( ( int(deltaLogTime) >= int(LOG_INTERVAL))){

    String line = String(current_time/1000) + "," +                                                                                     // log timestamp
                  String(Rocket.report.timestamp_ms) + "," +                                                                              // Sensor Report timestamp
                  String(Rocket.report.accel[0]) + "," + String(Rocket.report.accel[1]) + "," + String(Rocket.report.accel[2]) + "," +    // Accerlerometer
                  String(Rocket.report.gyro[0]) + "," + String(Rocket.report.gyro[1]) + "," + String(Rocket.report.gyro[2]) + "," +       // gyroscopes
                  String(Rocket.report.altitude) + "," +                                                                                  // Baraometer pressure
                  String(Rocket.report.tempature) + "," +                                                                                 // Barometer tempature
                  String(Rocket.FC_temp) + "," +                                                                                          // Teensy  tempature
                  String(Rocket.report.Date) + "," +                                                                                      // RTC Date and Time
                  // String(Rocket.position[0]) + "," + String(Rocket.position[1]) + "," + String(Rocket.position[2]) + "," +                // estimated postion
                  // String(Rocket.velocity[0]) + "," + String(Rocket.velocity[1]) + "," + String(Rocket.velocity[2]) + "," +                // estimated velcoity
                  // String(Rocket.accel[0]) + "," + String(Rocket.accel[1]) + "," + String(Rocket.accel[2]);                                //estimated acceleration
                  // String(Rocket.batteryVoltage);                                                                                          // Battery voltage
                  String("");

    // if(FlightState == "LANDED"){
    //   if (!hasDumped) {
    //     this->dumpFlashToSD();
    //     hasDumped = true;
    //   }else{
    //     sdLogger.log(line);
    //   }
    // } else {
    //   flashLogger.log(line);
    // }

    // Temporary: just log to SD
    sdLogger.log(line);

    // if(GND_link) Serial.println(line);  // debug tool
  };
  Rocket.lastLogTimestamp = current_time;
  return true;
}


// void LogManager::dumpFlashToSD() {
//   //opens flash log file and sd log file and writes flash to sd file

//   File flashLogFile = flashLogger.getFile(FileLog);
//   File sdLogFile = sdLogger.getFile(FileLog);

//   if (flashLogFile && sdLogFile) {
//     Serial.println("Dumping Flash log to SD Card...");
//     while (flashLogFile.available()) {
//       String line = flashLogFile.readStringUntil('\n');
//       sdLogFile.println(line);
//     }
//     this->logEvent("Flash log dumped to SD Card", "LANDED");
//     sdLogFile.flush();
//     sdLogFile.close();
//     flashLogFile.flush();
//     flashLogFile.close();
//   } else {
//     Serial.println("[ERROR] Unable to open log files for dump.");
//   }
//   File flashEventFile = flashLogger.getFile(FileEvent);
//   File sdEventFile = sdLogger.getFile(FileEvent);
//   if (flashEventFile && sdEventFile) {
//     Serial.println("Dumping Flash event log to SD Card...");
//     while (flashEventFile.available()) {
//       String line = flashEventFile.readStringUntil('\n');
//       sdEventFile.println(line);
//     }
//     this->logEvent("Flash event log dumped to SD Card", "LANDED");
//     sdEventFile.flush();
//     sdEventFile.close();
//     flashEventFile.flush();
//     flashEventFile.close();
//   } else {
//     Serial.println("[ERROR] Unable to open event files for dump.");
//   }
// }