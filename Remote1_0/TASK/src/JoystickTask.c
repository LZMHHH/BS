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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "JoystickTask.h"


CLASS_Joystick Joystick_Left;
CLASS_Joystick Joystick_Right;


/* �������� */
static void JoystickData_Init(void);
static void UpJoystickData(void);
static void Ipc_RxJoystickData(void);
static void Ipc_TxJoystickData(void);




void vTaskJoystick( void * pvParameters )
{
	
	JoystickData_Init();
	
	while(1)
	{
		/* �������� */
		Ipc_RxJoystickData();
		UpJoystickData();
		
		/* �������� */
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
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	CLASS_Joystick       Joystick_x;
	
	/*�ȶ��գ��ٷ���*/
	xReturn = xQueueReceive( vQueue_JoystickLeft,        /* ��Ϣ���еľ�� */
                             (void *)&Joystick_x,      /* ���͵���Ϣ���� */
                             0);                       /* ���ȴ� */
														 
	copyJoystickData(Joystick_Left,Joystick_x);
														 
	/*�ȶ��գ��ٷ���*/
	xReturn = xQueueReceive( vQueue_JoystickRight,       /* ��Ϣ���еľ�� */
                             (void *)&Joystick_x,      /* ���͵���Ϣ���� */
                             0);                       /* ���ȴ� */
														 
	copyJoystickData(Joystick_Right,Joystick_x);

}

static void Ipc_TxJoystickData(void)
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */

	xQueueSend( vQueue_JoystickLeft,      /* ��Ϣ���еľ�� */
								 (void *)&Joystick_Left,   /* ���͵���Ϣ���� */
								 0);                       /* ���ȴ� */
														 
	xQueueSend( vQueue_JoystickRight,     /* ��Ϣ���еľ�� */
							 (void *)&Joystick_Right,     /* ���͵���Ϣ���� */
							 0);                         /* ���ȴ� */
}




