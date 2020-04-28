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
		
		/* ��UI�������� */
		Key_Control();
		
		vTaskDelay( 10 );
	}
	
}


/* ����-���� (��ҳ����ư���)*/
void  Key_Control(void)
{
	//A��������
	if(Key_PA.Key_RetVal == enKey_Click)
	{

		/* �����л�ģʽ���� */
		sendRmotorCmd(enIDCAR,CMD_CHANGE_MODE,0,0);
		
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
		switch(Show_ui)
		{
			case MAIN_ui:
						Show_ui = CAR_ui;
						OLED_Fill(0,0,128,64,0);
						break;
			case CAR_ui:
						Show_ui = MAIN_ui;
			      OLED_Fill(0,0,128,64,0);
						break;
			default:break;
		}
		
		Key_PB.Key_RetVal = enKey_No;   //��־��λ
	}
	//B����������
	if(Key_PB.Key_RetVal == enKey_LongPress)
	{
		;
	}	
	
}








