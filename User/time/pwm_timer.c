#include "pwm_timer.h"
#include "pwm_servo.h"

void TIMx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//打开GPIO时钟，*同时打开AFIO复用功能时钟
	RCC_APB2PeriphClockCmd(TIMx_GPIO_CLK|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(TIMx_CLK,ENABLE);
	
	//TIMxGPIO端口初始化
	GPIO_InitStructure.GPIO_Pin = TIMx_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(TIMx_GPIO_PROT, &GPIO_InitStructure);
	
	//配置通用定时器2
	TIM_TimeBaseStructure.TIM_Period=19999;
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIMx, DISABLE);
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE );  
	TIM_Cmd(TIMx,ENABLE);
	
	//配置PWM模式
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	
	//TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  						//TIM2 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//先占优先级 0 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  				//从优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  						//IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure);  														//④初始化 NVIC 寄存器
	TIM_Cmd(TIMx, ENABLE);  
}


/***********************************************
	函数名称：	TIM2_IRQHandler() 
	功能介绍：	输出舵机Pwm波形
	函数参数：	无
	返回值：	无
 ***********************************************/
void TIM2_IRQHandler(void) {
	static u8 flag = 0;
	int temp;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 					//检查 TIM2 更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); 							//清除 TIM2 更新中断标志
		if(servo_data[servo_index].cur>L270)	servo_data[servo_index].cur=L270;
		if(servo_data[servo_index].cur<L0)		servo_data[servo_index].cur=L0;
				
		if(!flag) {
			TIM2->ARR = ((unsigned int)(servo_data[servo_index].cur));
			Servo_Set(servo_index, 1);
		} else {
			temp = 2500 - (unsigned int)(servo_data[servo_index].cur);
			if(temp < 20)temp = 20;
			TIM2->ARR = temp;
			Servo_Set(servo_index, 0);
			servo_index ++;
		}
		if(servo_index >= SERVO_NUM) {
			servo_index = 0;
		}
		flag = !flag;
	}
} 



