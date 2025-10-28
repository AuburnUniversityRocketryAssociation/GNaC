#include "FlightState.h"

void FlightStateMachine::begin() {
    phase = IDLE;
    lastPhase = IDLE;
}

void FlightStateMachine::update(const SensorReport& r) {
    lastPhase = phase;
    switch (phase) {
        case IDLE:
            if (r.altitude > 5.0 && r.accel[2] > 2.0) phase = ASCENT;
            break;
        case ASCENT:
            if (r.altitude < 10.0 && r.accel[2] < 1.0) phase = DESCENT;
            break;
        case DESCENT:
            if (r.altitude < 1.0 && fabs(r.accel[2]) < 0.5) phase = LANDED;
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
