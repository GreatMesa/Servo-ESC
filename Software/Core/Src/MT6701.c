#include "mt6701.h"

HAL_StatusTypeDef MT6701_Initialize(MT6701 * encoder, I2C_HandleTypeDef *I2Chandle)
{
    encoder->I2Chandle = I2Chandle;
    
    return encoder->hal;
}
