/**
  ******************************************************************************
  * @file    EnvironmentTask.c
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
#include "EnvironmentTask.h"

CLASS_Huimiture Huimiture;
CLASS_Bme       Bme;

void Para_Init(void);

void vTaskEnvironment( void * pvParameters )
{
	/* 初始化参数 */
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


