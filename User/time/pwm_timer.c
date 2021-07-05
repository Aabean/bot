#include "pwm_timer.h"
#include "pwm_servo.h"

void TIMx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//��GPIOʱ�ӣ�*ͬʱ��AFIO���ù���ʱ��
	RCC_APB2PeriphClockCmd(TIMx_GPIO_CLK|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(TIMx_CLK,ENABLE);
	
	//TIMxGPIO�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = TIMx_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(TIMx_GPIO_PROT, &GPIO_InitStructure);
	
	//����ͨ�ö�ʱ��2
	TIM_TimeBaseStructure.TIM_Period=19999;
	TIM_TimeBaseStructure.TIM_Prescaler=71;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIMx, DISABLE);
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE );  
	TIM_Cmd(TIMx,ENABLE);
	
	//����PWMģʽ
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	
	//TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  						//TIM2 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//��ռ���ȼ� 0 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  				//�����ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  						//IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  														//�ܳ�ʼ�� NVIC �Ĵ���
	TIM_Cmd(TIMx, ENABLE);  
}


/***********************************************
	�������ƣ�	TIM2_IRQHandler() 
	���ܽ��ܣ�	������Pwm����
	����������	��
	����ֵ��	��
 ***********************************************/
void TIM2_IRQHandler(void) {
	static u8 flag = 0;
	int temp;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 					//��� TIM2 �����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); 							//��� TIM2 �����жϱ�־
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



