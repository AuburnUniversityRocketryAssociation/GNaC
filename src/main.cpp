#include <Arduino.h>
// #include <USLI_26.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // Boot up procedure
  
  initalizeFC(); // rocket object and structure compontents
  // initializeTelemetry(); // Initalize telemetry and/or ground serial

  Serial.println("Setup complete. Beginning framerate-driven procedure.");
  // setFlightComputerState(FC_ARMED);
  // setVehicleState(VEHICLE_STARTUP);
  // setControlState(CONTROL_DISABLED);
  // timeStepUpdate();
}

void loop() {
  // Main code to run every frame:

  // --- Read sensors ---
  sensorReport = readSensors(); // Read IMU/GPS and feed into navigation library
  Serial.println(sensorReport);

  // powerManager(); // measure voltage and current, disable power to subsystems drawing too much.
  // handles abort secnarios if loss of power, short, or over temperature 

  // massManager(); // update vehicleManager object, tracking mass, CoM, and MMOI on 3 axes based on flight time


  // --- GNC Loop ---
  // navigation(sensorReport); // in (positon, velocity, attitude) --> KF or PF --> state estimation
  // guidance(); // path planning, claculate error in state to desired state
  // control(); // Correction using control surfaces 

  // telemetryUpdate(); // 

  // --- Events ---
  // updates rocket state and runs events Example. pastApogge== true --> Parachute.launch
  // eventManager(); // handles EVENT (status) class, checking trigger fucntions and time constraints 
  // ledManager(); // blinky led cool
  // pyroManager(); // PYRO objects, checks continuity and, if firing, checks firing durations
  // logManager(); // writes flight data to flash memory, then at end writes to mircoSD
  // timeStepUpdate(); // ensure constant framerate
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

bool initalizeFC(){
  /*
  Begins serials and initalizes stuff, you know
  */

  Serial.begin(115200);
  Serial.println("Beginning Start up Procedure");

  Wire.begin

  return true;
}