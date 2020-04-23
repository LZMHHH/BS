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
CLASS_Clock ClockA;    /* ������ʾ��ǰʱ�� */


CLASS_Clock SetClock;  /* ����ʱ��ʱ�� */


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



