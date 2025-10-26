#include "Rocket.h"
#include "ULSI26.h"

// Constructor
Rocket::Rocket(){};

// Methods
void Rocket::init(State initialState){
    this-> state        = initialState;
    this ->lastLogTime  = 0;    
}

void setLogicState(logicState lState){
    rocket.state.logic = lState;
};