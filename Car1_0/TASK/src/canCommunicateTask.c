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
		
		
		memset(&p, 0x00, sizeof(p));
		
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
																EVENT_canLED
															 |EVENT_canCARPAGE0
															 |EVENT_canCARPAGE1
															 |EVENT_canCARPAGE2
															 |EVENT_canCARPAGE3
															 |EVENT_canCARUI
															 |EVENT_canMOTOR
															 |EVENT_canENCODER
															 |EVENT_canOLEDCLEAR,/* �����̸߳���Ȥ���¼� */
																pdTRUE,   /* �˳�ʱ����¼�λ */
																pdFALSE,   /* �������Ȥ�����һ���¼� */
																portMAX_DELAY);/* ָ����ʱ�¼�,һֱ�� */
		
		/* LED�¼� */
		if((r_event & EVENT_canLED) == (EVENT_canLED)) 
    {		
			canSendLedData();
    }		
		/* CARUI�¼� */
		if((r_event & EVENT_canCARUI) == (EVENT_canCARUI)) 
    {		
			canSendCarUIData();
    }
		/* CARUI Page 0�¼� */
		if((r_event & EVENT_canCARPAGE0) == (EVENT_canCARPAGE0)) 
    {		
			canSendEncoderData();
			canSendCarData();
			canSendHwbzData();
			canSendVl53l0xData();
    }		
		/* CARUI Page 1�¼� */
		if((r_event & EVENT_canCARPAGE1) == (EVENT_canCARPAGE1)) 
    {		
			canSendMotorData();
			canSendEncoderData();
			canSendHwbzData();
    }		
		/* CARUI Page 2�¼� */
		if((r_event & EVENT_canCARPAGE2) == (EVENT_canCARPAGE2)) 
    {		
			canSendCarData();
			canSendVl53l0xData();
			canSendMotorPidData();
    }		
		/* CARUI Page 3�¼� */
		if((r_event & EVENT_canCARPAGE3) == (EVENT_canCARPAGE3)) 
    {		
			canSendLedData();
    }		
		/* ����¼� */
		if((r_event & EVENT_canMOTOR) == (EVENT_canMOTOR)) 
    {		
			canSendMotorData();
		}
		/* �������¼� */
		if((r_event & EVENT_canENCODER) == (EVENT_canENCODER)) 
    {		
			canSendEncoderData();
		}
		/* �����¼� */
		if((r_event & EVENT_canOLEDCLEAR) == (EVENT_canOLEDCLEAR)) 
    {		
			OLED_Fill(0,0,128,64,0);
		}
		
		
	}
}


