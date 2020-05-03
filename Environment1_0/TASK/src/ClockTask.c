/**
  ******************************************************************************
  * @file    TimeTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   时钟任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "ClockTask.h"

/* 创建一个时钟 */
CLASS_Clock ClockA;    /* 用于显示当前时间 */


CLASS_Clock SetClock;  /* 用于时钟时间 */


static void Para_Init(void);
void canSendClockData(void);


void vTaskClock( void * pvParameters )
{
	
	Para_Init();
	
	while(1)
	{
		
		
		DS3231_Readtime(&ClockA);
		
		canSendClockData();
		
		vTaskDelay( 100 );
	}
	
}


static void Para_Init(void)
{
	SetClock.num_save = 0;
	ClockA.num_save   = 0;
}

void canSendClockData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	
	switch(flag)
	{
		case 0:
					flag++;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_DS3231;
					p.Data[3] = CAN_Second;
					memcpy(p.Data+4, &(ClockA.Second), sizeof(ClockA.Second));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Minute;
					memcpy(p.Data+4, &(ClockA.Minute), sizeof(ClockA.Minute));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Hour;
					memcpy(p.Data+4, &(ClockA.Hour), sizeof(ClockA.Hour));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Day;
					memcpy(p.Data+4, &(ClockA.Day), sizeof(ClockA.Day));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Week;
					memcpy(p.Data+4, &(ClockA.Week), sizeof(ClockA.Week));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Month;
					memcpy(p.Data+4, &(ClockA.Month), sizeof(ClockA.Month));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Year;
					memcpy(p.Data+4, &(ClockA.Year), sizeof(ClockA.Year));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag++;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_DS3231;
					p.Data[3] = CAN_ClockMode;
					p.Data[4] = ClockA.Switch;
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[3] = CAN_SaveNum;
					memcpy(p.Data+4, &(ClockA.num_save), sizeof(ClockA.num_save));
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 2:
					flag++;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;
					p.Data[3] = CAN_Second;
					memcpy(p.Data+4, &(SetClock.Second), sizeof(SetClock.Second));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Minute;
					memcpy(p.Data+4, &(SetClock.Minute), sizeof(SetClock.Minute));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Hour;
					memcpy(p.Data+4, &(SetClock.Hour), sizeof(SetClock.Hour));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					break;
		case 3:
					flag++;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;
					p.Data[3] = CAN_Day;
					memcpy(p.Data+4, &(SetClock.Day), sizeof(SetClock.Day));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Week;
					memcpy(p.Data+4, &(SetClock.Week), sizeof(SetClock.Week));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Month;
					memcpy(p.Data+4, &(SetClock.Month), sizeof(SetClock.Month));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
					
					break;
		case 4:
					flag=0;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;			
					p.Data[3] = CAN_Year;
					memcpy(p.Data+4, &(SetClock.Year), sizeof(SetClock.Year));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 5);
		
					p.Data[3] = CAN_ClockMode;
					p.Data[4] = SetClock.Switch;
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[3] = CAN_SaveNum;
					memcpy(p.Data+4, &(SetClock.num_save), sizeof(SetClock.num_save));
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
								flag = 0;	
								break;
	}
	
}


