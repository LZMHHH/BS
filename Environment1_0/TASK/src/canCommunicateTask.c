/**
  ******************************************************************************
  * @file    canCommunicateTask.c
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
#include "canCommunicateTask.h"

static void Led_ComCtrl(void);

//Can�Ľ�������
void vTaskCanRx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	CanRxMsg      p;  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	canCommunicateParaInit();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canRx,           /* ��Ϣ���еľ�� */
                             (void *)&p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		
		/* ���� */
		canmsgAnalyze(&p);
					
		Led_ComCtrl();
		canConnect.tickCount = xTaskGetTickCount();
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Can�ķ�������
void vTaskCanTx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	CanTxMsg      p;  /* ʵ���� ����copy����*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canTx,           /* ��Ϣ���еľ�� */
                             &p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
										
		

		/* ���� */
		CAN_Transmit(CAN1, &p);	
		
		Led_ComCtrl();
		
		memset(&p, 0x00, sizeof(p));
		
	}
}

static void Led_ComCtrl(void)
{
	if(LedA.flag_mode == enCom)
	{
		digitalToggle(LedA.config.gpio_port,LedA.config.gpio_pin);
	}
	if(LedB.flag_mode == enCom)
	{
		digitalToggle(LedB.config.gpio_port,LedB.config.gpio_pin);
	}
	
}

/****************************************************
									  ����Ϊֱ��can����
										����Ϊ׼����������
*****************************************************/
/* ���� */
void sendLedData(void);
void sendKeyAckData(void);

//�ϴ���������
void vTaskcanSendData( void * pvParameters )
{
	EventBits_t r_event;  /* ����һ���¼����ձ��� */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_SendData,  /* �¼������� */
																EVENT_SHT3X
															 |EVENT_GY30
															 |EVENT_PMS
															 |EVENT_BME
															 |EVENT_LED,/* �����̸߳���Ȥ���¼� */
																pdTRUE,   /* �˳�ʱ����¼�λ */
																pdFALSE,   /* �������Ȥ�����һ���¼� */
																portMAX_DELAY);/* ָ����ʱ�¼�,һֱ�� */
		
		/* LED�¼� */
		if((r_event & EVENT_LED) == (EVENT_LED)) 
    {		
			canSendLedData();
    }
		
		
	}
}



