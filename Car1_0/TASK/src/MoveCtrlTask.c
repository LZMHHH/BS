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

void vTaskMoveCtrl( void * pvParameters )
{
	int a=0;
	while(1)
	{
		a++;
		if(a>8000)
			a=0;
		Set_Pwm(MotorA,a);
		Set_Pwm(MotorB,a);
		Set_Pwm(MotorC,a);
		Set_Pwm(MotorD,a);
		vTaskDelay( 10 );
	}
	
}





