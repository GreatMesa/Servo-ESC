#include "mt6701.h"

HAL_StatusTypeDef MT6701_Initialize(MT6701 * encoder, I2C_HandleTypeDef *I2Chandle)
{
    encoder->I2Chandle = I2Chandle;
    encoder->raw_position = 0;
    encoder->position = 0;
    encoder->raw_rpm = 0;
    encoder->rpm = 0;
    return encoder->hal;
}

HAL_StatusTypeDef MT6701_Read(MT6701 *encoder)
{
    uint8_t rxBuf[1];
    HAL_I2C_Mem_Read(encoder->I2Chandle, MT6701_I2C_ADRESS, REG_ANGLE_H, I2C_MEMADD_SIZE_8BIT, rxBuf, 1, 100);
    encoder->raw_position = rxBuf[0] << 8;
    HAL_I2C_Mem_Read(encoder->I2Chandle, MT6701_I2C_ADRESS, REG_ANGLE_L, I2C_MEMADD_SIZE_8BIT, rxBuf, 1, 100);
    encoder->raw_position += rxBuf[0];
}