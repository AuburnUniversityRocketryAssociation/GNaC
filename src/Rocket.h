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

    // Default constructor
    Rocket(); 

    // Methods
    void init(State initialState);

    void setLogicState(logicState lState);
};

#endif