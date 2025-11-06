#include "FlightState.h"

void FlightStateMachine::begin() {
    phase = IDLE;
    lastPhase = IDLE;
}

void FlightStateMachine::update(const SensorReport& report) {

    // ideally based off rocket state and not raw sensor readings
    float accelMagnitude = sqrt(report.accel[0]*report.accel[0] + report.accel[1]*report.accel[1] + report.accel[2]*report.accel[2]);

    lastPhase = phase;
    switch (phase) {
        case IDLE:
            if (1000 < report.timestamp_ms && report.timestamp_ms < 2000){
                beigningAltitude = lowPassFilter(beigningAltitude, report.altitude, 0.7);
            }
            if (accelMagnitude > Launch_ACCEL_Threshould) {
                phase = ASCENT;
                Serial.println("we have lift off");
                timeLaunched = millis();
                
                event = String(timeLaunched) + "\t Vehicle launched at UTC: " + report.Date; 
            }
            break;

        case ASCENT:
            
            lastAltitude = lowPassFilter(lastAltitude, report.altitude, 0.3);

            if (timeLaunched + 2000 < report.timestamp_ms && maxAltitude - lastAltitude > 0) {
                phase = DESCENT;
                Serial.println("Apogee reached");
                timeApogee = millis();
                maxAltitude = lastAltitude;

                event = String(millis()) + "\t Apogee reached of " + String(maxAltitude); 
            }
            break;

        case DESCENT:
        
            accel_Magnitude_filtered = lowPassFilter(accel_Magnitude_filtered, accelMagnitude, 0.8);

            if (report.altitude - beigningAltitude < 100 && accel_Magnitude_filtered < 9.8 && timeApogee + 5000 < report.timestamp_ms) {
                phase = LANDED;
                timeLanded = millis();
                Serial.println("Vehcile landed");

                event = String(timeLaunched) + "\t Touchdown at UTC: " + report.Date; 
            }
            break;

        case LANDED:
            if (report.timestamp_ms - timeLanded > 5000) {
                phase = COMPLETE;
                Serial.println("game over");

                event = String(timeLaunched) + "\t Mission complete, stopping logging"; 
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

/*
Basic low pass filter until state estimation is establsihed

@param alpha is the emphasis on the prior state belonging to range [0,1] where 0.7 is high smoothing and more lag
*/ 
float FlightStateMachine::lowPassFilter(float prior, float measurement, float alpha){
    return alpha * prior + (1-alpha) * measurement; 
}