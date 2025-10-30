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

}

void loop() {
  // Main code to run every frame:
  bool GND_link;
  if(Serial){ 
    GND_link = true;
  }
  
  // --- Read sensors ---
  
  
  SensorReport Sensor_report = sensors.read();   // Read IMU/GPS, sensor array
  
  // potential GPS: u-blox NEO-M8N, ZED-F9P ZOE-M8Q
  // potential LoRa: RFM95, REYAX RYLR896
  
  uint32_t deltaTime = (millis() - lastTime);
  lastTime = Sensor_report.timestamp_ms;
  
  //    Poor man's IMU filter
  for (int i = 0; i < 3; ++i) {
      if (std::fabs(Sensor_report.accel[i]) < 0.4) {
          Sensor_report.accel[i] = 0.0;
      }
  }


  // veleocity
  rocket.velocity[0] = 0.9 * rocket.velocity[0] + (rocket.accel[0] * deltaTime)/1000; 
  rocket.velocity[1] = 0.9 * rocket.velocity[1] + (rocket.accel[1] * deltaTime)/1000;     // [x, y, z]
  rocket.velocity[2] = 0.9 * rocket.velocity[2] +(rocket.accel[2] * deltaTime)/1000;
  
  // positon
  rocket.position[0] += (rocket.velocity[0] * deltaTime)/1000; 
  rocket.position[1] += (rocket.velocity[1] * deltaTime)/1000;      // [x, y, z]
  rocket.position[2] += (rocket.velocity[2] * deltaTime)/1000;
  
  // accleration update
  rocket.accel[0] = Sensor_report.accel[0];
  rocket.accel[1] = Sensor_report.accel[1];     // [x, y, z]
  rocket.accel[2] = Sensor_report.accel[2];
  
  rocket.orientation[0] = Sensor_report.gyro[0];
  rocket.orientation[1] = Sensor_report.gyro[1];   // euler angles (yaw pitch roll)
  rocket.orientation[2] = Sensor_report.gyro[2];
  
  rocket.report = Sensor_report;    // last sensor report
  rocket.date = Sensor_report.Date;          // UTC ish date
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
      Serial.println("we have lift off");
    }
    if (input == 'a'){          // trigger on 'a' to apogee
      Sensor_report.altitude = 20;
      Sensor_report.accel[2] = -1;
      Serial.println("new highscore");
    }
    if (input == 'c'){        // trigger on 'c' to crash landl
      Sensor_report.altitude = 2;
      Sensor_report.accel[2] = 0;
      Serial.println("game over");
    }
  }
  
  
  fsm.update(Sensor_report);
  // eventManager(); // handles EVENT (status) class,  Example. pastApogge == true --> Rocket.launchParachute()
  
  ledManager(fsm.getState()); // blinky led cool
  
  // powerManager();  // measure voltage and current, disable power to subsystems drawing too much.
                      // handles abort secnarios if loss of power, short, or over temperature 
  
  logger.update(rocket, GND_link, fsm.getState()); // writes flight data to flash memory, then at end writes to mircoSD
  
  // massManager(); // update vehicleManager object, tracking mass, CoM, and MMOI on 3 axes based on flight time

  // timeStepUpdate(); // ensure constant framerate
}