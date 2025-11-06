#include "Logger/LogManager.h"
#include "Sensor/SensorManager.h"
#include "FlightState.h"
#include "LED/ledManager.h"
#include "Rocket.h"

SensorManager sensors;
LogManager logger;
FlightStateMachine fsm;
Rocket rocket;

uint32_t lastTime;

void setup() {
  // Attempts USB serial
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n\nRocket Flight Computer Starting...");

  // intialize
  sensors.begin();
  fsm.begin();
  logger.begin();

  Serial.println("Setup complete. Beginning Frame-rate operations.");

}

void loop() {
  // Main code to run every frame:
  
  bool GND_link;
  if(Serial){ 
    GND_link = true;
  }
  
  // --- Read sensors --
  SensorReport Sensor_report = sensors.read();   // Read IMU, Baro, etc.
   
  rocket.report = Sensor_report;              // last sensor report
  rocket.date = Sensor_report.Date;           // UTC ish date - time
  rocket.FC_temp = Sensor_report.CPU_temp;
  
  
  // --- GNC Loop ---
  // navigation(sensorReport);  // KF or PF --> state estimation
  // guidance();                // path planning                        NOT VALID FOR USE CASE
  // control();                 // Correction using control surfaces    NOT VALID FOR USE CASE
  
  
  // --- Events ---
  
  // Hardware in the loop test
  if (Serial.available()) {
    char input = Serial.read();  // Read one byte
    
    if (input == 'l') {          // Trigger on 'l' to launch
      Sensor_report.altitude = 2;
      Sensor_report.accel[2] = 5;
    }
    if (input == 'a'){          // trigger on 'a' to apogee
      Sensor_report.altitude = 20;
      Sensor_report.accel[2] = -1;
    }
    if (input == 'c'){        // trigger on 'c' to crash landl
      Sensor_report.altitude = 2;
      Sensor_report.accel[2] = 0;
    }
  }
  
  
  fsm.update(Sensor_report);
  // eventManager(); // handles EVENT (status) class,  Example. pastApogge == true --> Rocket.launchParachute()
  
  ledManager(fsm.getState()); // blinky led cool
  
  // powerManager();  // measure voltage and current, disable power to subsystems drawing too much.
                      // handles abort secnarios if loss of power, short, or over temperature 
  
  
  // Logs event data by clearing fsm event buffer
  if(fsm.event != ""){
    logger.logEvent(fsm.event, fsm.getState());
    fsm.event = "";
  }
  
  logger.update(rocket, GND_link, fsm.getState()); // writes flight data to flash memory, then at end writes to mircoSD

  // massManager(); // update vehicleManager object, tracking mass, CoM, and MMOI on 3 axes based on flight time

  // timeStepUpdate(); // ensure constant framerate
}