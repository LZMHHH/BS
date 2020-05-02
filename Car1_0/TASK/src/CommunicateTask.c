/**
  ******************************************************************************
  * @file    CommunicateTask.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
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
#include "CommunicateTask.h"


//Uart1�Ľ�������
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	msg_t      p;  /* ʵ���� ����copy����*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* ��Ϣ���еľ�� */
                             (void *)&p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		
		/* ���� */
		msgAnalyze(&p);
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Uart1�ķ�������
void vTaskUart1Tx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	msg_t      p;  /* ʵ���� ����copy����*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             &p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
										
		
		
		Uart1_DMA_SendString((u8 *)&p,
													p.dataLen + 4);	  /*  */
		
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  ����Ϊֱ�ﴮ������
										����Ϊ׼����������
*****************************************************/

/* ���� */
void sendLedData(void);
void sendKeyAckData(void);

//�ϴ���������
void vTaskSendData( void * pvParameters )
{
	EventBits_t r_event;  /* ����һ���¼����ձ��� */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_SendData,  /* �¼������� */
																EVENT_MOTOR
															 |EVENT_ENCODER
															 |EVENT_LED
															 |EVENT_KEYACK,/* �����̸߳���Ȥ���¼� */
																pdTRUE,   /* �˳�ʱ����¼�λ */
																pdFALSE,   /* �������Ȥ�����һ���¼� */
																portMAX_DELAY);/* ָ����ʱ�¼�,һֱ�� */
		
		/* ����¼� */
		if((r_event & EVENT_MOTOR) == (EVENT_MOTOR)) 
    {		
			Motorpwm.pwmoutA = MotorA.pwmout;
			Motorpwm.pwmoutB = MotorB.pwmout;
			Motorpwm.pwmoutC = MotorC.pwmout;
			Motorpwm.pwmoutD = MotorD.pwmout;
			/*���͵������*/
			sendData(UP_DATA,enIDRemote, KIND_MOTOR, (u8*)&Motorpwm, sizeof(Motorpwm), 20);
    }
		/* �������¼� */
		if((r_event & EVENT_ENCODER) == (EVENT_ENCODER)) 
    {		
			Encoder.motorA = MotorA.encoderVal;
			Encoder.motorB = MotorB.encoderVal;
			Encoder.motorC = MotorC.encoderVal;
			Encoder.motorD = MotorD.encoderVal;
			/*���ͱ���������*/
			sendData(UP_DATA,enIDRemote, KIND_ENCODER, (u8*)&Encoder, sizeof(Encoder), 20);
    }
		/* LED�¼� */
		if((r_event & EVENT_LED) == (EVENT_LED)) 
    {		
			sendLedData();
    }
		/* UIACK�¼� */
		if((r_event & EVENT_KEYACK) == (EVENT_KEYACK)) 
    {		
			sendKeyAckData();
    }
		
	}
}

void sendLedData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDRemote;
	p.dataLen = 2+sizeof(LedA.flag_mode)+sizeof(LedA.cycle)+sizeof(LedB.flag_mode)+sizeof(LedB.cycle); 
	p.data[0] = enDATA;
	p.data[1] = KIND_LED;
	
	memcpy(p.data+2, 
				&(LedA.flag_mode), 1);  /* �ر����⣬���ֽ���ǰ */
	memcpy(p.data+2+1, 
				&(LedA.cycle), 4);  /* �ر����⣬���ֽ���ǰ */
	memcpy(p.data+2+1+4, 
				&(Fmq.flag_mode), 1);  /* �ر����⣬���ֽ���ǰ */
	memcpy(p.data+2+1+4+1, 
				&(Fmq.cycle), 4);  /* �ر����⣬���ֽ���ǰ */

	xQueueSend(xQueue_uart1Tx, &p, 20);
}

void sendKeyAckData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_ACK;
	p.mcuID = enIDRemote;
	p.dataLen = 2; 
	p.data[0] = enCMD;
	p.data[1] = KIND_KEY;

	xQueueSend(xQueue_uart1Tx, &p, 20);
}
