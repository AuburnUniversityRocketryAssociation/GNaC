#ifndef LOGICSTATE_H
#define LOGICSTATE_H

enum logicState{
    UNARMED,            // low power state, idling
    ARMED,              // launch imminent
    BURNING,            // from launch to burnout
    COLD,               // motor burned out but still upward velocity
    APPOGEED,           // past appogee
    DEPLOYING_CHUTES,   // until deacceleration is detected
    CHUTES_DEPLOYED,
    LANDED,
    DRILLING, 
    LOW_POWER,          // low power detected, shuting down
    DEAD                // mission complete, power down
};
#endif