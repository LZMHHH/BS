/**
  ******************************************************************************
  * @file    PmsTask.c
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
#include "PmsTask.h"

CLASS_Pms Pms; 

void UpdataPms(uint8_t *databuff,CLASS_Pms *pms);


void vTaskPms( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint8_t    ReadBuff[DEBUG2_RX_BSIZE];  /* 实数组 接收copy数据*/\
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart2Rx,           /* 消息队列的句柄 */
                             (void *)&ReadBuff,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */

														 
		UpdataPms(ReadBuff,&Pms);
														 

	}
	
}

void UpdataPms(uint8_t *databuff,CLASS_Pms *pms)
{
	if(databuff[0] == 0x42)
	{
		if(databuff[1] == 0x4d)
		{
			 pms->PM2_5_Vol = (databuff[12] << 8) | databuff[13];
			 pms->PM10_Vol  = (databuff[14] << 8) | databuff[15]; 
		}
	}
}



