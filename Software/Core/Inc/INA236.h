#ifndef INA236_H_
#define INA236_H_

#include "main.h"
#include "stm32f3xx_hal_i2c.h"
#include <stdint.h>
#include <stdbool.h>

#define INA236_I2C_ADDRESS (0b01000000 << 1)
#define INA236_I2C_HANDLE hi2c1

/*
    INA236 Register Map
    - Register 0x00 -> (Configuration Register) Register used to configure the INA236. (Read / Write)
    - Register 0x01 -> (Shunt Voltage Register) 16-bit 2's complement value for the shunt resistor voltage (Volts). (Read only)
    - Register 0x02 -> (Bus Voltage Register) 16-bit 2's complement value for the bus voltage (Volts). (Read only)
    - Register 0x03 -> (Power Register) 16-bit 2's complement value for the power of the system (Watts). (Read only)
    - Register 0x04 -> (Current Register) 16-bit 2's complement value for the current of the system (Amperes). (Read only)
    - Register 0x05 -> (Callibration Register) Register that stores the shunt resistor value connected to the INA236 (Ohms). (Read / Write)
    - Register 0x06 -> (Mask-Enable Register) Register that configures the alert pin of the INA236. (Read / Write)
    - Register 0x07 -> (Alert-Limit Register) Register used to configure a value for alert pinging. (Read / Write)
    - Register 0x3E -> (Manufacturer ID) Reads back TI in ASCII (8473). (Read only)
    - Register 0x3E -> (Device ID) Stores back the device identification bits for device communication verification. (Read only)
*/
#define INA_CONFIG_REGISTER 0x00
#define SHUNT_VOLTAGE_REGISTER 0x01
#define VOLTAGE_REGISTER 0x02
#define POWER_REGISTER 0x03
#define CURRENT_REGISTER 0x04
#define CALLIBRATION_REGISTER 0x05
#define MASK_ENABLE_REGISTER 0x06
#define ALERT_REGISTER 0x07
#define DEVICE_ID 0x3F

/*
    INA236 Configuration Register Map (Use INA236 Datasheet for bit configuration lookup table)
    - Bits 12 (ADCRANGE) Bit to determine the configuration of 
    - Bits 11 - 9 -> (AVG) 3 bit configuration to determine the number of ADC conversions to be averaged, register values are done after averages (configured for 1 average).
    - Bits 8 - 6 -> (VBUSCT) 3 bit configuration to determine the conversion time for the bus voltage register (Configured for 1.1 milliseconds).
    - Bits 5 - 3 -> (VSHCT) 3 bit configurattion to determine the conversion time for the shunt voltage register (Configured for 1.1 milliseconds).
    - Bits 2 - 0 -> (MODE) 3 bit configuration used to determine the operating mode of the INA236 (Configured to  Continuous Shunt and Bus voltage).
*/
#define INA236_CONFIG_RST 0b0
#define INA236_CONFIG_ADC_RANGE 0b1
#define INA236_CONFIG_AVG 0b0
#define INA236_CONFIG_VBUSCT 0b100
#define INA236_CONFIG_VSHCT 0b100
#define INA236_CONFIG_MODE 0b111

#define INA236_MAX_CURRENT 1
#define INA236_SHUNT_RESISTANCE 0.01

typedef struct
{
    I2C_HandleTypeDef *I2Chandle;
    GPIO_TypeDef *interrupt;
    
    float current;
    float power;
    float voltage;
    /*Raw variables used for data transfer*/
    int16_t raw_current;
    int16_t raw_voltage;
    int16_t raw_power;
    uint16_t config;
    uint16_t callibration;
    HAL_StatusTypeDef hal;
} INA236;

extern I2C_HandleTypeDef INA236_I2C_HANDLE;

//Functions
uint16_t  INA236_Config();
uint16_t  INA236_Callibration();
HAL_StatusTypeDef INA236_Initialize(INA236 *ina236, I2C_HandleTypeDef *I2Chandle, GPIO_TypeDef *interrupt);
void getCurrent(INA236 *ina236);
void getVoltage(INA236 *ina236);
void getPower(INA236 *ina236);
void readINA236(INA236 *ina236);
#endif
