#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <Arduino.h>
#include <string>

const int LED_PIN = 13;

void ledManager(String fsmState);
#endif