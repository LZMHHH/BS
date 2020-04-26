/**
  ******************************************************************************
  * @file    LedTask.c
  * @author  lss
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
#include "LedTask.h"

static void Para_Init(void);
static void Fmq_Ctrl(void);
static void Led_Ctrl(void);

void vTaskLed( void * pvParameters )
{
	
	/* 初始化参数 */
	Para_Init();
	
	while(1)
	{


		Led_Ctrl();
		
		vTaskDelay( 10 );
	}
	
}

static void Para_Init(void)
{
	LedA.flag_mode = enOFF;
	LedA.cycle   = 100;
	LedB.flag_mode = enFre;
	LedB.cycle   = 10;
	Fmq.flag_mode  = enOFF;
	Fmq.cycle    = -1;
}

static void Led_Ctrl(void)
{
	switch(LedA.flag_mode)
	{
		case enON:
					bsp_Led_Flash(&LedA,-1);
					break;
		case enOFF:
					bsp_Led_Flash(&LedA,0);
					break;
		case enFre:
					bsp_Led_Flash(&LedA,LedA.cycle);
					break;
		default:break;
	}
	
}

static void Fmq_Ctrl(void)
{
	
}





