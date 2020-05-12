/**
  ******************************************************************************
  * @file    LedTask.c
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
#include "LedTask.h"

volatile TickType_t SendLedDataTickCount; //用于定时上传数据
volatile TickType_t SendLedDataTickCountA; //用于定时上传数据

static void Para_Init(void);
static void Fmq_Ctrl(void);
static void Led_Ctrl(void);

void vTaskLed( void * pvParameters )
{
	
	/* 初始化参数 */
	Para_Init();
	
	while(1)
	{


		Led_Ctrl();
		Fmq_Ctrl();
		
//		/*定时上报*/
//		if((xTaskGetTickCount()-100) > SendLedDataTickCount)
//		{
//			/* 触发事件 */
//			xEventGroupSetBits(Event_canSendData,EVENT_canLED);			
//			SendLedDataTickCount = xTaskGetTickCount();
//		}
//		if(SendLedDataTickCount > xTaskGetTickCount())
//		{
//			SendLedDataTickCount = xTaskGetTickCount();
//		}
//		if((xTaskGetTickCount()-500) > SendLedDataTickCountA)
//		{
//			/* 触发一个事件*/
//			xEventGroupSetBits(Event_SendData,EVENT_LED);	
//			SendLedDataTickCountA = xTaskGetTickCount();
//		}
//		if(SendLedDataTickCountA > xTaskGetTickCount())
//		{
//			SendLedDataTickCountA = xTaskGetTickCount();
//		}
		
		vTaskDelay( 10 );
	}
	
}

static void Para_Init(void)
{
	LedA.flag_mode = enOFF;
	LedA.cycle   = 100;
	LedB.flag_mode = enFre;
	LedB.cycle   = 10;
	Fmq.flag_mode  = enOFF;
	Fmq.cycle    = -1;
	
	SendLedDataTickCount  = xTaskGetTickCount();
	SendLedDataTickCountA = xTaskGetTickCount();
}

static void Led_Ctrl(void)
{
	switch(LedA.flag_mode)
	{
		case enON:
					bsp_Led_Flash(&LedA,-1);
					break;
		case enOFF:
					bsp_Led_Flash(&LedA,0);
					break;
		case enFre:
					bsp_Led_Flash(&LedA,LedA.cycle);
					break;
		default:break;
	}

	
}

static void Fmq_Ctrl(void)
{
	switch(Fmq.flag_mode)
	{
		case enON:
					bsp_Fmq_Flash(&Fmq,-1);
					break;
		case enOFF:
					bsp_Fmq_Flash(&Fmq,0);
					break;
		case enFre:
					bsp_Fmq_Flash(&Fmq,Fmq.cycle);
					break;
		default:break;
	}
}


void canSendLedData(void)
{
	CanTxMsg p;
	
	/* 发送数据 */
	p.StdId = CAN_LEDID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_LEDA;
	p.Data[3] = CAN_LedMode;
	p.Data[4] = LedA.flag_mode;
	xQueueSend(xQueue_canTx, &p, 10);
	
	/* 发送数据 */
	p.StdId = CAN_LEDID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_LEDA;
	p.Data[3] = CAN_LedFre;
	memcpy(p.Data+4, &(LedA.cycle), sizeof(LedA.cycle));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);
	
	
	p.Data[2] = CAN_FMQ;
	p.Data[3] = CAN_LedMode;
	p.Data[4] = Fmq.flag_mode;
	xQueueSend(xQueue_canTx, &p, 10);
	
	p.Data[2] = CAN_FMQ;
	p.Data[3] = CAN_LedFre;
	memcpy(p.Data+4, &(Fmq.cycle), sizeof(Fmq.cycle));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);

}

void uart1SendLedData(TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 2+sizeof(LedA.flag_mode)+sizeof(LedA.cycle)+sizeof(LedB.flag_mode)+sizeof(LedB.cycle); 
	p.data[0] = enDATA;
	p.data[1] = KIND_LED;
	
	memcpy(p.data+2, 
				&(LedA.flag_mode), 1);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1, 
				&(LedA.cycle), 4);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1+4, 
				&(Fmq.flag_mode), 1);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1+4+1, 
				&(Fmq.cycle), 4);  /* 特别留意，低字节在前 */

	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
