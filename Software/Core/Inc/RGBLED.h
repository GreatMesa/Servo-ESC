#ifndef RGBLED_H_
#define RGBLED_H_

#include "main.h"
#include <stdint.h>
typedef struct 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    int state;
    TIM_HandleTypeDef * tim;
} RGBLED;
void RGBLED_Initialize(RGBLED * rgb, TIM_HandleTypeDef * tim);
void setColor(RGBLED * rgb, int state);
#endif