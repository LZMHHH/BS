/**
  ******************************************************************************
  * @file    LightTask.c
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
#include "LightTask.h"

CLASS_Light Light; 


static void Para_Init(void);
void canSendGy30Data(void);


void vTaskLight( void * pvParameters )
{
	Para_Init();
	
	/* 先延时，让模块准备数据 */
	vTaskDelay( 200 );
	
	while(1)
	{

		Updata_BH1750(&Light);
		
		canSendGy30Data();
		
		vTaskDelay( 200 );
	}
	
}

static void Para_Init(void)
{
	Light.shieldVal = 2000;
	Light.a         = 1.0;
}

void canSendGy30Data(void)
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
	p.Data[2] = CAN_GY30;
	p.Data[3] = CAN_Light;
	intdata = (int)((Light.BH_Voltage)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_Shield;
	intdata = (int)((Light.shieldVal)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_MODE;
	p.Data[4] = Light.a;
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_FactorA;
	intdata = (int)((Light.a)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
}



