/**
  ******************************************************************************
  * @file    CommunicateCTask.c
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
#include "CommunicateCTask.h"


//Uart1的接收任务
void vTaskUart3Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Rx,           /* 消息队列的句柄 */
                             (void *)&p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		/* 解码 */
		msgAnalyze(&p);
									
		uart3Connect.tickCount = xTaskGetTickCount();
														 
		memset(&p, 0x00, sizeof(p));										
		
	}
}

//Uart1的发送任务
void vTaskUart3Tx( void * pvParameters )
{
//	u8 len;
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
//	uint8_t    SendBuff[DEBUG3_TX_BSIZE];  /* 实数组 接收copy数据*/
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Tx,           /* 消息队列的句柄 */
                             &p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
		
		
		Uart3_DMA_SendString((u8 *)&p,
													p.dataLen + 4);	  /*  */
		
		if(LedB.flag_mode != enOFF)
		{
			digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
		}
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  以上为直达can任务
										以下为准备数据任务
*****************************************************/

//上传数据任务
void vTaskuart3SendData( void * pvParameters )
{
	EventBits_t r_event;  /* 定义一个事件接收变量 */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_uart3SendData,  /* 事件对象句柄 */
															  EVENT_uart3CARUI
															 |EVENT_uart3CARUIREQ
															 |EVENT_uart3OLEDCLEAR,/* 接收线程感兴趣的事件 */
																pdTRUE,   /* 退出时清除事件位 */
																pdFALSE,   /* 满足感兴趣的如何一个事件 */
																portMAX_DELAY);/* 指定超时事件,一直等 */
		

		/* CARUI请求事件 */
		if((r_event & EVENT_uart3CARUIREQ) == (EVENT_uart3CARUIREQ)) 
    {		
			canSendCarUIReqCmd();
    }
		/* 清屏事件 */
		if((r_event & EVENT_uart3OLEDCLEAR) == (EVENT_uart3OLEDCLEAR)) 
    {		
			OLED_Fill(0,0,128,64,0);
		}
		
	}
}


