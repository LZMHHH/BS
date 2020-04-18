/**
  ******************************************************************************
  * @file    LightTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "LightTask.h"

CLASS_Light Light; 

void vTaskLight( void * pvParameters )
{
	/* 先延时，让模块准备数据 */
	vTaskDelay( 200 );
	
	while(1)
	{

		Updata_BH1750(&Light);
		
		vTaskDelay( 200 );
	}
	
}





