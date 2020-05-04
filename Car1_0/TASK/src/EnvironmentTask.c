/**
  ******************************************************************************
  * @file    EnvironmentTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   普通环境数据采集
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "EnvironmentTask.h"

static void Para_Init(void);


void vTaskEnvironment( void * pvParameters )
{
	
	
	
	/* 初始化参数 */
	Para_Init();
	
	
	while(1)
	{
		/* SHT3X */
		xEventGroupSetBits(Event_SendData,EVENT_uart1SHT3X);	
		/* GY30 */
		xEventGroupSetBits(Event_SendData,EVENT_uart1GY30);	
		/* PMS */
		xEventGroupSetBits(Event_SendData,EVENT_uart1PMS);	
		/* BME */
		xEventGroupSetBits(Event_SendData,EVENT_uart1BME);	
		
		
		vTaskDelay( 200 );
	}
	
}


static void Para_Init(void)
{

}

/*发送数据*/
void sendSht3xData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 8 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SHT3X;
	intdata   = (int)((Huimiture.temperature)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Huimiture.huimidity)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
void sendGy30Data(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_GY30;
	intdata   = (int)((Light.BH_Voltage)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
void sendPmsData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 8 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_PMS;
	intdata   = (int)((Pms.PM2_5_Vol)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Pms.PM10_Vol)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
void sendBmeData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 16 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_BME;
	intdata   = (int)((Bme.pressure)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Bme.asl)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	intdata   = (int)((Bme.temperature)*100);
	memcpy(p.data+10, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Bme.humidity)*100);
	memcpy(p.data+14, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}


