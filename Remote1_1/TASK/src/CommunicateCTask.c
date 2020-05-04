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
	msg_t      p;  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart3Rx,           /* ��Ϣ���еľ�� */
                             (void *)&p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		/* ���� */
		msgAnalyze(&p);
									
		uart3Connect.tickCount = xTaskGetTickCount();
														 
		memset(&p, 0x00, sizeof(p));										
		
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
													p.dataLen + 4);	  /*  */
		
		if(LedB.flag_mode != enOFF)
		{
			digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
		}
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  ����Ϊֱ��can����
										����Ϊ׼����������
*****************************************************/

//�ϴ���������
void vTaskuart3SendData( void * pvParameters )
{
	EventBits_t r_event;  /* ����һ���¼����ձ��� */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_uart3SendData,  /* �¼������� */
															  EVENT_uart3CARUI
															 |EVENT_uart3CARUIREQ
															 |EVENT_uart3OLEDCLEAR,/* �����̸߳���Ȥ���¼� */
																pdTRUE,   /* �˳�ʱ����¼�λ */
																pdFALSE,   /* �������Ȥ�����һ���¼� */
																portMAX_DELAY);/* ָ����ʱ�¼�,һֱ�� */
		

		/* CARUI�����¼� */
		if((r_event & EVENT_uart3CARUIREQ) == (EVENT_uart3CARUIREQ)) 
    {		
			canSendCarUIReqCmd();
    }
		/* �����¼� */
		if((r_event & EVENT_uart3OLEDCLEAR) == (EVENT_uart3OLEDCLEAR)) 
    {		
			OLED_Fill(0,0,128,64,0);
		}
		
	}
}


