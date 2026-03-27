#ifndef i2cslave_H_
#define i2cslave_H_
#include "stm32f3xx_hal_i2c.h"
#define bankSize 16

typedef struct
{
    I2C_HandleTypeDef *I2Chandle;
    uint16_t registerBank[bankSize];
    HAL_StatusTypeDef hal;
} i2cslave;

void I2CSlave_Initialize();
void 
#endif