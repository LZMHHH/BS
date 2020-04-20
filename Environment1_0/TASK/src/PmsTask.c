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



