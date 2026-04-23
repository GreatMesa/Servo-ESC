#include "main.h"
#include <stdbool.h>
#include <stdint.h>

enum DriveState
{
    SLEEP = 0,
    COAST = 1,
    REVERSE = 2,
    FORWARD = 3,
    BRAKE = 4
};

typedef struct
{
    uint16_t sleepPin;
    uint16_t faultPin;
    GPIO_TypeDef * sleep;
    GPIO_TypeDef * fault;
    TIM_HandleTypeDef *tim;
    ADC_HandleTypeDef *adc;
    DAC_HandleTypeDef *dac;
    int state;
    uint16_t speed;
    bool direction;
    float maxAmps;
    float torque;
    HAL_StatusTypeDef HAL;
} DRV8876;

void DRV8876_Initialize(DRV8876 *drv, TIM_HandleTypeDef *tim, ADC_HandleTypeDef *adc, DAC_HandleTypeDef *dac, GPIO_TypeDef * sleep, uint16_t sleepPin, GPIO_TypeDef * fault, uint16_t faultPin);
void setMaxAmps(DRV8876 *drv, float torque);
void getTorque(DRV8876 *drv);
void setVelocity(DRV8876 *drv, int32_t velocity);
void setDriveState(DRV8876 *drv, int state);
void setDRV8876(DRV8876 *drv, float torque, float speed, bool diretion, int state);