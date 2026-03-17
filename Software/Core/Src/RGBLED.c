#include "RGBLED.h"
#include <DRV8876.h>
void RGBLED_Initialize(RGBLED * rgb, TIM_HandleTypeDef * tim)
{
    rgb->tim = tim;
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, (0));
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, (0));
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, (0));
}
void setColor(RGBLED * rgb, int state)
{
    TIM_HandleTypeDef * tim = rgb->tim;
    if(state == SLEEP){
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, 0x22);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, 0x22);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, 0x22);
    }
    else if (state == FORWARD)
    {
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, 0x00);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, 0x00);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, 0x22);
    }
    else if (state == REVERSE)
    {
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, 0x22);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, 0x00);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, 0x00);
    }
    else if(state == BRAKE){
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, 0x00);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, 0x22);
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, 0x00);
    }
}