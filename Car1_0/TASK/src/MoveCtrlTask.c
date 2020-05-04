/**
  ******************************************************************************
  * @file    MoveCtrlTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   移动控制任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
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


volatile TickType_t CarTickCount; //用于检测小车信号中断
volatile TickType_t CarSendDataTickCount;  //用于定时上传数据

static void Para_Init(void);
void vCarMoveCon(void);


void vTaskMoveCtrl( void * pvParameters )
{
	/* 初始化参数 */
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
			/* 触发一个上传pwm数据的事件 */
			xEventGroupSetBits(Event_SendData,EVENT_MOTOR);		
			/* 触发一个上传编码器数据的事件 */
			xEventGroupSetBits(Event_SendData,EVENT_ENCODER);		
			/* 触发一个上传pwm数据的事件 */
			xEventGroupSetBits(Event_canSendData,EVENT_canMOTOR);		
			/* 触发一个上传编码器数据的事件 */
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
	
/* 通讯 */

void canSendMotorData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORA;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorA.pwmout), sizeof(MotorA.pwmout));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORB;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorB.pwmout), sizeof(MotorB.pwmout));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORC;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorC.pwmout), sizeof(MotorC.pwmout));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORD;
					p.Data[3] = CAN_PwmOut;
					memcpy(p.Data+4, &(MotorD.pwmout), sizeof(MotorD.pwmout));  /* 特别留意，低字节在前 */
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
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORA;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorA.encoderVal), sizeof(MotorA.encoderVal));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORB;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorB.encoderVal), sizeof(MotorB.encoderVal));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					/* 发送sht3x的温度数据 */
					p.StdId = CAN_MOTORID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARMOTORC;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorC.encoderVal), sizeof(MotorC.encoderVal));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_CARMOTORD;
					p.Data[3] = CAN_Encoder;
					memcpy(p.Data+4, &(MotorD.encoderVal), sizeof(MotorD.encoderVal));  /* 特别留意，低字节在前 */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
								flag = 0;	
								break;
	}
	
}	