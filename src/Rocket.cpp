#include "Rocket.h"
#include "ULSI26.h"

// Constructor
Rocket::Rocket(){};

// Methods
void Rocket::init(State initialState){
    this-> state        = initialState;
    this ->lastLogTime  = 0; 
}

void Rocket::init(){
    state.time = millis();
    state.positionX= 0;
    state.positionY= 0;
    state.positionZ= 0;
    state.velocityX= 0;
    state.velocityY= 0;
    state.velocityZ= 0; 
    state.accelX= 0;
    state.accelY= 0;
    state.accelZ= 0;     
    state.roll        = 0;
    state.pitch       = 0;
    state.yaw         = 0;
    state.latitude    = 0;
    state.longitude   = 0;
    state.altitude    = 0;
    state.logic       = UNARMED;
}

void Rocket::setLogicState(logicState lState){
    rocket.state.logic = lState;
};