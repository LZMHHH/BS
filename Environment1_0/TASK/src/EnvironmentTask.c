/**
  ******************************************************************************
  * @file    EnvironmentTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ��ͨ�������ݲɼ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "EnvironmentTask.h"

CLASS_Huimiture Huimiture;

static void Para_Init(void);
void canSendSht3xData(void);

volatile TickType_t EnvTickCount; //�����ϱ����ݵļ�ʱ

void vTaskEnvironment( void * pvParameters )
{
	
	
	
	/* ��ʼ������ */
	Para_Init();
	
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		
		if(xTaskGetTickCount() > (EnvTickCount+100))
		{
			canSendSht3xData();
			EnvTickCount = xTaskGetTickCount();
		}
		if(EnvTickCount > xTaskGetTickCount())
		{
			EnvTickCount = xTaskGetTickCount();
		}
		
		vTaskDelay( 20 );
	}
	
}


static void Para_Init(void)
{
	EnvTickCount = xTaskGetTickCount();
}

void canSendSht3xData(void)
{
	int intdata;
	CanTxMsg p;
	
	/* ����sht3x���¶����� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_SHTX;
	p.Data[3] = CAN_Temperature;
	intdata = (int)((Huimiture.temperature)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* ����sht3x��ʪ������ */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_SHTX;
	p.Data[3] = CAN_Humidity;
	intdata = (int)((Huimiture.huimidity)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
}


