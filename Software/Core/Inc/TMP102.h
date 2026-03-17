#ifndef TMP102_H_
#define TMP102_H_

#include <stdbool.h>
#include "main.h"
#include "stm32f3xx_hal_i2c.h"

#define TMP102_ADDR             (0x48 << 1)

/* TMP102 Register Pointers */
#define TEMPATURE_REGISTER      0x00
#define TMP_CONFIG_REGISTER     0x01
#define LOW_REGISTER            0x02
#define HIGH_REGISTER           0x03


#define SHUTDOWN                0
#define THERMOSTAT              0
#define POLARITY                0
#define FAULT                   0
#define CONV_RATE               2
#define EXT_MODE                0

#define TMP102_TIMEOUT          100
#define TMP102_RESOLUTION       0.0625f    

typedef struct
{
    I2C_HandleTypeDef  *I2Chandle;
    int16_t raw_temp;
    float tempature;
    bool high;
    bool low;
    HAL_StatusTypeDef   hal;
} TMP102;

uint8_t getTMPConfig();
bool    TMP102_Initialize(TMP102 *tmp102, I2C_HandleTypeDef *I2Chandle, GPIO_TypeDef *interrupt);
void    readTempature(TMP102 *tmp102);

#endif /* TMP102_H_ */