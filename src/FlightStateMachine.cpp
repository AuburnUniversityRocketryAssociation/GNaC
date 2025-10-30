#include "FlightState.h"

void FlightStateMachine::begin() {
    phase = IDLE;
    lastPhase = IDLE;
}

void FlightStateMachine::update(const SensorReport& report) {
    /*  [TO-DO]
        trasnfer from checking sensor report to chekcing rocket state
        tune conditionals from state shifts
    */ 
     float accelMagnitude = sqrt(report.accel[0]*report.accel[0] + report.accel[1]*report.accel[1] + report.accel[2]*report.accel[2]);

    lastPhase = phase;
    switch (phase) {
        case IDLE:
            if (report.altitude > 1.0 && accelMagnitude > 2.0) phase = ASCENT;
            break;
        case ASCENT:
            if (report.altitude > 10.0 && report.accel[2] < 0) phase = DESCENT;
            break;
        case DESCENT:
            if (report.altitude < 100 && accelMagnitude < 0.5) phase = LANDED;
            timeLanded = report.timestamp_ms;
            break;
        case LANDED:
            if (report.timestamp_ms - timeLanded > 5000) phase = COMPLETE;
            break;
    }
}

const char* FlightStateMachine::getState() const {
    switch (phase) {
        case IDLE: return "IDLE";
        case ASCENT: return "ASCENT";
        case DESCENT: return "DESCENT";
        case LANDED: return "LANDED";
        case COMPLETE: return "COMPLETE";
        default: return "UNKNOWN";
    }
}

bool FlightStateMachine::inFlight() const {
    return phase == ASCENT || phase == DESCENT;
}

bool FlightStateMachine::justLanded() {
    return lastPhase != LANDED && phase == LANDED;
}

bool FlightStateMachine::justLaunched() {
    return lastPhase == IDLE && phase == ASCENT;
}

bool FlightStateMachine::justReachedApogee() {
    return lastPhase == ASCENT && phase == DESCENT;
}
