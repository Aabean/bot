#ifndef __PWM_SERVO_H
#define __PWM_SERVO_H

#include "stm32f10x.h"
#include "pwm_timer.h"

#define SERVO_NUM	7


typedef struct{
	float aim;//目标值	
	float cur;//当前值
	int time;//时间	
	float inc;//中间值
}servo_data_t;

/*GPIO映射*/
#define SERVO0_Pin 					GPIO_Pin_3  
#define SERVO0_GPIO_Port 			GPIOB
#define SERVO1_Pin 					GPIO_Pin_8  
#define SERVO1_GPIO_Port 			GPIOB
#define SERVO2_Pin 					GPIO_Pin_9  
#define SERVO2_GPIO_Port 			GPIOB
#define SERVO3_Pin 					GPIO_Pin_6  
#define SERVO3_GPIO_Port 			GPIOB
#define SERVO4_Pin 					GPIO_Pin_7  
#define SERVO4_GPIO_Port 			GPIOB
#define SERVO5_Pin 					GPIO_Pin_4  
#define SERVO5_GPIO_Port 			GPIOB

/*快捷指令*/
#define SERVO0_H 					GPIO_SetBits(SERVO0_GPIO_Port,SERVO0_Pin) 
#define SERVO0_L					GPIO_ResetBits(SERVO0_GPIO_Port,SERVO0_Pin)
#define SERVO1_H					GPIO_SetBits(SERVO1_GPIO_Port,SERVO1_Pin) 
#define SERVO1_L					GPIO_ResetBits(SERVO1_GPIO_Port,SERVO1_Pin)
#define SERVO2_H					GPIO_SetBits(SERVO2_GPIO_Port,SERVO2_Pin) 
#define SERVO2_L					GPIO_ResetBits(SERVO2_GPIO_Port,SERVO2_Pin)
#define SERVO3_H 					GPIO_SetBits(SERVO3_GPIO_Port,SERVO3_Pin) 
#define SERVO3_L					GPIO_ResetBits(SERVO3_GPIO_Port,SERVO3_Pin)
#define SERVO4_H 					GPIO_SetBits(SERVO4_GPIO_Port,SERVO4_Pin) 
#define SERVO4_L					GPIO_ResetBits(SERVO4_GPIO_Port,SERVO4_Pin)
#define SERVO5_H 					GPIO_SetBits(SERVO5_GPIO_Port,SERVO5_Pin) 
#define SERVO5_L					GPIO_ResetBits(SERVO5_GPIO_Port,SERVO5_Pin)


//每5°转动角度定义：
//arr=1000/（最大转动角度/2）*5
#define L0		500
#define L5		537
#define L10		574
#define L15		611
#define L20		648
#define L25		685
#define L30		722
#define L35		759
#define L40		796
#define L45		833
#define L50		870
#define L55		907
#define L60		944
#define L65		981
#define L70		1018
#define L75		1055
#define L80		1092
#define L85		1129
#define L90		1166
#define L95		1203
#define L100	1240
#define L105	1277
#define L110	1314
#define L115	1351
#define L120	1388
#define L125	1425
#define L130	1462
#define L135	1499
#define L140	1536
#define L145	1573
#define L150	1610
#define L155	1647
#define L160	1684
#define L165	1721
#define L170	1758
#define L175	1795
#define L180	1832
#define L185	1869
#define L190	1906
#define L195	1943
#define L200	1980
#define L205	2017
#define L210	2054
#define L215	2091
#define L220	2128
#define L225	2165
#define L230	2202
#define L235	2239
#define L240	2276
#define L245	2313
#define L250	2350
#define L255	2387
#define L260	2424
#define L265	2461
#define L270	2497



extern servo_data_t servo_data[SERVO_NUM];
extern uint8_t 	servo_index;


void Servo_Setup(void);
void Servo_Set(uint8_t index, uint8_t level);
void Servo_Config(void);
void Servo_Run(uint8_t index,int aim,int time);


#endif  /*__PWM_SERVO_H*/
