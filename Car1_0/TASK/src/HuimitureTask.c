/**
  ******************************************************************************
  * @file    HuimitureTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "HuimitureTask.h"

CLASS_Huimiture Huimiture;

void vTaskHuimiture( void * pvParameters )
{
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		
		
		vTaskDelay( 20 );
	}
	
}





