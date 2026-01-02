#include "INA236.h"
#include "stm32f3xx_hal_i2c.h"
#include <stdint.h>

bool getConfig()
{
    return ((INA236_CONFIG_RST << 15) |
            (INA236_CONFIG_ADC_RANGE << 12) | 
            (INA236_CONFIG_AVG << 9) |
            (INA236_CONFIG_VBUSCT << 6) |
            (INA236_CONFIG_VSHCT << 3) |
            INA236_CONFIG_MODE);
}

bool getCallibration()
{
    float current_lsb = (INA236_MAX_CURRENT / 32768.0f);
    uint16_t SHUNT_CAL = ((0.00512f) / ((INA236_SHUNT_RESISTANCE) * (current_lsb))) / 4;
    return SHUNT_CAL;
}


bool INA236_Initialize(INA236 *ina236, I2C_HandleTypeDef *I2Chandle, GPIO_TypeDef *interrupt)
{
    //Configuring Starting Values
    ina236->I2Chandle = I2Chandle;
    ina236->config = getConfig();
    ina236->callibration = getCallibration();
    ina236->current = 0.0f;
    ina236->power = 0.0f;
    ina236->voltage = 0.0f;
    uint8_t txBuf[2];
    //Tramnsmitting Configuration Register
    txBuf[0] = ((ina236->config >> 8) & 0xFF); txBuf[1] = (ina236->config & 0xFF);
    ina236->hal = HAL_I2C_Mem_Write(ina236->I2Chandle, INA236_I2C_ADDRESS,CONFIG_REGISTER,I2C_MEMADD_SIZE_8BIT, txBuf, 2, 100);
    if(ina236->hal != 1){return 0;}
    //Transmitting Callibration Register
    txBuf[0] = ((ina236->callibration >> 8) & 0xFF); txBuf[1] = (ina236->callibration & 0xFF);
    HAL_I2C_Mem_Write(ina236->I2Chandle, INA236_I2C_ADDRESS,CALLIBRATION_REGISTER,I2C_MEMADD_SIZE_8BIT, txBuf, 2, 100);
    if(ina236->hal != 1){return 0;}
    return 1;
}

void getCurrent(INA236 *ina236)
{
    uint8_t rxBuf[2];
    HAL_I2C_Mem_Read(ina236->I2Chandle, INA236_I2C_ADDRESS, CURRENT_REGISTER, I2C_MEMADD_SIZE_8BIT, rxBuf, 2, 100);
    int16_t raw_current = ((rxBuf[0] << 8) | (rxBuf[1]));
    float current_lsb = (INA236_MAX_CURRENT / 32768.0f);
    ina236->current = current_lsb * raw_current;
}

void getVoltage(INA236 *ina236)
{
    uint8_t rxBuf[2];
    HAL_I2C_Mem_Read(ina236->I2Chandle, INA236_I2C_ADDRESS, VOLTAGE_REGISTER, I2C_MEMADD_SIZE_8BIT, rxBuf, 2, 100);
    int16_t raw_voltage = ((rxBuf[0] << 8) | (rxBuf[1]));
    ina236->voltage = raw_voltage * 0.0016f;
}

void getPower(INA236 *ina236)
{
    uint8_t rxBuf[2];
    HAL_I2C_Mem_Read(ina236->I2Chandle, INA236_I2C_ADDRESS, POWER_REGISTER, I2C_MEMADD_SIZE_8BIT, rxBuf, 2, 100);
    int16_t raw_power = ((rxBuf[0] << 8) | (rxBuf[1]));
    float current_lsb = (INA236_MAX_CURRENT / 32768.0f);
    ina236->power = raw_power * current_lsb * 32;
}