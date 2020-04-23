/**
  ******************************************************************************
  * @file    TimeTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   时钟任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "ClockTask.h"

/* 创建一个时钟 */
CLASS_Clock ClockA;    /* 用于显示当前时间 */


CLASS_Clock SetClock;  /* 用于时钟时间 */


static void Para_Init(void);

void vTaskClock( void * pvParameters )
{
	
	Para_Init();
	
	while(1)
	{
		
		
		DS3231_Readtime(&ClockA);
		
		vTaskDelay( 100 );
	}
	
}


static void Para_Init(void)
{
	SetClock.num_save = 0;
	ClockA.num_save   = 0;
}



