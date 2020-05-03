/**
  ******************************************************************************
  * @file    BmeTask.c
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
#include "BmeTask.h"

CLASS_Bme       Bme;

static void Para_Init(void);
void canSendBMEData(void);


void vTaskBme( void * pvParameters )
{
	/* ��ʼ������ */
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
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Pressure;
	intdata = (int)((Bme.pressure)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Hight;
	intdata = (int)((Bme.asl)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Temperature;
	intdata = (int)((Bme.temperature)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_BME;
	p.Data[3] = CAN_Humidity;
	intdata = (int)((Bme.humidity)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
}


