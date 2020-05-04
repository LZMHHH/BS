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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "KeyTask.h"

//声明
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
		
		/* 非UI按键控制 */
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



/* 按键-处理 (非页面控制按键)*/
void  Key_Control(void)
{
	//A键被单击
	if(Key_PA.Key_RetVal == enKey_Click)
	{

		/* 发送切换模式命令 */
		sendRmotorCmd(enIDRemote,CMD_CHANGE_MODE,0,0);
		
		Key_PA.Key_RetVal = enKey_No;   //标志复位
	}
	//A键被长按中
	if(Key_PA.Key_RetVal == enKey_LongPress)
	{
		;
	}	
	
	//B键被单击
	if(Key_PB.Key_RetVal == enKey_Click)
	{
		
		/* 切换显示模式 */
		Change_UIMode();
		
		Key_PB.Key_RetVal = enKey_No;   //标志复位
	}
	//B键被长按中
	if(Key_PB.Key_RetVal == enKey_LongPress)
	{
		;
	}
	//B键被长按
	if(Key_PB.Key_RetVal == enKey_No && Key_PB.Flag_LongPress == true)
	{
		/* 同步参数 */
		if(Show_ui == CAR_ui)
		{
				if(carUIPara.Sync == true) carUIPara.Sync = false;
				else                       
				{
					carUIPara.Sync = true;
					/* 触发一个事件 */
					xEventGroupSetBits(Event_uart3SendData,EVENT_uart3CARUIREQ);	
				}
		}
		
		
		Key_PB.Flag_LongPress = false; //标志复位
	}	
	
}








