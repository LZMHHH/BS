/**
  ******************************************************************************
  * @file    EnvironmentTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ��ͨ�������ݲɼ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "EnvironmentTask.h"

CLASS_Huimiture Huimiture;

static void Para_Init(void);

void vTaskEnvironment( void * pvParameters )
{
	/* ��ʼ������ */
	Para_Init();
	
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		
		vTaskDelay( 20 );
	}
	
}


static void Para_Init(void)
{
	
}


