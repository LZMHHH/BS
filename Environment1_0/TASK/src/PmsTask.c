/**
  ******************************************************************************
  * @file    PmsTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
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
#include "PmsTask.h"

CLASS_Pms Pms; 

void canSendPmsData(void);
void UpdataPms(uint8_t *databuff,CLASS_Pms *pms);


void vTaskPms( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    ReadBuff[DEBUG2_RX_BSIZE];  /* ʵ���� ����copy����*/\
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart2Rx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */

														 
		UpdataPms(ReadBuff,&Pms);
					
		/* ��Ϊpms������200-800ms�ŷ���һ���������������ԣ�����ֱ��can��ȥ */
		canSendPmsData();

	}
	
}

void UpdataPms(uint8_t *databuff,CLASS_Pms *pms)
{
	if(databuff[0] == 0x42)
	{
		if(databuff[1] == 0x4d)
		{
			 pms->PM2_5_Vol = (databuff[12] << 8) | databuff[13];
			 pms->PM10_Vol  = (databuff[14] << 8) | databuff[15]; 
		}
	}
}


void canSendPmsData(void)
{
	u16 u16data;
	
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
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM2_5;
	u16data = (u16)(Pms.PM2_5_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* ����sht3x���¶����� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
  p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM10;
	u16data = (u16)(Pms.PM10_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
}

