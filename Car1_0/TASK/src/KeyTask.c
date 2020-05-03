/**
  ******************************************************************************
  * @file    KeyTask.c
  * @author  fire
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
#include "KeyTask.h"

//����
void Key_Control(void);
void Status_Scan(void);

void vTaskKey( void * pvParameters )
{
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		Key_Scan(&Key_PL);
		Key_Scan(&Key_PR);
		Key_Scan(&Key_PM);
		
		
		Status_Scan();
		
		vTaskDelay( 10 );
	}
	
}


//����-����-----------------------------------------------------------------------------
void  Key_Control(void)
{
	//�ϼ�������
	if(Key_PU.Key_RetVal == enKey_Click)
	{
		;
	}

	
}


void Status_Scan(void)
{
	
	/* uart1 */
	if((xTaskGetTickCount() - 300) > uart1Connect.tickCount)
	{
		uart1Connect.status = enBreak;
	}
	else
	{
		uart1Connect.status = enSig3;
	}
	if(uart1Connect.tickCount > xTaskGetTickCount())
	{
		uart1Connect.tickCount = xTaskGetTickCount();
	}
	
	/* can */
	if((xTaskGetTickCount() - 300) > canConnect.tickCount)
	{
		canConnect.status = enBreak;
	}
	else
	{
		canConnect.status = enSig3;
	}
	if(canConnect.tickCount > xTaskGetTickCount())
	{
		canConnect.tickCount = xTaskGetTickCount();
	}
	
}





