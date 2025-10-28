#pragma once
#include "SensorReport.h"

enum FlightPhase { IDLE, ASCENT, DESCENT, LANDED };

class FlightStateMachine {
public:
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