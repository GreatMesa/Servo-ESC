#ifndef i2cslave_H_
#define i2cslave_H_
#include "i2cslave.h"
#include "stm32f3xx_hal_i2c.h"
#include "INA236.h"
#include "TMP102.h"
#include "DRV8876.h"
#include "pid.h"

typedef struct
{
    I2C_HandleTypeDef *I2Chandle;
    uint16_t registerBank[16];
    HAL_StatusTypeDef hal;
} i2cslave;

void I2CSlave_Initialize();
void I2CSlave_Update(INA236 * ina, TMP102 * tmp, DRV8876 * drv, PID * pid);
#endif