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
void Signal_Scan(void);


void vTaskKey( void * pvParameters )
{
	
	while(1)
	{
		Key_Scan(&Key_PU);
		Key_Scan(&Key_PD);
		Key_Scan(&Key_PL);
		Key_Scan(&Key_PR);
		Key_Scan(&Key_PM);
		Key_Scan(&Key_PA);
		Key_Scan(&Key_PB);
		Key_Scan(&Key_PC);
		
		Signal_Scan();
		
		/* ��UI�������� */
		Key_Control();
		
		vTaskDelay( 10 );
	}
	
}

void Signal_Scan(void)
{
	
	/* uart1 */
	if((xTaskGetTickCount() - 300) > uart3Connect.tickCount)
	{
		uart3Connect.status = enBreak;
	}
	else
	{
		uart3Connect.status = enSig3;
	}
	if(uart3Connect.tickCount > xTaskGetTickCount())
	{
		uart3Connect.tickCount = xTaskGetTickCount();
	}
	
}



/* ����-���� (��ҳ����ư���)*/
void  Key_Control(void)
{
	//A��������
	if(Key_PA.Key_RetVal == enKey_Click)
	{

		/* �����л�ģʽ���� */
		sendRmotorCmd(enIDRemote,CMD_CHANGE_MODE,0,0);
		
		Key_PA.Key_RetVal = enKey_No;   //��־��λ
	}
	//A����������
	if(Key_PA.Key_RetVal == enKey_LongPress)
	{
		;
	}	
	
	//B��������
	if(Key_PB.Key_RetVal == enKey_Click)
	{
		
		/* �л���ʾģʽ */
		Change_UIMode();
		
		Key_PB.Key_RetVal = enKey_No;   //��־��λ
	}
	//B����������
	if(Key_PB.Key_RetVal == enKey_LongPress)
	{
		;
	}
	//B��������
	if(Key_PB.Key_RetVal == enKey_No && Key_PB.Flag_LongPress == true)
	{
		/* ͬ������ */
		if(Show_ui == CAR_ui)
		{
				if(carUIPara.Sync == true) carUIPara.Sync = false;
				else                       
				{
					carUIPara.Sync = true;
					/* ����һ���¼� */
					xEventGroupSetBits(Event_uart3SendData,EVENT_uart3CARUIREQ);	
				}
		}
		
		
		Key_PB.Flag_LongPress = false; //��־��λ
	}	
	
}








