/**
  ******************************************************************************
  * @file    Checkask.c
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
#include "CheckTask.h"

#if IFFILESYSTEM

void vTaskCheck( void * pvParameters )
{
	
	u8 err;
	u8 State_SD = U_IDLE;  //SD卡的状态位：U_IDLE：已经插入。U_ING：拔出中。U_ED：拔出处理完成
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
//	uint8_t    ReadBuff[DEBUG1_RX_BSIZE];  /* 实数组 接收copy数据*/
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	while(1)
	{

		/* ======== SD 卡的热拔插检测 ======== */
		err = SD_PowerON();
		if (err != SD_OK)
		{
			if(State_SD == U_IDLE)
			{		
					/*终端提示插入SD卡*/
				xReturn = xQueueSend( xQueue_uart1Tx,  /* 消息队列的句柄 */
															"Please Check SD card!\r\n",       /* 发送的消息内容 */
															xMaxBlockTime ); /* 等待时间 0.5s */
				
				/* 本地状态位改为已处理相关操作 */
				State_SD = U_ING;
			}				
			
		}
		if(err == SD_OK && State_SD == U_ING)
		{
			/* 告诉SD卡初始化模块进行初始化 */
			xTaskNotify(xHandleTaskInit,   /* 目标任务 */
									BIT_0,             /* 设置目标任务事件标志位bit0  */
									eSetBits);         /* 将目标任务的事件标志位与BIT_0进行或操作， 
				                                      将结果赋值给事件标志位。*/
			/* 本地状态位改为已处理相关操作 */
			State_SD = U_IDLE;  //直接空闲
		}
	
	
		vTaskDelay( 800 );
	}
}


#endif


