#ifndef TMP102_H_
#define TMP102_H_

#include <stdbool.h>
#include "main.h"
#include "stm32f3xx_hal_i2c.h"
//TMP102 Registers
#define TEMPATURE_REGISTER 0x0
#define CONFIG_REGISTER 0x1
#define LOW_REGISTER 0x2
#define HIGH_REGISTER 0x3
//Configuration Macros
#define SHUTDOWN 0
#define (3)

typedef struct
{
    int16_t temperature;
    bool low;
    bool high;
    HAL_StatusTypeDef hal;
} TMP102;
uint8_t TMP102_Initialize(TMP102 * tmp);
uint8_t getTempature(TMP102 * tmp);
#endif
