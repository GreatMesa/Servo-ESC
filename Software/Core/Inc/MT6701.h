#ifndef MT6701_H
#define MT6701_H

#include "main.h"
#include "stm32f3xx_hal_i2c.h"
#include <stdint.h>

/*
    MT6701 Register Map
    - 0x03 (Angle Register [13:6]) Reads the highest 8 bits of the 14 bit angle
   measurment.
    - 0x04 (Angle Register [5:0]) Reads the lower 6 bits of the 14 bit angle
   measurment.
*/
#define REG_ANGLE_H 0x03
#define REG_ANGLE_L 0x04

/* I2C Address */
#define MT6701_I2C_ADRESS 0x06

/* 14-bit resolution */
#define MT6701_RESOLUTION 16384.0f
#define MT6701_DEGREES 360.0f

typedef struct {
  I2C_HandleTypeDef *I2Chandle;
  uint16_t raw_position;
  float position;
  float prevPosition;
  float rpm;
  float prevRpm;
  HAL_StatusTypeDef hal;
} MT6701;

HAL_StatusTypeDef MT6701_Initialize(MT6701 *encoder,
                                    I2C_HandleTypeDef *I2Chandle);
HAL_StatusTypeDef MT6701_Read(MT6701 *encoder);
void getRPM(MT6701 *encoder, int delay, float alpha);
#endif /* MT6701_H */
