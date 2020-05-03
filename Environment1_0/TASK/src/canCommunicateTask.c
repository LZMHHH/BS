/**
  ******************************************************************************
  * @file    canCommunicateTask.c
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
#include "canCommunicateTask.h"

static void Led_ComCtrl(void);

//Can的接收任务
void vTaskCanRx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	CanRxMsg      p;  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	canCommunicateParaInit();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canRx,           /* 消息队列的句柄 */
                             (void *)&p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		
		/* 解码 */
		canmsgAnalyze(&p);
					
		Led_ComCtrl();
		canConnect.tickCount = xTaskGetTickCount();
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Can的发送任务
void vTaskCanTx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	CanTxMsg      p;  /* 实数组 接收copy数据*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canTx,           /* 消息队列的句柄 */
                             &p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
		

		/* 发送 */
		CAN_Transmit(CAN1, &p);	
		
		Led_ComCtrl();
		
		memset(&p, 0x00, sizeof(p));
		
	}
}

static void Led_ComCtrl(void)
{
	if(LedA.flag_mode == enCom)
	{
		digitalToggle(LedA.config.gpio_port,LedA.config.gpio_pin);
	}
	if(LedB.flag_mode == enCom)
	{
		digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
	}
	
}

/****************************************************
									  以上为直达can任务
										以下为准备数据任务
*****************************************************/
/* 声明 */
void sendLedData(void);
void sendKeyAckData(void);

//上传数据任务
void vTaskcanSendData( void * pvParameters )
{
	EventBits_t r_event;  /* 定义一个事件接收变量 */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_SendData,  /* 事件对象句柄 */
																EVENT_SHT3X
															 |EVENT_GY30
															 |EVENT_PMS
															 |EVENT_BME
															 |EVENT_LED,/* 接收线程感兴趣的事件 */
																pdTRUE,   /* 退出时清除事件位 */
																pdFALSE,   /* 满足感兴趣的如何一个事件 */
																portMAX_DELAY);/* 指定超时事件,一直等 */
		
		/* LED事件 */
		if((r_event & EVENT_LED) == (EVENT_LED)) 
    {		
			canSendLedData();
    }
		
		
	}
}



