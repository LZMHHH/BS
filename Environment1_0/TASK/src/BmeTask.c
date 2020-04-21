/**
  ******************************************************************************
  * @file    BmeTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   普通环境数据采集
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "BmeTask.h"

CLASS_Bme       Bme;

static void Para_Init(void);

void vTaskBme( void * pvParameters )
{
	/* 初始化参数 */
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


