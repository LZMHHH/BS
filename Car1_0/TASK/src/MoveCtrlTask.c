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
CLASS_Pid   MotorAllPID;



volatile TickType_t CarTickCount; //用于检测小车信号中断
volatile TickType_t CarSendDataTickCount;  //用于定时上传数据
/* 自动模式 */
volatile TickType_t MotorATickCount;  
volatile TickType_t MotorBTickCount; 
volatile TickType_t MotorCTickCount; 
volatile TickType_t MotorDTickCount; 

static void Para_Init(void);
void vCarMoveCon(void);
void hwbz_scan(void);

void vTaskMoveCtrl( void * pvParameters )
{
	/* 初始化参数 */
	Para_Init();
	
	while(1)
	{
		
		MotorA.encoderVal = -Read_Encoder(4);
		MotorB.encoderVal = -Read_Encoder(2);
		MotorC.encoderVal =  Read_Encoder(3);
		MotorD.encoderVal =  Read_Encoder(1);
		
		hwbz_scan();
		
		
		vCarMoveCon();
		
		Set_Pwm(&MotorA);
		Set_Pwm(&MotorB);
		Set_Pwm(&MotorC);
		Set_Pwm(&MotorD);
		
		CarSendDataTickCount++;
		if(CarSendDataTickCount > 20)
		{
//			/* 触发一个上传pwm数据的事件 */
//			xEventGroupSetBits(Event_SendData,EVENT_MOTOR);		
//			/* 触发一个上传编码器数据的事件 */
//			xEventGroupSetBits(Event_SendData,EVENT_ENCODER);		
//			/* 触发一个上传pwm数据的事件 */
//			xEventGroupSetBits(Event_canSendData,EVENT_canMOTOR);		
//			/* 触发一个上传编码器数据的事件 */
//			xEventGroupSetBits(Event_canSendData,EVENT_canENCODER);		
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
	
	
	Car.mode          = enPWM;
	Car.flag          = enMOVE;
	Car.MaxPwm        = 10000;
	
	CarTickCount      = 0;
	CarSendDataTickCount = 0;
	
	Set_Pwm(&MotorA);
	Set_Pwm(&MotorB);
	Set_Pwm(&MotorC);
	Set_Pwm(&MotorD);

}

void hwbz_scan(void)
{
	if(Hwbz_Pre(Hwbz_LD))
		Hwbz_LD.status =  HWBZ_TURE;
	else
		Hwbz_LD.status =  HWBZ_FALSE;
	if(Hwbz_Pre(Hwbz_LU))
		Hwbz_LU.status =  HWBZ_TURE;
	else
		Hwbz_LU.status =  HWBZ_FALSE;
	if(Hwbz_Pre(Hwbz_RU))
		Hwbz_RU.status =  HWBZ_TURE;
	else
		Hwbz_RU.status =  HWBZ_FALSE;
	if(Hwbz_Pre(Hwbz_RD))
		Hwbz_RD.status =  HWBZ_TURE;
	else
		Hwbz_RD.status =  HWBZ_FALSE;
}

/* 控制 */
void vPwmModeCon(void)
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
		MotorA.pwmout =   -Car.speedX + Car.speedY + Car.speedZ;
		MotorB.pwmout =    Car.speedX + Car.speedY + Car.speedZ;
		MotorC.pwmout =   -Car.speedX + Car.speedY - Car.speedZ;
		MotorD.pwmout =    Car.speedX + Car.speedY - Car.speedZ;
		
		MotorA.pwmout = map(MotorA.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorB.pwmout = map(MotorB.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorC.pwmout = map(MotorC.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorD.pwmout = map(MotorD.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
	}
	if(CarTickCount > xTaskGetTickCount())
	{
		CarTickCount = xTaskGetTickCount();
	}
	
	if((Hwbz_LD.status == 1 && MotorA.pwmout < 0)
	 ||(Hwbz_LU.status == 1 && MotorB.pwmout > 0)
	 ||(Hwbz_RD.status == 1 && MotorC.pwmout < 0)
	 ||(Hwbz_RU.status == 1 && MotorD.pwmout > 0))
		Car.flag          = enSTOP;
	else
	{
		Car.flag          = enMOVE;
	}
	
	if(Car.flag == enSTOP)
	{
		MotorA.pwmout = 0;
		MotorB.pwmout = 0;
		MotorC.pwmout = 0;
		MotorD.pwmout = 0;
	}
}
void vPwmSelfModeCon(void)
{

	if((xTaskGetTickCount() - CarTickCount) > 150 )
	{
		if(Hwbz_LD.status == 1)
		{
			MotorATickCount = xTaskGetTickCount()+1000;
		}
		if(Hwbz_LU.status == 1)
		{
			MotorBTickCount = xTaskGetTickCount()+1000;
		}
		if(Hwbz_RU.status == 1)
		{
			MotorCTickCount = xTaskGetTickCount()+1000;
		}
		if(Hwbz_RD.status == 1)
		{
			MotorDTickCount = xTaskGetTickCount()+1000;
		}
		

		if(xTaskGetTickCount() < MotorBTickCount || xTaskGetTickCount() < MotorCTickCount)
		{
			if(xTaskGetTickCount() < MotorBTickCount)
			{
				MotorA.pwmout = -1500;
				MotorB.pwmout = -1500;
				MotorC.pwmout = -4500;
				MotorD.pwmout = -4500;
			}
			else
			{
				MotorA.pwmout = -4500;
				MotorB.pwmout = -4500;
				MotorC.pwmout = -1500;
				MotorD.pwmout = -1500;
			}
		}
		else
		{
			MotorA.pwmout = 3500;
			MotorB.pwmout = 3500;
			MotorC.pwmout = 3500;
			MotorD.pwmout = 3500;
		}

		if((Hwbz_LD.status == 1 && MotorA.pwmout < 0)
		 ||(Hwbz_RU.status == 1 && MotorD.pwmout > 0))
			Car.flag          = enSTOP;
		else
		{
			Car.flag          = enMOVE;
		}
		
		if(Car.flag == enSTOP)
		{
			MotorA.pwmout = 0;
			MotorB.pwmout = 0;
			MotorC.pwmout = 0;
			MotorD.pwmout = 0;
		}
	}
	else
	{
		MotorA.pwmout =   -Car.speedX + Car.speedY + Car.speedZ;
		MotorB.pwmout =    Car.speedX + Car.speedY + Car.speedZ;
		MotorC.pwmout =   -Car.speedX + Car.speedY - Car.speedZ;
		MotorD.pwmout =    Car.speedX + Car.speedY - Car.speedZ;
		
		MotorA.pwmout = map(MotorA.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorB.pwmout = map(MotorB.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorC.pwmout = map(MotorC.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
		MotorD.pwmout = map(MotorD.pwmout,-3000,3000,-Car.MaxPwm,Car.MaxPwm);
	}
	if(CarTickCount > xTaskGetTickCount())
	{
		CarTickCount = xTaskGetTickCount();
	}
	
	if((Hwbz_LD.status == 1 && MotorA.pwmout < 0)
	 ||(Hwbz_LU.status == 1 && MotorB.pwmout > 0)
	 ||(Hwbz_RD.status == 1 && MotorC.pwmout < 0)
	 ||(Hwbz_RU.status == 1 && MotorD.pwmout > 0))
		Car.flag          = enSTOP;
	else
	{
		Car.flag          = enMOVE;
	}
	
	if(Car.flag == enSTOP)
	{
		MotorA.pwmout = 0;
		MotorB.pwmout = 0;
		MotorC.pwmout = 0;
		MotorD.pwmout = 0;
	}
}
void vCarMoveCon(void)
{
	switch(Car.mode)
	{
		case enPWM:
					vPwmModeCon();
					break;
		case enPWMSelf:
					vPwmSelfModeCon();
					break;
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
void uart1SendMotorData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_MOTOR;
	memcpy(p.data+2, &(MotorA.pwmout), 4);  /* 特别留意，低字节在前 */
	memcpy(p.data+6, &(MotorB.pwmout), 4);
	memcpy(p.data+10, &(MotorC.pwmout), 4);
	memcpy(p.data+14, &(MotorD.pwmout), 4);
	xQueueSend(xQueue_uart1Tx, &p, 10);
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
void uart1SendEncoderData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_ENCODER;
	memcpy(p.data+2, &(MotorA.encoderVal), 4);  /* 特别留意，低字节在前 */
	memcpy(p.data+6, &(MotorB.encoderVal), 4);
	memcpy(p.data+10, &(MotorC.encoderVal), 4);
	memcpy(p.data+14, &(MotorD.encoderVal), 4);
	xQueueSend(xQueue_uart1Tx, &p, 10);
}	
void canSendCarData(void)
{
	
	CanTxMsg p;

	p.StdId = CAN_CARDATAID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
	p.Data[1] = enDATA;
	p.Data[2] = CAN_EMPTY;
	p.Data[3] = CAN_MODE;
	p.Data[4] = Car.mode;
	xQueueSend(xQueue_canTx, &p, 10);

	p.Data[3] = CAN_MaxVal;
	memcpy(p.Data+4, &(Car.MaxPwm), sizeof(Car.MaxPwm));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);
	
}	
void uart1SendCarData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 1+2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_CARDATA;
	p.data[2] = Car.mode;
	memcpy(p.data+3, &(Car.MaxPwm), 2);  
	xQueueSend(xQueue_uart1Tx, &p, 10);
}	
void canSendMotorPidData(void)
{
	int intdata;
	
	CanTxMsg p;

	p.StdId = CAN_MOTORID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
	p.Data[1] = enDATA;
	p.Data[2] = CAN_CARMOTOR;
	p.Data[3] = CAN_P;
	intdata = (int)((MotorAllPID.p)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);
	
	p.Data[3] = CAN_I;
	intdata = (int)((MotorAllPID.i)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);
	
	p.Data[3] = CAN_D;
	intdata = (int)((MotorAllPID.d)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 10);
	
}
void uart1SendMotorPidData(void)
{
	int intdata;
	
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 4*3 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_MOTORPID;
	intdata = (int)((MotorAllPID.p)*100);
	memcpy(p.data+2, &(intdata), 4);  /* 特别留意，低字节在前 */
	intdata = (int)((MotorAllPID.i)*100);
	memcpy(p.data+6, &(intdata), 4);
	intdata = (int)((MotorAllPID.d)*100);
	memcpy(p.data+10, &(intdata), 4);
	xQueueSend(xQueue_uart1Tx, &p, 10);
}	
void canSendHwbzData(void)
{

	CanTxMsg p;

	p.StdId = CAN_BZID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
	p.Data[1] = enDATA;
	p.Data[2] = CAN_HWBZ;
	p.Data[3] = CAN_Empty;
	p.Data[4] = Hwbz_LD.status;   
	p.Data[5] = Hwbz_LU.status;
	p.Data[6] = Hwbz_RU.status;
	p.Data[7] = Hwbz_RD.status;
	xQueueSend(xQueue_canTx, &p, 10);
	
}
void uart1SendHwbzData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = 4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_HWBZ;
	p.data[2] = Hwbz_LD.status;   
	p.data[3] = Hwbz_LU.status;   
	p.data[4] = Hwbz_RU.status;   
	p.data[5] = Hwbz_RD.status;   	
	xQueueSend(xQueue_uart1Tx, &p, 10);
}	


