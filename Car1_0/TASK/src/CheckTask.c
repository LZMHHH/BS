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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "CheckTask.h"

#if IFFILESYSTEM

void vTaskCheck( void * pvParameters )
{
	
	u8 err;
	u8 State_SD = U_IDLE;  //SD����״̬λ��U_IDLE���Ѿ����롣U_ING���γ��С�U_ED���γ��������
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
//	uint8_t    ReadBuff[DEBUG1_RX_BSIZE];  /* ʵ���� ����copy����*/
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	while(1)
	{

		/* ======== SD �����Ȱβ��� ======== */
		err = SD_PowerON();
		if (err != SD_OK)
		{
			if(State_SD == U_IDLE)
			{		
					/*�ն���ʾ����SD��*/
				xReturn = xQueueSend( xQueue_uart1Tx,  /* ��Ϣ���еľ�� */
															"Please Check SD card!\r\n",       /* ���͵���Ϣ���� */
															xMaxBlockTime ); /* �ȴ�ʱ�� 0.5s */
				
				/* ����״̬λ��Ϊ�Ѵ�����ز��� */
				State_SD = U_ING;
			}				
			
		}
		if(err == SD_OK && State_SD == U_ING)
		{
			/* ����SD����ʼ��ģ����г�ʼ�� */
			xTaskNotify(xHandleTaskInit,   /* Ŀ������ */
									BIT_0,             /* ����Ŀ�������¼���־λbit0  */
									eSetBits);         /* ��Ŀ��������¼���־λ��BIT_0���л������ 
				                                      �������ֵ���¼���־λ��*/
			/* ����״̬λ��Ϊ�Ѵ�����ز��� */
			State_SD = U_IDLE;  //ֱ�ӿ���
		}
	
	
		vTaskDelay( 800 );
	}
}


#endif


