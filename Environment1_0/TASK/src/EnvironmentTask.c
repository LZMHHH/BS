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
CLASS_Bme       Bme;

void Para_Init(void);

void vTaskEnvironment( void * pvParameters )
{
	/* ��ʼ������ */
	Para_Init();
	
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		
		BME280_Getdata(&Bme);
		
		vTaskDelay( 200 );
	}
	
}


void Para_Init(void)
{
	
}


