/**
  ******************************************************************************
  * @file    TimeTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ʱ������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "ClockTask.h"

/* ����һ��ʱ�� */
CLASS_Clock ClockA; 

void vTaskClock( void * pvParameters )
{
	
	while(1)
	{
		
		
		DS3231_Readtime(&ClockA);
		
		vTaskDelay( 100 );
	}
	
}





