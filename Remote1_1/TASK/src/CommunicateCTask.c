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
	uint8_t    ReadBuff[DEBUG3_RX_BSIZE];  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Rx,           /* 消息队列的句柄 */
                             (void *)&ReadBuff,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		//接收成功后马上发回去
		xReturn = xQueueSend( xQueue_uart3Tx,  /* 消息队列的句柄 */
													&ReadBuff,       /* 发送的消息内容 */
													0 );             /* 等待时间 0 */													
		
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
													p.dataLen + 3);	  /*  */
		
		if(LedB.flag_mode != enOFF)
		{
			digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
		}
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


