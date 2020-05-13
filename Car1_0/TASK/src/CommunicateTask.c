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
	
	CommunicateParaInit();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* ��Ϣ���еľ�� */
                             (void *)&p,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
		
		
		/* ���� */
		msgAnalyze(&p);
				
		uart1Connect.tickCount = xTaskGetTickCount();
														 
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
															 |EVENT_KEYACK
															 |EVENT_uart1CARUI
															 |EVENT_uart1ENVUI
															 |EVENT_uart1SHT3X
															 |EVENT_uart1GY30
															 |EVENT_uart1PMS
															 |EVENT_uart1BME
															 |EVENT_uart1CARPAGE0
															 |EVENT_uart1CARPAGE1
															 |EVENT_uart1CARPAGE2
															 |EVENT_uart1CARPAGE3
															 |EVENT_uart1ENVPAGE0
															 |EVENT_uart1ENVPAGE1
															 |EVENT_uart1ENVPAGE2
															 |EVENT_uart1ENVPAGE3
															 |EVENT_uart1ENVPAGE4
															 |EVENT_uart1ENVPAGE5,/* �����̸߳���Ȥ���¼� */
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
//			sendData(UP_DATA,enIDCar, KIND_MOTOR, (u8*)&Motorpwm, sizeof(Motorpwm), 20);
    }
		/* �������¼� */
		if((r_event & EVENT_ENCODER) == (EVENT_ENCODER)) 
    {		
			Encoder.motorA = MotorA.encoderVal;
			Encoder.motorB = MotorB.encoderVal;
			Encoder.motorC = MotorC.encoderVal;
			Encoder.motorD = MotorD.encoderVal;
			/*���ͱ���������*/
//			sendData(UP_DATA,enIDCar, KIND_ENCODER, (u8*)&Encoder, sizeof(Encoder), 20);
    }
		/* LED�¼� */
		if((r_event & EVENT_LED) == (EVENT_LED)) 
    {		
			uart1SendLedData(20);
    }
		/* UIACK�¼� */
		if((r_event & EVENT_KEYACK) == (EVENT_KEYACK)) 
    {		
			sendKeyAckData();
    }
		/* ENVUI�¼� */
		if((r_event & EVENT_uart1CARUI) == (EVENT_uart1CARUI)) 
    {		
			SendCarUIData();
    }
		/* ENVUI�¼� */
		if((r_event & EVENT_uart1ENVUI) == (EVENT_uart1ENVUI)) 
    {		
			SendEnvUIData();
    }
		/* EVENT_uart1SHT3X�¼� */
		if((r_event & EVENT_uart1SHT3X) == (EVENT_uart1SHT3X)) 
    {		
			uart1SendSht3xData(20);
    }
		/* EVENT_uart1GY30�¼� */
		if((r_event & EVENT_uart1GY30) == (EVENT_uart1GY30)) 
    {		
			uart1SendGy30Data(20);
    }
		/* EVENT_uart1PMS�¼� */
		if((r_event & EVENT_uart1PMS) == (EVENT_uart1PMS)) 
    {		
			uart1SendPmsData(20);
    }
		/* EVENT_uart1BME�¼� */
		if((r_event & EVENT_uart1BME) == (EVENT_uart1BME)) 
    {		
			uart1SendBmeData(20);
    }
		/* CARUI Page 0�¼� */
		if((r_event & EVENT_uart1CARPAGE0) == (EVENT_uart1CARPAGE0)) 
    {		
			uart1SendEncoderData();
			vTaskDelay( 5 );
			uart1SendHwbzData();
			vTaskDelay( 10 );
			uart1SendCarData();
			vTaskDelay( 10 );
			uart1SendVl53l0xData();
		}
		/* CARUI Page 1�¼� */
		if((r_event & EVENT_uart1CARPAGE1) == (EVENT_uart1CARPAGE1)) 
    {		
			uart1SendEncoderData();
			vTaskDelay( 5 );
			uart1SendHwbzData();
		}
		/* CARUI Page 2�¼� */
		if((r_event & EVENT_uart1CARPAGE2) == (EVENT_uart1CARPAGE2)) 
    {	
			uart1SendCarData();
			vTaskDelay( 5 );
			uart1SendVl53l0xData();		
			vTaskDelay( 10 );
			uart1SendMotorPidData();
		}
		/* CARUI Page 3�¼� */
		if((r_event & EVENT_uart1CARPAGE3) == (EVENT_uart1CARPAGE3)) 
    {		
			uart1SendLedData(20);
		}
		/* ENVUI Page 0�¼� */
		if((r_event & EVENT_uart1ENVPAGE0) == (EVENT_uart1ENVPAGE0)) 
    {		
			uart1SendClockData(20);
			vTaskDelay( 5 );
			uart1SendHuimitureData(20);
			vTaskDelay( 5 );
			uart1SendPmsData(20);
			vTaskDelay( 5 );
			uart1SendBmeData(20);
		}
		/* ENVUI Page 1�¼� */
		if((r_event & EVENT_uart1ENVPAGE1) == (EVENT_uart1ENVPAGE1)) 
    {		
			uart1SendClockData(20);
			vTaskDelay( 5 );
			uart1SendHuimitureData(20);
			vTaskDelay( 10 );
			uart1SendGy30Data(20);
			vTaskDelay( 10 );
			uart1SendPmsData(20);
			vTaskDelay( 10 );
			uart1SendBmeData(20);
			vTaskDelay( 10 );
			uart1SendSmogData(20);
			vTaskDelay( 10 );
			uart1SendHydrogenData(20);
			vTaskDelay( 10 );
			uart1SendCOData(20);
		}
		/* ENVUI Page 2�¼� */
		if((r_event & EVENT_uart1ENVPAGE2) == (EVENT_uart1ENVPAGE2)) 
    {		
			uart1SendClockData(20);
			vTaskDelay( 5 );
			uart1SendSht3xData(20);
			vTaskDelay( 10 );
			uart1SendGy30Data(20);
			vTaskDelay( 10 );
			uart1SendPmsData(20);
			vTaskDelay( 10 );
			uart1SendBmeData(20);
			vTaskDelay( 10 );
			uart1SendSmogData(20);
			vTaskDelay( 10 );
			uart1SendHydrogenData(20);
			vTaskDelay( 10 );
			uart1SendCOData(20);
		}
		/* ENVUI Page 3�¼� */
		if((r_event & EVENT_uart1ENVPAGE3) == (EVENT_uart1ENVPAGE3)) 
    {		
			uart1SendClockData(20);
			vTaskDelay( 5 );
			uart1SendLedData(20);
		}
		/* ENVUI Page 4�¼� */
		if((r_event & EVENT_uart1ENVPAGE4) == (EVENT_uart1ENVPAGE4)) 
    {		
			uart1SendClockData(20);
			vTaskDelay( 5 );
			uart1SendSetClockData(20);
		}
		/* ENVUI Page 5�¼� */
		if((r_event & EVENT_uart1ENVPAGE5) == (EVENT_uart1ENVPAGE5)) 
    {		
			uart1SendSht3xData(20);
			vTaskDelay( 5 );
			uart1SendGy30Data(20);
			vTaskDelay( 10 );
			uart1SendPmsData(20);
		}
		
	}
}



void sendKeyAckData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_ACK;
	p.mcuID = enIDCar;
	p.dataLen = 2; 
	p.data[0] = enCMD;
	p.data[1] = KIND_CARKEY;

	xQueueSend(xQueue_uart1Tx, &p, 20);
}
