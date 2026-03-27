#ifndef pid_H_
#include <stdint.h>

typdef struct
{
    /* PID Constants */
    uint8_t Kp;
    uint8_t Ki;
    uint8_t Kd;

    /* PID Limits */
    uint16_t min;
    uint16_t max;

    /* PID Main Terms*/
    uint16_t power;
    uint16_t error;
    uint16_t totalError;
    uint16_t prevError;

    /* Feedfoard Constants */
    uint16_t kV;
    uint16_t kA;
} pid ;

void PID_Initialize();
uint16_t PID_Step();

#endif