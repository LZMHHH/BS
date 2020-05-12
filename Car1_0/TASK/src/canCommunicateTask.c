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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "canCommunicateTask.h"


//Can的接收任务
void vTaskCanRx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	CanRxMsg      p;  /* 实数组 接收copy数据*/
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	canCommunicateParaInit();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canRx,           /* 消息队列的句柄 */
                             (void *)&p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
		
		
		/* 解码 */
		canmsgAnalyze(&p);
						
		canConnect.tickCount = xTaskGetTickCount();
														 
		memset(&p, 0x00, sizeof(p));
	}
}

//Can的发送任务
void vTaskCanTx( void * pvParameters )
{
	BaseType_t    xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	CanTxMsg      p;  /* 实数组 接收copy数据*/
//  const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	while(1)
	{
		xReturn = xQueueReceive( xQueue_canTx,           /* 消息队列的句柄 */
                             &p,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
										
		

		/* 发送 */
		CAN_Transmit(CAN1, &p);	
		
		
		memset(&p, 0x00, sizeof(p));
		
	}
}


/****************************************************
									  以上为直达can任务
										以下为准备数据任务
*****************************************************/
/* 声明 */
void sendLedData(void);
void sendKeyAckData(void);

//上传数据任务
void vTaskcanSendData( void * pvParameters )
{
	EventBits_t r_event;  /* 定义一个事件接收变量 */
	while(1)
	{
		 r_event = xEventGroupWaitBits(Event_canSendData,  /* 事件对象句柄 */
																EVENT_canLED
															 |EVENT_canCARPAGE0
															 |EVENT_canCARPAGE1
															 |EVENT_canCARPAGE2
															 |EVENT_canCARPAGE3
															 |EVENT_canCARUI
															 |EVENT_canMOTOR
															 |EVENT_canENCODER
															 |EVENT_canOLEDCLEAR,/* 接收线程感兴趣的事件 */
																pdTRUE,   /* 退出时清除事件位 */
																pdFALSE,   /* 满足感兴趣的如何一个事件 */
																portMAX_DELAY);/* 指定超时事件,一直等 */
		
		/* LED事件 */
		if((r_event & EVENT_canLED) == (EVENT_canLED)) 
    {		
			canSendLedData();
    }		
		/* CARUI事件 */
		if((r_event & EVENT_canCARUI) == (EVENT_canCARUI)) 
    {		
			canSendCarUIData();
    }
		/* CARUI Page 0事件 */
		if((r_event & EVENT_canCARPAGE0) == (EVENT_canCARPAGE0)) 
    {		
			canSendEncoderData();
			canSendCarData();
			canSendHwbzData();
			canSendVl53l0xData();
    }		
		/* CARUI Page 1事件 */
		if((r_event & EVENT_canCARPAGE1) == (EVENT_canCARPAGE1)) 
    {		
			canSendMotorData();
			canSendEncoderData();
			canSendHwbzData();
    }		
		/* CARUI Page 2事件 */
		if((r_event & EVENT_canCARPAGE2) == (EVENT_canCARPAGE2)) 
    {		
			canSendCarData();
			canSendVl53l0xData();
			canSendMotorPidData();
    }		
		/* CARUI Page 3事件 */
		if((r_event & EVENT_canCARPAGE3) == (EVENT_canCARPAGE3)) 
    {		
			canSendLedData();
    }		
		/* 电机事件 */
		if((r_event & EVENT_canMOTOR) == (EVENT_canMOTOR)) 
    {		
			canSendMotorData();
		}
		/* 编码器事件 */
		if((r_event & EVENT_canENCODER) == (EVENT_canENCODER)) 
    {		
			canSendEncoderData();
		}
		/* 清屏事件 */
		if((r_event & EVENT_canOLEDCLEAR) == (EVENT_canOLEDCLEAR)) 
    {		
			OLED_Fill(0,0,128,64,0);
		}
		
		
	}
}


