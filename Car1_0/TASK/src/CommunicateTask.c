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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "CommunicateTask.h"


//Uart1的接收任务
void vTaskUart1Rx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Rx,           /* 消息队列的句柄 */
                             (void *)&p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		
		/* 解码 */
		msgAnalyze(&p);
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Uart1的发送任务
void vTaskUart1Tx( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	msg_t      p;  /* 实数组 接收copy数据*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             &p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
		
		
		Uart1_DMA_SendString((u8 *)&p,
													p.dataLen + 4);	  /*  */
		
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  以上为直达串口任务
										以下为准备数据任务
*****************************************************/

/* 声明 */
void sendLedData(void);
void sendKeyAckData(void);

//上传数据任务
void vTaskSendData( void * pvParameters )
{
	EventBits_t r_event;  /* 定义一个事件接收变量 */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_SendData,  /* 事件对象句柄 */
																EVENT_MOTOR
															 |EVENT_ENCODER
															 |EVENT_LED
															 |EVENT_KEYACK,/* 接收线程感兴趣的事件 */
																pdTRUE,   /* 退出时清除事件位 */
																pdFALSE,   /* 满足感兴趣的如何一个事件 */
																portMAX_DELAY);/* 指定超时事件,一直等 */
		
		/* 电机事件 */
		if((r_event & EVENT_MOTOR) == (EVENT_MOTOR)) 
    {		
			Motorpwm.pwmoutA = MotorA.pwmout;
			Motorpwm.pwmoutB = MotorB.pwmout;
			Motorpwm.pwmoutC = MotorC.pwmout;
			Motorpwm.pwmoutD = MotorD.pwmout;
			/*发送电机数据*/
			sendData(UP_DATA,enIDRemote, KIND_MOTOR, (u8*)&Motorpwm, sizeof(Motorpwm), 20);
    }
		/* 编码器事件 */
		if((r_event & EVENT_ENCODER) == (EVENT_ENCODER)) 
    {		
			Encoder.motorA = MotorA.encoderVal;
			Encoder.motorB = MotorB.encoderVal;
			Encoder.motorC = MotorC.encoderVal;
			Encoder.motorD = MotorD.encoderVal;
			/*发送编码器数据*/
			sendData(UP_DATA,enIDRemote, KIND_ENCODER, (u8*)&Encoder, sizeof(Encoder), 20);
    }
		/* LED事件 */
		if((r_event & EVENT_LED) == (EVENT_LED)) 
    {		
			sendLedData();
    }
		/* UIACK事件 */
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
				&(LedA.flag_mode), 1);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1, 
				&(LedA.cycle), 4);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1+4, 
				&(Fmq.flag_mode), 1);  /* 特别留意，低字节在前 */
	memcpy(p.data+2+1+4+1, 
				&(Fmq.cycle), 4);  /* 特别留意，低字节在前 */

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
