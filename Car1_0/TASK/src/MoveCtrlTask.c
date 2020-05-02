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
		
		MotorA.pwmout = map(MotorA.pwmout,-3000,3000,-7200,7200);
		MotorB.pwmout = map(MotorB.pwmout,-3000,3000,-7200,7200);
		MotorC.pwmout = map(MotorC.pwmout,-3000,3000,-7200,7200);
		MotorD.pwmout = map(MotorD.pwmout,-3000,3000,-7200,7200);
	}
	
	
	
	
}
	

