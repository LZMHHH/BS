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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "LightTask.h"

CLASS_Light Light; 

void vTaskLight( void * pvParameters )
{
	/* ����ʱ����ģ��׼������ */
	vTaskDelay( 200 );
	
	while(1)
	{

		Updata_BH1750(&Light);
		
		vTaskDelay( 200 );
	}
	
}





