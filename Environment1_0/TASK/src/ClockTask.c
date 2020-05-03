/**
  ******************************************************************************
  * @file    TimeTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ʱ������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "ClockTask.h"

/* ����һ��ʱ�� */
CLASS_Clock ClockA;    /* ������ʾ��ǰʱ�� */


CLASS_Clock SetClock;  /* ����ʱ��ʱ�� */


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
					/* ����sht3x���¶����� */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_DS3231;
					p.Data[3] = CAN_Second;
					memcpy(p.Data+4, &(ClockA.Second), sizeof(ClockA.Second));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Minute;
					memcpy(p.Data+4, &(ClockA.Minute), sizeof(ClockA.Minute));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Hour;
					memcpy(p.Data+4, &(ClockA.Hour), sizeof(ClockA.Hour));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Day;
					memcpy(p.Data+4, &(ClockA.Day), sizeof(ClockA.Day));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Week;
					memcpy(p.Data+4, &(ClockA.Week), sizeof(ClockA.Week));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Month;
					memcpy(p.Data+4, &(ClockA.Month), sizeof(ClockA.Month));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_Year;
					memcpy(p.Data+4, &(ClockA.Year), sizeof(ClockA.Year));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag++;
					/* ����sht3x���¶����� */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
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
					/* ����sht3x���¶����� */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;
					p.Data[3] = CAN_Second;
					memcpy(p.Data+4, &(SetClock.Second), sizeof(SetClock.Second));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Minute;
					memcpy(p.Data+4, &(SetClock.Minute), sizeof(SetClock.Minute));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Hour;
					memcpy(p.Data+4, &(SetClock.Hour), sizeof(SetClock.Hour));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					break;
		case 3:
					flag++;
					/* ����sht3x���¶����� */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;
					p.Data[3] = CAN_Day;
					memcpy(p.Data+4, &(SetClock.Day), sizeof(SetClock.Day));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Week;
					memcpy(p.Data+4, &(SetClock.Week), sizeof(SetClock.Week));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					
					p.Data[3] = CAN_Month;
					memcpy(p.Data+4, &(SetClock.Month), sizeof(SetClock.Month));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 5);
					
					break;
		case 4:
					flag=0;
					/* ����sht3x���¶����� */
					p.StdId = CAN_TIMEID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;;
					p.Data[2] = CAN_SETCLOCK;			
					p.Data[3] = CAN_Year;
					memcpy(p.Data+4, &(SetClock.Year), sizeof(SetClock.Year));  /* �ر����⣬���ֽ���ǰ */
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


