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
static void Para_Init(void);
static void UpJoystickData(void);

/* ͨѶ���� */



void vTaskJoystick( void * pvParameters )
{
	
	Para_Init();
	
	while(1)
	{
		
		/* �������� */
		UpJoystickData();
		
		
		if(ConCarMode == enJoystick)
		{
			CarMoveVal.MoveX = Joystick_Left.NorX;
			CarMoveVal.MoveY = Joystick_Left.NorY;
			CarMoveVal.MoveZ = Joystick_Right.NorX;
			

			sendRmotorData(enIDCAR, KIND_MOVE, (u8*)&CarMoveVal, sizeof(CarMoveVal), 20);
		}
		
		
		vTaskDelay( 2000 );
	}
	
}

static void Para_Init(void)
{
	Joystick_Left.YZeroSet  = 2048;
	Joystick_Left.XZeroSet  = 2048;
	Joystick_Right.YZeroSet = 2048;
	Joystick_Right.XZeroSet = 2048;
	
	Joystick_Left.XShieldVal  = 100;
	Joystick_Left.YShieldVal  = 100;
	Joystick_Right.XShieldVal = 100;
	Joystick_Right.YShieldVal = 100;
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







