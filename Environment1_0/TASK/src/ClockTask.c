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
CLASS_Clock ClockA; 

void vTaskClock( void * pvParameters )
{
	
	while(1)
	{
		
		
		DS3231_Readtime(&ClockA);
		
		vTaskDelay( 100 );
	}
	
}





