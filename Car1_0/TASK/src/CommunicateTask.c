/**
  ******************************************************************************
  * @file    CommunicateTask.c
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
#include "CommunicateTask.h"


//Uart1的接收任务
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* 消息队列的句柄 */
                             (void *)&p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		
		/* 解码 */
		msgAnalyze(&p);
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Uart1的发送任务
void vTaskUart1Tx( void * pvParameters )
{
//	u8 len;
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             &p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
		
		
		Uart1_DMA_SendString((u8 *)&p,
													p.dataLen + 3);	  /*  */
		
		if(LedB.flag_mode != enOFF)
		{
			digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
		}
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


