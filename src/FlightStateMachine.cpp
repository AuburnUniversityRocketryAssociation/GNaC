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
            if (1000 < report.timestamp_ms && report.timestamp_ms < 2000){
                beigningAltitude = report.altitude;
            }
            if (accelMagnitude > 5.0) {
                phase = ASCENT;
                Serial.println("we have lift off");
                timeLaunched = report.timestamp_ms;
            }
            break;
        case ASCENT:
            if (report.accel[2] < 0 && timeLaunched + 5000 < report.timestamp_ms) {
                phase = DESCENT;
                Serial.println("Apogee reached");
                timeApogee = report.timestamp_ms;
                maxAltitude = report.altitude;
            }
            break;
        case DESCENT:
            if (report.altitude - beigningAltitude < 100 && accelMagnitude < 1 && timeApogee + 5000 < report.timestamp_ms) {
                phase = LANDED;
                timeLanded = report.timestamp_ms;
                Serial.println("Vehcile landed");
            }
            break;
        case LANDED:
            if (report.timestamp_ms - timeLanded > 5000) {
                phase = COMPLETE;
                Serial.println("game over");
            }
            break;
        case COMPLETE:
            // Do nothing, final state
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
