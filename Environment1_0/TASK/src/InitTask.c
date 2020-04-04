/**
  ******************************************************************************
  * @file    InitTask.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   类似linux中的热拔插
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "InitTask.h"

#if IFFILESYSTEM

void vTaskInit( void * pvParameters )
{
	BaseType_t xResult;
//	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(5000); /* 设置最大等待时间为500ms */
	uint32_t ulValue;
	
	while(1)
	{
		/* 接收到事件标志后进行相关操作 */
		xResult = xTaskNotifyWait(0x00000000,      
															0xFFFFFFFF,      /* 取出全部标志位 */  
															&ulValue,        /* 保存ulNotifiedValue到变量ulValue中 */
															portMAX_DELAY);  /* 最大允许延迟时间 */
		
		if( xResult == pdPASS )
		{
			/* 接收到初始化SD卡通知 */
			if((ulValue & BIT_0) != 0)
			{
				File_sys_init_rtos();
				Usar1_SendString(DEBUG1_USARTx,"SD Card reset success!\r\n");		
			}

		}

	
	}
}


#endif


