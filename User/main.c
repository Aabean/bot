#include "stm32f10x.h"   
#include "pwm_servo.h"   
#include "pwm_timer.h"   
#include "key.h"

int main(void)
{
	Servo_Config();
	TIMx_Init();
	Servo_Setup();
	
	while(1)
	{
		while (KEY_Scan(KEY1_GPIO_PORT,uint16_t GPIO_Pin)!=KEY_ON);
		Servo_Run(0,L225,0);
		delay_ms(500);
		Servo_Run(1,L180,0);
		delay_ms(500);
		Servo_Run(2,L225,0);
		delay_ms(500);
		Servo_Run(3,L90,0);
		delay_ms(500);
		Servo_Run(5,L100,0);
		delay_ms(500);
		/***/
		Servo_Run(1,L135,0);
		delay_ms(500);
		Servo_Run(0,L135,0);
		delay_ms(500);
		Servo_Run(1,L180,0);
		delay_ms(500);
		/***/
		Servo_Run(5,L135,0);
		delay_ms(500);
		Servo_Run(1,L135,0);
		delay_ms(500);
		Servo_Run(2,L135,0);
		delay_ms(500);
		Servo_Run(3,L135,0);
		delay_ms(500);
	}
	
	
}


