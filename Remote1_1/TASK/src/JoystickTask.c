/**
  ******************************************************************************
  * @file    JoystickTask.c
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
#include "JoystickTask.h"


CLASS_Joystick Joystick_Left;
CLASS_Joystick Joystick_Right;


/* 函数声明 */
static void JoystickData_Init(void);
static void UpJoystickData(void);
static void Ipc_RxJoystickData(void);
static void Ipc_TxJoystickData(void);




void vTaskJoystick( void * pvParameters )
{
	
	JoystickData_Init();
	
	while(1)
	{
		/* 更新数据 */
		Ipc_RxJoystickData();
		UpJoystickData();
		
		/* 发送数据 */
		Ipc_TxJoystickData();

		vTaskDelay( 20 );
	}
	
}

static void JoystickData_Init(void)
{
	Joystick_Left.YZeroSet  = 2048;
	Joystick_Left.XZeroSet  = 2048;
	Joystick_Right.YZeroSet = 2048;
	Joystick_Right.XZeroSet = 2048;
}

static void UpJoystickData(void)
{
	Joystick_Left.PriY  = getAdcValue(ADC_LLINE);
	Joystick_Left.PriX  = getAdcValue(ADC_LROW);
	Joystick_Right.PriY = getAdcValue(ADC_RLINE);
	Joystick_Right.PriX = getAdcValue(ADC_RROW);
	
	Joystick_Left.NorY  = Joystick_Left.PriY  - Joystick_Left.YZeroSet;
	Joystick_Left.NorX  = Joystick_Left.PriX  - Joystick_Left.XZeroSet;
	Joystick_Right.NorY = Joystick_Right.PriY - Joystick_Right.YZeroSet;
	Joystick_Right.NorX = Joystick_Right.PriX - Joystick_Right.XZeroSet;
	
}

static void copyJoystickData(CLASS_Joystick dest,CLASS_Joystick src)
{
	dest.PriY = src.PriY;
	dest.PriX = src.PriX;
	
	dest.NorY = src.NorY;
	dest.NorX = src.NorX;
	
	dest.YZeroSet = src.YZeroSet;
	dest.XZeroSet = src.XZeroSet;
	
	dest.Mode = src.Mode;
}

static void Ipc_RxJoystickData(void)
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	CLASS_Joystick       Joystick_x;
	
	/*先读空，再发送*/
	xReturn = xQueueReceive( vQueue_JoystickLeft,        /* 消息队列的句柄 */
                             (void *)&Joystick_x,      /* 发送的消息内容 */
                             0);                       /* 不等待 */
														 
	copyJoystickData(Joystick_Left,Joystick_x);
														 
	/*先读空，再发送*/
	xReturn = xQueueReceive( vQueue_JoystickRight,       /* 消息队列的句柄 */
                             (void *)&Joystick_x,      /* 发送的消息内容 */
                             0);                       /* 不等待 */
														 
	copyJoystickData(Joystick_Right,Joystick_x);

}

static void Ipc_TxJoystickData(void)
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */

	xQueueSend( vQueue_JoystickLeft,      /* 消息队列的句柄 */
								 (void *)&Joystick_Left,   /* 发送的消息内容 */
								 0);                       /* 不等待 */
														 
	xQueueSend( vQueue_JoystickRight,     /* 消息队列的句柄 */
							 (void *)&Joystick_Right,     /* 发送的消息内容 */
							 0);                         /* 不等待 */
}




