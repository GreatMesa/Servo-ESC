#include "DRV8876.h"
#include "main.h"
#include "stm32f3xx_hal_dac.h"
#include "stm32f3xx_hal_gpio.h"
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
    drv->maxAmps = 0.0f;
    drv->torque = 0.0f;
    drv->speed = 65535;
    drv->state = BRAKE;
    
    HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 1);
    HAL_TIM_PWM_Start(drv->tim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(drv->tim, TIM_CHANNEL_2);
    HAL_DAC_Start(drv->dac, DAC_CHANNEL_1);
    drv->HAL = HAL_DAC_SetValue(drv->dac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 4095
    );
    setDriveState(drv, drv->state);
}

void setVelocity(DRV8876 *drv, float speed, bool direction)
{
    drv->speed = speed;
    drv->direction = direction;
}

void setMaxAmps(DRV8876 *drv, float maxAmps)
{
    drv->maxAmps = maxAmps;
    uint16_t amps = (uint16_t) maxAmps * 10240;
    drv->HAL = HAL_DAC_SetValue(drv->dac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, amps);
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

void setDriveState(DRV8876 *drv, int state)
{
    drv->state = state;
    if(state == SLEEP)
    {
        HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 0);
    }
    else if(state == COAST)
    {
        //Slows down the motor with a gradual decent.
        HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 1);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_2, 0);
    }
    else if(state == REVERSE)
    {
        /*
        
        */
        HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 1);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_2, drv->speed);
    }
    else if(state == FORWARD)
    {
        HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 1);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_1, drv->speed);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_2, 0);
    }
    else if(state == BRAKE)
    {
        HAL_GPIO_WritePin(HBRIDGE_SLEEP_GPIO_Port, HBRIDGE_SLEEP_Pin, 1);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_1, 65535);
        __HAL_TIM_SET_COMPARE(drv->tim, TIM_CHANNEL_2, 65535);
    }
}
