#include "ledManager.h"
#include <Arduino.h>

void ledManager(){
    // hopefully eventually a way to visually show error codes if not USB not connected
    
    if(int(millis()/1000) % 2 == 0) {
        digitalWrite(LED_PIN, HIGH);  // LED ON during even seconds
    } else {
        digitalWrite(LED_PIN, LOW);   // LED OFF during odd seconds
    }
}