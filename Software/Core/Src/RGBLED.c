#include "RGBLED.h"
void RGBLED_Initialize(RGBLED * rgb, TIM_HandleTypeDef * tim)
{
    rgb->tim = tim;
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(tim, TIM_CHANNEL_4);
}
void setColor(RGBLED * rgb, uint8_t red, uint8_t green, uint8_t blue)
{
    TIM_HandleTypeDef * tim = rgb->tim;
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_1, (red << 8));
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_4, (green << 8));
    __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL_3, (blue << 8));
}