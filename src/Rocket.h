#ifndef Rocket_H
#define Rocket_H

#include "Sensors/SensorReport.h"
#include "Rocket.h"
#include "State.h"
#include "Sensors/readSensors.h"




class Rocket {
private:
public:
    State state;
    uint32_t lastLogTime;
    bool isLanded    = false;
    bool GND_link    = false; // is connected to USB
    float CPU_Temp;
    // int speed;
    // int G_force;

    // Default constructor
    Rocket(); 

    // Methods
    void init(State initialState);

    void init();

    void setLogicState(logicState lState);
};

#endif