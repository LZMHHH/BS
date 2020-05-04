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
		 r_event = xEventGroupWaitBits(Event_canSendData,  /* �¼������� */
																EVENT_canSHT3X
															 |EVENT_canGY30
															 |EVENT_canPMS
															 |EVENT_canBME
															 |EVENT_canLED
															 |EVENT_canCARUI
															 |EVENT_canCARUIREQ
															 |EVENT_canOLEDCLEAR,/* �����̸߳���Ȥ���¼� */
																pdTRUE,   /* �˳�ʱ����¼�λ */
																pdFALSE,   /* �������Ȥ�����һ���¼� */
																portMAX_DELAY);/* ָ����ʱ�¼�,һֱ�� */
		
		/* LED�¼� */
		if((r_event & EVENT_canLED) == (EVENT_canLED)) 
    {		
			canSendLedData();
    }
		
//		/* CARUI�¼����´����ݣ� */
//		if((r_event & EVENT_canCARUI) == (EVENT_canCARUI)) 
//    {		
//			canSendCarUIData();
//    }
		/* CARUI�����¼� */
		if((r_event & EVENT_canCARUIREQ) == (EVENT_canCARUIREQ)) 
    {		
			canSendCarUIReqCmd();
    }
		/* �����¼� */
		if((r_event & EVENT_canOLEDCLEAR) == (EVENT_canOLEDCLEAR)) 
    {		
			OLED_Fill(0,0,128,64,0);
		}
		
	}
}



