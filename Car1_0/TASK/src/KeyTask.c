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


//按键-处理-----------------------------------------------------------------------------
void  Key_Control(void)
{
	//上键被单击
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

/* 通讯 */
void canSendKeyClickData(u8 key,TickType_t xTicksToWait)
{
	u16 u16data;
	
	CanTxMsg p;
	
	p.StdId = CAN_KEYID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
  p.Data[1] = enDATA;
	p.Data[2] = key;
	p.Data[3] = CAN_KeyRet;
	p.Data[4] = enKey_Click; /* 单击 */
	xQueueSend(xQueue_canTx, &p, xTicksToWait);

}



