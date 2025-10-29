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

    lastPhase = phase;
    switch (phase) {
        case IDLE:
            if (report.altitude > 1.0 && report.accel[2] > 2.0) phase = ASCENT;
            break;
        case ASCENT:
            if (report.altitude > 10.0 && report.accel[2] < 0) phase = DESCENT;
            break;
        case DESCENT:
            if (report.altitude < 100 && fabs(report.accel[2]) < 0.5) phase = LANDED;
            break;
        case LANDED:
            break;
    }
}

const char* FlightStateMachine::getState() const {
    switch (phase) {
        case IDLE: return "IDLE";
        case ASCENT: return "ASCENT";
        case DESCENT: return "DESCENT";
        case LANDED: return "LANDED";
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
