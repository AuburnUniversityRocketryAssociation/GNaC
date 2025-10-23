#include <Arduino.h>
#include <Wire.h>
#include <USLI_26.h>


// put function declarations here:
int myFunction(int, int);

struct SensorReport {
    uint64_t timestamp;       // Unix timestamp in milliseconds
    float accelX, accelY, accelZ;  // IMU accelerometer
    float gyroX, gyroY, gyroZ;     // IMU gyroscope
    double latitude, longitude;    // GPS coordinates
    float altitude;                // Barometer altitude
    float pressure;                // Barometric pressure
};

bool initalizeFC();
SensorReport readSensor();


// I2C addresses 


void setup() {
  // Boot up procedure
  
  initalizeFC(); // rocket object and structure compontents
  // initializeTelemetry(); // Initalize telemetry and/or ground serial
  Serial.println(millis());
  Serial.println("Setup complete. Beginning framerate-driven procedure.");
  // setFlightComputerState(FC_ARMED);
  // setVehicleState(VEHICLE_STARTUP);
  // setControlState(CONTROL_DISABLED);
  // timeStepUpdate();
}

void loop() {
  // Main code to run every frame:

  // --- Read sensors ---
  SensorReport = readSensors(); // Read IMU/GPS, sensor array

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
  Begins serials and checks for sensors
  build I2C address of sensors and their jacobians, and static data
  */

  Serial.begin(115200);
  Serial.println("Beginning Start up Procedure");

  Wire.begin();

  return true;
}

SensorReport readSensor() {
    SensorReport report;
    report.timestamp = getTimestamp();

    int imuFile = setupI2C("/dev/i2c-1", 0x28);   // BNO055 default I2C address
    int baroFile = setupI2C("/dev/i2c-1", 0x76);  // BMP3 default I2C address

    // readIMU(imuFile, report);
    // readGPS(gpsFile, report);
    // readBarometer(baroFile, report);

    // close(imuFile);
    // close(baroFile);

    return report;
}

float calculateAltitude(float pressure) {
    // Simple formula assuming sea level pressure = 1013.25 hPa
    return 44330.0f * (1.0f - pow(pressure / 1013.25f, 0.1903f));
}