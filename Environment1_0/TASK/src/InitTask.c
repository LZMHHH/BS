/**
  ******************************************************************************
  * @file    InitTask.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   ����linux�е��Ȱβ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "InitTask.h"

#if IFFILESYSTEM

void vTaskInit( void * pvParameters )
{
	BaseType_t xResult;
//	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(5000); /* �������ȴ�ʱ��Ϊ500ms */
	uint32_t ulValue;
	
	while(1)
	{
		/* ���յ��¼���־�������ز��� */
		xResult = xTaskNotifyWait(0x00000000,      
															0xFFFFFFFF,      /* ȡ��ȫ����־λ */  
															&ulValue,        /* ����ulNotifiedValue������ulValue�� */
															portMAX_DELAY);  /* ��������ӳ�ʱ�� */
		
		if( xResult == pdPASS )
		{
			/* ���յ���ʼ��SD��֪ͨ */
			if((ulValue & BIT_0) != 0)
			{
				File_sys_init_rtos();
				Usar1_SendString(DEBUG1_USARTx,"SD Card reset success!\r\n");		
			}

		}

	
	}
}


#endif


