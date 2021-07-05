#include "pwm_servo.h"

servo_data_t servo_data[SERVO_NUM];
uint8_t 	servo_index;
/***********************************************
	函数名称：	Servo_Init() 
	功能介绍：	配置端口
	函数参数：	无
	返回值：	无
 ***********************************************/
 static void Servo_Init()
 {
	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  SERVO0_Pin|SERVO1_Pin|SERVO2_Pin|SERVO3_Pin|SERVO4_Pin|SERVO5_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SERVO0_GPIO_Port, &GPIO_InitStructure);	
	
	Servo_Set(0,0);
	Servo_Set(1,0);
	Servo_Set(2,0);
	Servo_Set(3,0);
	Servo_Set(4,0);
	Servo_Set(5,0);
 }

/***********************************************
	函数名称：	Servo_Set(uint8_t index, uint8_t level) 
	功能介绍：	设置输出量
	函数参数：	index 编号 ；level 输出量
	返回值：	无
 ***********************************************/
void Servo_Set(uint8_t index, uint8_t level)
 {
	if (level)
	{
		switch(index){
			case 0:SERVO0_H;break;
			case 1:SERVO1_H;break;
			case 2:SERVO2_H;break;
			case 3:SERVO3_H;break;
			case 4:SERVO4_H;break;
			case 5:SERVO5_H;break;
			default:		break;
		}
	}else
	{
		switch(index){
			case 0:SERVO0_L;break;
			case 1:SERVO1_L;break;
			case 2:SERVO2_L;break;
			case 3:SERVO3_H;break;
			case 4:SERVO4_H;break;
			case 5:SERVO5_H;break;
			default:		break;
	}
	}
}
 
/***********************************************
	函数名称：	Servo_Setup() 
	功能介绍：	所有Servo输出90°位置
	函数参数：	无
	返回值：	无
 ***********************************************/
void Servo_Setup(void)
{

	for(servo_index=0;servo_index<SERVO_NUM;servo_index++)
	{
		
		servo_data[servo_index].aim=1500;
		servo_data[servo_index].cur=1500;
		servo_data[servo_index].time=0;
	}
}


/***********************************************
	函数名称：	Servo_Config() 
	功能介绍：	初始化
	函数参数：	无
	返回值：	无
 ***********************************************/
void Servo_Config(void)
{
	Servo_Setup();
	Servo_Init();
}
 
 /***********************************************
	函数名称：	Servo_Run(uint8_t index,int aim,int time)
	功能介绍：	Servo 运行函数
	函数参数：	index 编号；aim 运行目标值；time 限定运行时间
	返回值：	无
 ***********************************************/
void Servo_Run(uint8_t index,int aim,int time)
{
	if(index<SERVO_NUM&&(aim>=500)&&(aim<=2500)&&(time<10000))
	{
		if (servo_data[index].cur == aim){
			aim=aim+0.0077;
		}
		if(aim>L270)	aim=L270;
		if(aim<L0)		aim=L0;
		
		if(time<20){
			servo_data[index].aim=aim;
			servo_data[index].cur=aim;
			servo_data[index].inc=0;
		}else {
			servo_data[index].aim = aim;
			servo_data[index].time = time;
			servo_data[index].inc = (servo_data[index].aim-servo_data[index].cur)/(servo_data[index].time/20.000);
		}
	}
		
	}
}

/***********************************************
	函数名称：	loop_servo() 
	功能介绍：	循环处理舵机的指令
	函数参数：	无
	返回值：		无
 ***********************************************/
void loop_servo(void) {
	if(servo_data[servo_index].inc != 0) {
		if(servo_data[servo_index].aim>2495)	servo_data[servo_index].aim=2495;
		if(servo_data[servo_index].aim<500)		servo_data[servo_index].aim=500;
		if(servo_abs(servo_data[servo_index].aim - servo_data[servo_index].cur) <= servo_abs(servo_data[servo_index].inc + servo_data[servo_index].inc)) {
			servo_data[servo_index].cur = servo_data[servo_index].aim;
			servo_data[servo_index].inc = 0;
		} else {
			servo_data[servo_index].cur += servo_data[servo_index].inc;
		}
	}
}





