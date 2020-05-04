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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "LedTask.h"

volatile TickType_t SendLedDataTickCount; //���ڶ�ʱ�ϴ�����

static void Para_Init(void);
static void Fmq_Ctrl(void);
static void Led_Ctrl(void);

void vTaskLed( void * pvParameters )
{
	
	/* ��ʼ������ */
	Para_Init();
	
	while(1)
	{
		Led_Ctrl();
		
		if((xTaskGetTickCount()-100) > SendLedDataTickCount)
		{
			/* �����¼� */
			xEventGroupSetBits(Event_canSendData,EVENT_canLED);		
			SendLedDataTickCount = xTaskGetTickCount();
		}
		if(SendLedDataTickCount > xTaskGetTickCount())
		{
			SendLedDataTickCount = xTaskGetTickCount();
		}
		
		vTaskDelay( 10 );
	}
	
}

static void Para_Init(void)
{
	LedA.flag_mode = enFre;
	LedA.cycle   = 100;
	LedB.flag_mode = enCom;
	LedB.cycle   = 10;
	Fmq.flag_mode  = enOFF;
	Fmq.cycle    = -1;
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
	
	switch(LedB.flag_mode)
	{
		case enON:
					bsp_Led_Flash(&LedB,-1);
					break;
		case enOFF:
					bsp_Led_Flash(&LedB,0);
					break;
		case enFre:
					bsp_Led_Flash(&LedB,LedB.cycle);
					break;
		default:break;
	}
}

static void Fmq_Ctrl(void)
{
	
}

void canSendLedData(void)
{
	CanTxMsg p;
	
	/* �������� */
	p.StdId = CAN_LEDID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_LEDA;
	p.Data[3] = CAN_LedMode;
	p.Data[4] = LedA.flag_mode;
	xQueueSend(xQueue_canTx, &p, 10);
	
	/* �������� */
	p.StdId = CAN_LEDID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_LEDA;
	p.Data[3] = CAN_LedFre;
	memcpy(p.Data+4, &(LedA.cycle), sizeof(LedA.cycle));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 10);
	
	
	/* �޸Ĳ��ּ��� */
	p.Data[2] = CAN_LEDB;
	p.Data[3] = CAN_LedMode;
	p.Data[4] = LedB.flag_mode;
	xQueueSend(xQueue_canTx, &p, 10);
	
	p.Data[2] = CAN_LEDB;
	p.Data[3] = CAN_LedFre;
	memcpy(p.Data+4, &(LedB.cycle), sizeof(LedB.cycle));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 10);
	
	
	p.Data[2] = CAN_FMQ;
	p.Data[3] = CAN_LedMode;
	p.Data[4] = Fmq.flag_mode;
	xQueueSend(xQueue_canTx, &p, 10);
	
	p.Data[2] = CAN_FMQ;
	p.Data[3] = CAN_LedFre;
	memcpy(p.Data+4, &(Fmq.cycle), sizeof(Fmq.cycle));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 10);

}



