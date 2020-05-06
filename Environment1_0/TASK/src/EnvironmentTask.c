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
CLASS_Gas       Smog;
CLASS_Gas       Hydrogen;
CLASS_Gas       CO;


static void Para_Init(void);
			 void UpGasData(void);
			 void canSendSht3xData(void);
			 void canSendGasData(void);


volatile TickType_t EnvTickCount; //�����ϱ����ݵļ�ʱ

void vTaskEnvironment( void * pvParameters )
{
	
	
	
	/* ��ʼ������ */
	Para_Init();
	
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		UpGasData();
		
		
		if(xTaskGetTickCount() > (EnvTickCount+100))
		{
			canSendSht3xData();
			vTaskDelay( 10 );
			canSendGasData();
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
	
	Huimiture.temp_offset = 0;
	Huimiture.huim_offset = 0;
	Huimiture.tempAdd_shieldVal = 10;
	Huimiture.tempRed_shieldVal = 25;
	Huimiture.huim_shieldVal    = 60;
	Huimiture.tempAdd_mode = enOFF;
	Huimiture.tempRed_mode = enOFF;
	Huimiture.huim_mode    = enOFF;
	
	
	Smog.PriVal  = 0;
	Smog.ShieldVal = 2000;
	Hydrogen.PriVal  = 0;
	Hydrogen.ShieldVal = 2000;
	CO.PriVal  = 0;
	CO.ShieldVal = 2000;
	
	
}

void UpGasData(void)
{
	
	Smog.PriVal      = getAdcValue(ADC_GASA);
	Hydrogen.PriVal  = getAdcValue(ADC_GASB);
	CO.PriVal        = getAdcValue(ADC_GASC);
	
}


/* ͨѶ */
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

void canSendGasData(void)
{
	CanTxMsg p;
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_MQ2;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(Smog.PriVal), sizeof(Smog.PriVal));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[2] = CAN_MQ8;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(Hydrogen.PriVal), sizeof(Hydrogen.PriVal));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[2] = CAN_MQ7;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(CO.PriVal), sizeof(CO.PriVal));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
}
