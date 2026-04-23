#ifndef PID_H_
#define PID_H_

#include "main.h"
#include "stdbool.h"
typedef struct
{
    /* PID Constants */
    float Kp;
    float Ki;
    float Kd;


    /* PID Main Terms*/
    int16_t power;
    int16_t error;
    int16_t totalError;
    int16_t prevError;
    int16_t maxError;
    bool settled;

    /* Feedfoard Constants */
    float kV;
    float kA;
} PID;

void PID_Initialize(PID * pid,float iKp, float iKI, float iKD,  float ikV, float ikA);
void PID_Step(PID * pid, int16_t wPos, int16_t cPos, int16_t wVel, int16_t cVel, int16_t wAccel, int16_t cAccel);

#endif