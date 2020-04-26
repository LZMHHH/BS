/**
  ******************************************************************************
  * @file    MoveCtrlTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   移动控制任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "MoveCtrlTask.h"


CLASS_Motor MotorA;
CLASS_Motor MotorB;
CLASS_Motor MotorC;
CLASS_Motor MotorD;


static void Para_Init(void);

void vTaskMoveCtrl( void * pvParameters )
{
	int a = 0;
	
	/* 初始化参数 */
	Para_Init();
	
	while(1)
	{
		a+=5;
		if(a > 7000)
			a = -7000;
		
		MotorA.encoderVal =  Read_Encoder(1);
		MotorB.encoderVal =  Read_Encoder(2);
		MotorC.encoderVal = -Read_Encoder(3);
		MotorD.encoderVal = -Read_Encoder(4);
		
		MotorA.pwmout     = a;
		MotorB.pwmout     = a;
		MotorC.pwmout     = a;
		MotorD.pwmout     = a;
		
		
		
		Set_Pwm(&MotorA);
		Set_Pwm(&MotorB);
		Set_Pwm(&MotorC);
		Set_Pwm(&MotorD);
		
		vTaskDelay( 10 );
	}
	
}

static void Para_Init(void)
{
	MotorA.name = enMotorA;
	MotorB.name = enMotorB;
	MotorC.name = enMotorC;
	MotorD.name = enMotorD;
	
	MotorA.pwmout     = 0;
	MotorB.pwmout     = 0;
	MotorC.pwmout     = 0;
	MotorD.pwmout     = 0;
	
	Set_Pwm(&MotorA);
	Set_Pwm(&MotorB);
	Set_Pwm(&MotorC);
	Set_Pwm(&MotorD);
}




