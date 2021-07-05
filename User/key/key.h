#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY1_GPIO_CLK	RCC_APB2Periph_GPIOC
#define KEY2_GPIO_CLK	RCC_APB2Periph_GPIOC


#define KEY1_GPIO_PORT	GPIOA
#define KEY1_GPIO_PIN	GPIO_Pin_0

#define KEY2_GPIO_PORT	GPIOA
#define KEY2_GPIO_PIN	GPIO_Pin_1

#define KEY_ON 	1
#define KEY_OFF 0

void KEY_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin);
#endif 