#include "pid.h"
#include <stdbool.h>

void PID_Initialize(PID * pid,float iKp, float iKI, float iKD, float ikV, float ikA)
{
    pid->Kp = iKp;
    pid->Ki = iKI;
    pid->Kd = iKD;
    pid->kV = ikV;
    pid->kA = ikA;
}

void PID_Step(PID * pid, int16_t wPos, int16_t cPos, int16_t wVel, int16_t cVel, int16_t wAccel, int16_t cAccel)
{
    pid->error = (wPos - cPos);
    pid->totalError = pid->totalError + pid->error;
    
    if(pid->maxError > pid->error)
    {
        /* Steady State Reached */
        pid->totalError = 0;
        pid->settled = true;
        pid->power = 0;
    }
    else
    {
        /* Initiate PID Step */
        pid->power = (pid->Ki * pid->error) + (pid->Ki * pid->totalError) + (pid->Ki * pid->prevError) + (pid->kV * (wVel - cVel)) + (pid->kA * (wAccel - cVel));
        pid->prevError = pid->error;
    }
}