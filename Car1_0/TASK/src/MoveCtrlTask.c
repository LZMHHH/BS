/**
  ******************************************************************************
  * @file    MoveCtrlTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   �ƶ���������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "MoveCtrlTask.h"


CLASS_Motor MotorA;
CLASS_Motor MotorB;
CLASS_Motor MotorC;
CLASS_Motor MotorD;
car_t       Car;

car_motor_e Car_Motor;


volatile TickType_t CarTickCount; //���ڼ��С���ź��ж�
volatile TickType_t CarSendDataTickCount;  //���ڶ�ʱ�ϴ�����

static void Para_Init(void);
void vCarMoveCon(void);


void vTaskMoveCtrl( void * pvParameters )
{
	/* ��ʼ������ */
	Para_Init();
	
	while(1)
	{
		
		MotorA.encoderVal = -Read_Encoder(1);
		MotorB.encoderVal = -Read_Encoder(2);
		MotorC.encoderVal =  Read_Encoder(3);
		MotorD.encoderVal =  Read_Encoder(4);
		
		vCarMoveCon();
		
		Set_Pwm(&MotorA);
		Set_Pwm(&MotorB);
		Set_Pwm(&MotorC);
		Set_Pwm(&MotorD);
		
		CarSendDataTickCount++;
		if(CarSendDataTickCount > 20)
		{
			/* ����һ���ϴ�pwm���ݵ��¼� */
			xEventGroupSetBits(Event_SendData,EVENT_MOTOR);		
			/* ����һ���ϴ����������ݵ��¼� */
			xEventGroupSetBits(Event_SendData,EVENT_ENCODER);		
			/* ����һ���ϴ�pwm���ݵ��¼� */
			xEventGroupSetBits(Event_canSendData,EVENT_canMOTOR);		
			/* ����һ���ϴ����������ݵ��¼� */
			xEventGroupSetBits(Event_canSendData,EVENT_canENCODER);		
			CarSendDataTickCount = 0;
		}
		
		vTaskDelay( 10 );
	}
	
}

static void Para_Init(void)
{
	MotorA.name = enMotorA;
	MotorB.name = enMotorB;
	MotorC.name = enMotorC;
	MotorD.name = enMotorD;
	
	MotorA.pwmout     = 0;
	MotorB.pwmout     = 0;
	MotorC.pwmout     = 0;
	MotorD.pwmout     = 0;
	
	Car_Motor         = CAR_MOTOR_PWM;
	
	CarTickCount      = 0;
	CarSendDataTickCount = 0;
	
	Set_Pwm(&MotorA);
	Set_Pwm(&MotorB);
	Set_Pwm(&MotorC);
	Set_Pwm(&MotorD);

}


void vCarMoveCon(void)
{
	if((xTaskGetTickCount() - CarTickCount) > 150 )
	{
		MotorA.pwmout = 0;
		MotorB.pwmout = 0;
		MotorC.pwmout = 0;
		MotorD.pwmout = 0;
	}
	else
	{
		MotorA.pwmout =   Car.speedX + Car.speedY - Car.speedZ;
		MotorB.pwmout =   Car.speedX + Car.speedY + Car.speedZ;
		MotorC.pwmout =  -Car.speedX + Car.speedY - Car.speedZ;
		MotorD.pwmout =  -Car.speedX + Car.speedY + Car.speedZ;
		
		MotorA.pwmout = map(MotorA.pwmout,-3000,3000,-10000,10000);
		MotorB.pwmout = map(MotorB.pwmout,-3000,3000,-10000,10000);
		MotorC.pwmout = map(MotorC.pwmout,-3000,3000,-10000,10000);
		MotorD.pwmout = map(MotorD.pwmout,-3000,3000,-10000,10000);
	}
	if(CarTickCount > xTaskGetTickCount())
	{
		CarTickCount = xTaskGetTickCount();
	}
	
}
	
/* ͨѶ */

void canSendMotorData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORA;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorA.pwmout), sizeof(MotorA.pwmout));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORB;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorB.pwmout), sizeof(MotorB.pwmout));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					/* ����sht3x���¶����� */
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORC;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorC.pwmout), sizeof(MotorC.pwmout));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORD;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorD.pwmout), sizeof(MotorD.pwmout));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
								flag = 0;	
								break;
	}
	
}	
void canSendEncoderData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORA;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorA.encoderVal), sizeof(MotorA.encoderVal));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORB;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorB.encoderVal), sizeof(MotorB.encoderVal));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					/* ����sht3x���¶����� */
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORC;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorC.encoderVal), sizeof(MotorC.encoderVal));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORD;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorD.encoderVal), sizeof(MotorD.encoderVal));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
								flag = 0;	
								break;
	}
	
}	