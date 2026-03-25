#include "main.h"
#include "stm32_hal_legacy.h"
#include "stm32f3xx_hal_i2c.h"
#include <stdint.h>
#include "i2cslave.h"

extern I2C_HandleTypeDef hi2c2;

uint16_t registerBank[bankSize];
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
    HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    if(TransferDirection == I2C_DIRECTION_TRANSMIT)
    {
        uint8_t RxData[2];
        HAL_I2C_Slave_Sequential_Receive_IT(hi2c,RxData,1,I2C_LAST_FRAME);
    }
    if(TransferDirection == I2C_DIRECTION_RECEIVE)
    {
        
    }
}