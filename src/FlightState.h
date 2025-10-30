#pragma once
#include "Sensor/SensorReport.h"

enum FlightPhase { IDLE, ASCENT, DESCENT, LANDED, COMPLETE };

class FlightStateMachine {
public:
    //Class values
    uint32_t timeLanded;

    // Methods 
    void begin();
    void update(const SensorReport& r);
    const char* getState() const;
    bool inFlight() const;
    bool justLanded();
    bool justLaunched();
    bool justReachedApogee();

private:
    FlightPhase phase = IDLE;
    FlightPhase lastPhase = IDLE;
};