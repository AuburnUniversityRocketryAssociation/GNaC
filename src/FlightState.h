#pragma once
#include "Sensor/SensorReport.h"

enum FlightPhase { IDLE, ASCENT, DESCENT, LANDED, COMPLETE };

class FlightStateMachine {
public:
    //Class values
    uint32_t timeLanded;
    uint32_t timeLaunched;
    uint32_t timeApogee;
    float maxAltitude;
    float beigningAltitude;
    float lastAltitude;
    float accel_Magnitude_filtered;
    String event;

    // Methods 
    void begin();
    void update(const SensorReport& report);
    const char* getState() const;
    bool inFlight() const;
    bool justLanded();
    bool justLaunched();
    bool justReachedApogee();

private:
    const float Launch_ACCEL_Threshould = 9.8 * 10;  // converts from G force to m/s^2  = ( 9.8 * Number of Gs )
    FlightPhase phase = IDLE;
    FlightPhase lastPhase = IDLE;
    float lowPassFilter(float prior, float measurement, float alpha);
};