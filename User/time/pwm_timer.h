#ifndef __PWM_TIMER_H
#define __PWM_TIMER_H

#include "stm32f10x.h"
#include "pwm_servo.h"

#define TIMx_GPIO_CLK				RCC_APB2Periph_GPIOA
#define TIMx_CLK					RCC_APB1Periph_TIM2

#define TIMx						TIM2

#define TIMx_GPIO_PROT				GPIOA
#define TIMx_GPIO_PIN				GPIO_Pin_0

void TIMx_Init(void);
void TIM2_IRQHandler(void);

#endif 

