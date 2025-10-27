#include "ULSI26.h"

void setup() {
  // Boot up procedure
  initializeFC(); // creates rocket object and establishes serial busses
  
    rocket.setLogicState(ARMED); 

  // timeStepUpdate();
}

void loop() {
  // Main code to run every frame:
  
  // --- Read sensors ---
  // powerManager(); // measure voltage and current, disable power to subsystems drawing too much.
  // handles abort secnarios if loss of power, short, or over temperature 
  
  // massManager(); // update vehicleManager object, tracking mass, CoM, and MMOI on 3 axes based on flight time
  
  SensorReport SensorReport = readSensors(rocket.state.time); // Read IMU/GPS, sensor array
  // GPS: u-blox NEO-M8N, ZED-F9P ZOE-M8Q
  // LoRa: RFM95, REYAX RYLR896
  
  // --- GNC Loop ---
  // navigation(sensorReport);  // KF or PF --> state estimation
  // guidance();                // path planning                        NOT VALID FOR USE CASE
  // control();                 // Correction using control surfaces    NOT VALID FOR USE CASE
  
  
  // --- Events ---
  // eventManager(); // handles EVENT (status) class,  Example. pastApogge == true --> Rocket.launchParachute()
  ledManager(); // blinky led cool
  // pyroManager(); // PYRO objects, checks continuity and, if firing, checks firing durations
  logManager(SensorReport); // writes flight data to flash memory, then at end writes to mircoSD
  // timeStepUpdate(); // ensure constant framerate
}