#include "ULSI26.h"

void setup() {
  // Boot up procedure
  
  initalizeFC(); // creates rocket object and establishes serial busses
  
  
  // setFlightComputerState(FC_ARMED);
  // setVehicleState(VEHICLE_STARTUP);
  // setControlState(CONTROL_DISABLED);
  // timeStepUpdate();
}

void loop() {
  // Main code to run every frame:

  
  // --- Read sensors ---
  SensorReport SensorReport = readSensors(rocket.IMU_I2C_Address, rocket.RTC_I2C_Address, rocket.Barometer_I2C_Address); // Read IMU/GPS, sensor array

  // powerManager(); // measure voltage and current, disable power to subsystems drawing too much.
  // handles abort secnarios if loss of power, short, or over temperature 

  // massManager(); // update vehicleManager object, tracking mass, CoM, and MMOI on 3 axes based on flight time


  // --- GNC Loop ---
  // navigation(sensorReport);  // KF or PF --> state estimation
  // guidance();                // path planning, claculate error in state to desired state
  // control();                 // Correction using control surfaces 

  // --- Events ---
  // updates rocket state and runs events Example. pastApogge== true --> Parachute.launch
  // eventManager(); // handles EVENT (status) class, checking trigger fucntions and time constraints 
  // ledManager(); // blinky led cool
  // pyroManager(); // PYRO objects, checks continuity and, if firing, checks firing durations
  // logManager(); // writes flight data to flash memory, then at end writes to mircoSD
  // timeStepUpdate(); // ensure constant framerate
}

/*
  Begins serials and checks for sensors
  build I2C address of sensors and their jacobians, and static data
  */
