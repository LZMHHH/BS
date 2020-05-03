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

void canSendPmsData(void);
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
					
		/* 因为pms器件隔200-800ms才发送一次数据上来，所以，可以直接can出去 */
		canSendPmsData();

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


void canSendPmsData(void)
{
	u16 u16data;
	
	CanTxMsg p;
	
	/* 发送sht3x的温度数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM2_5;
	u16data = (u16)(Pms.PM2_5_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* 发送sht3x的温度数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM10;
	u16data = (u16)(Pms.PM10_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
}

