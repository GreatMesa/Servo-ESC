#include "DRV8876.h"
#include <stdint.h>
void DRV8876_Initialize(DRV8876 *drv, TIM_HandleTypeDef *tim, ADC_HandleTypeDef *adc, DAC_HandleTypeDef *dac, GPIO_TypeDef * sleep, uint16_t sleepPin, GPIO_TypeDef * fault, uint16_t faultPin)
{
    drv->sleep = sleep;
    drv->fault = fault;
    drv->sleepPin = sleepPin;
    drv->faultPin = faultPin;
    drv->tim = tim;
    drv->adc = adc;
    drv->dac = dac;
    drv->direction = false;
    drv->maxTorque = 0.0f;
    drv->torque = 0.0f;
    drv->speed = 0.0f;

    HAL_GPIO_WritePin(sleep, sleepPin, true);
}

void setVelocity(DRV8876 *drv, float speed, bool direction)
{
    drv->speed = speed;
    drv->direction = direction;
}

void setMaxTorque(DRV8876 *drv, float maxTorque)
{
    drv->maxTorque = maxTorque;
}

void getTorque(DRV8876 *drv)
{
    if (HAL_ADC_Start(drv->adc) == HAL_OK)
    {
        if (HAL_ADC_PollForConversion(drv->adc, 10) == HAL_OK)
        {
            drv->torque = (float)HAL_ADC_GetValue(drv->adc);
        }
        HAL_ADC_Stop(drv->adc);
    }
}