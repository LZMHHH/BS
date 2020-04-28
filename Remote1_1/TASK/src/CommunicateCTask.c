/**
  ******************************************************************************
  * @file    CommunicateCTask.c
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
#include "CommunicateCTask.h"


//Uart1�Ľ�������
void vTaskUart3Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    ReadBuff[DEBUG3_RX_BSIZE];  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Rx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		//���ճɹ������Ϸ���ȥ
		xReturn = xQueueSend( xQueue_uart3Tx,  /* ��Ϣ���еľ�� */
													&ReadBuff,       /* ���͵���Ϣ���� */
													0 );             /* �ȴ�ʱ�� 0 */													
		
	}
}

//Uart1�ķ�������
void vTaskUart3Tx( void * pvParameters )
{
//	u8 len;
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	msg_t      p;  /* ʵ���� ����copy����*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
//	uint8_t    SendBuff[DEBUG3_TX_BSIZE];  /* ʵ���� ����copy����*/
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Tx,           /* ��Ϣ���еľ�� */
                             &p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
										
		
		
		Uart3_DMA_SendString((u8 *)&p,
													p.dataLen + 3);	  /*  */
		
		if(LedB.flag_mode != enOFF)
		{
			digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
		}
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


