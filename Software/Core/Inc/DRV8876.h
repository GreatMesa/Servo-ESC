#include "main.h"
#include <stdbool.h>
typedef struct
{
    uint16_t sleepPin;
    uint16_t faultPin;
    GPIO_TypeDef * sleep;
    GPIO_TypeDef * fault;
    TIM_HandleTypeDef *tim;
    ADC_HandleTypeDef *adc;
    DAC_HandleTypeDef *dac;

    bool direction;
    float maxTorque;
    float torque;
    float speed;

    short HAL;
} DRV8876;

void DRV8876_Initialize(DRV8876 *drv, TIM_HandleTypeDef *tim, ADC_HandleTypeDef *adc, DAC_HandleTypeDef *dac, GPIO_TypeDef * sleep, uint16_t sleepPin, GPIO_TypeDef * fault, uint16_t faultPin);
void setMaxTorque(DRV8876 *drv, float torque);
void getTorque(DRV8876 *drv);