/**
  ******************************************************************************
  * @file    BmeTask.c
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
#include "BmeTask.h"

CLASS_Bme       Bme;

static void Para_Init(void);
void canSendBMEData(void);


void vTaskBme( void * pvParameters )
{
	/* 初始化参数 */
	Para_Init();
	
	
	while(1)
	{
		
		
		BME280_Getdata(&Bme); 
		
		canSendBMEData();
		
		vTaskDelay( 200 );
	}
	
}


static void Para_Init(void)
{
	
}

void canSendBMEData(void)
{
	int intdata;
	CanTxMsg p;
	
	/* 发送数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Pressure;
	intdata = (int)((Bme.pressure)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* 发送数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Hight;
	intdata = (int)((Bme.asl)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* 发送数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Temperature;
	intdata = (int)((Bme.temperature)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* 发送数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Humidity;
	intdata = (int)((Bme.humidity)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
}


