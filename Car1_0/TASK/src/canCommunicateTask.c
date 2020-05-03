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
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  以上为直达can任务
										以下为准备数据任务
*****************************************************/

