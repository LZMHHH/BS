/**
  ******************************************************************************
  * @file    KeyTask.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
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
#include "KeyTask.h"

//声明
void Key_Control(void);
void Status_Scan(void);


void vTaskKey( void * pvParameters )
{
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		Key_Scan(&Key_PL);
		Key_Scan(&Key_PR);
		Key_Scan(&Key_PM);
		
		
		Status_Scan();
		
		vTaskDelay( 10 );
	}
	
}


void Status_Scan(void)
{
	
	/* can */
	if((xTaskGetTickCount() - 300) > canConnect.tickCount)
	{
		canConnect.status = enBreak;
	}
	else
	{
		canConnect.status = enSig3;
	}
	if(canConnect.tickCount > xTaskGetTickCount())
	{
		canConnect.tickCount = xTaskGetTickCount();
	}
	
}






