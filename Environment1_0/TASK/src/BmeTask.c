/**
  ******************************************************************************
  * @file    BmeTask.c
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
#include "BmeTask.h"

CLASS_Bme       Bme;

static void Para_Init(void);

void vTaskBme( void * pvParameters )
{
	/* ��ʼ������ */
	Para_Init();
	
	
	while(1)
	{
		
		
		BME280_Getdata(&Bme);
		
		vTaskDelay( 200 );
	}
	
}


static void Para_Init(void)
{
	
}


