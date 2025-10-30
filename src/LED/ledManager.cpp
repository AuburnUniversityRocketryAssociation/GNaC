#include "ledManager.h"
#include <Arduino.h>

void ledManager(String fsmState) {
    // hopefully eventually a way to visually show error codes if not USB not connected
    
    if (fsmState == "IDLE") {
        if(int(millis()/1000) % 2 == 0) {
                digitalWrite(LED_PIN, HIGH);  // LED ON during even seconds
        } else {
            digitalWrite(LED_PIN, LOW);   // LED OFF during odd seconds
        }
    } else if (fsmState == "ASCENT") {
        if(int(millis()/100) % 2 == 0) {
                digitalWrite(LED_PIN, HIGH);  // LED ON during even seconds
        } else {
            digitalWrite(LED_PIN, LOW);   // LED OFF during odd seconds
        }
    } else if (fsmState == "DESCENT") {
        digitalWrite(LED_PIN, LOW);   // LED off during descent 
    } else if (fsmState == "LANDED") {
        // LED on when safe to remove SD Card
        digitalWrite(LED_PIN, HIGH);    
    } else {
        if(int(millis()/1000) % 3 == 0) {
                digitalWrite(LED_PIN, HIGH);  // LED ON during even seconds
        } else {
            digitalWrite(LED_PIN, LOW);   // LED OFF during odd seconds
        }
    }
}