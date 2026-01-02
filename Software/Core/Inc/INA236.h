#ifndef INA236_H_
#define INA236_H_

#include "main.h"
#include "stm32f3xx_hal_i2c.h"

#define INA236_I2C_ADDRESS (0x40 << 1)
#define INA236_I2C_HANDLE hi2c1

#define CONFIG_REGISTER 0x00
#define SHUNT_VOLTAGE_REGISTER 0x01
#define VOLTAGE_REGISTER 0x02
#define POWER_REGISTER 0x03
#define CURRENT_REGISTER 0x04
#define CALLIBRATION_REGISTER 0x05
#define MASK_ENABLE_REGISTER 0x06
#define ALERT_REGISTER 0x07
#define DEVICE_ID 0x3F

#define INA236_CONFIG_RST 0x0
#define INA236_CONFIG_ADC_RANGE 0x1
#define INA236_CONFIG_AVG 0x0
#define INA236_CONFIG_VBUSCT 0x4
#define INA236_CONFIG_VSHCT 0x4
#define INA236_CONFIG_MODE 0x7

#define INA236_MAX_CURRENT 1
#define INA236_SHUNT_RESISTANCE 0.01

typedef struct
{
    I2C_HandleTypeDef *I2Chandle;
    GPIO_TypeDef *interrupt;
    float current;
    float power;
    float voltage;
    uint16_t config;
    uint16_t callibration;
    HAL_StatusTypeDef hal;
} INA236;

extern I2C_HandleTypeDef INA236_I2C_HANDLE;

//Functions
bool  getConfig();
bool  getCallibration();
bool INA236_Initialize(INA236 *ina236, I2C_HandleTypeDef *I2Chandle, GPIO_TypeDef *interrupt);
void getCurrent(INA236 *ina236);
void getVoltage(INA236 *ina236);
void getPower(INA236 *ina236);
#endif
