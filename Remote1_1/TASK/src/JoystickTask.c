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
static void Para_Init(void);
static void UpJoystickData(void);

/* 通讯部分 */



void vTaskJoystick( void * pvParameters )
{
	
	Para_Init();
	
	while(1)
	{
		
		/* 更新数据 */
		UpJoystickData();
		
		
		if(ConCarMode == enJoystick)
		{
			CarMoveVal.MoveX = Joystick_Left.NorX;
			CarMoveVal.MoveY = Joystick_Left.NorY;
			CarMoveVal.MoveZ = Joystick_Right.NorX;
			
			if( myabs(CarMoveVal.MoveX) < Joystick_Left.XShieldVal )
			{
				CarMoveVal.MoveX = 0;
			}
			else
			{
				CarMoveVal.MoveX = map(CarMoveVal.MoveX,-2048,2048,-1000,1000);
			}
			if( myabs(CarMoveVal.MoveY) < Joystick_Left.YShieldVal )
			{
				CarMoveVal.MoveY = 0;
			}
			else
			{
				CarMoveVal.MoveY = map(CarMoveVal.MoveY,-2048,2048,-1000,1000);
			}
			if( myabs(CarMoveVal.MoveZ) < Joystick_Right.XShieldVal )
			{
				CarMoveVal.MoveZ = 0;
			}
			else
			{
				CarMoveVal.MoveZ = map(CarMoveVal.MoveZ,-2048,2048,-1000,1000);
			}
			if((CarMoveVal.MoveX != 0) || (CarMoveVal.MoveY != 0) || (CarMoveVal.MoveZ != 0))
					sendRmotorData(enIDRemote, KIND_MOVE, (u8*)&CarMoveVal, sizeof(CarMoveVal), 20);
		}
		
		
		vTaskDelay( 20 );
	}
	
}

static void Para_Init(void)
{
//	Joystick_Left.YZeroSet  = 2048;
//	Joystick_Left.XZeroSet  = 2048;
//	Joystick_Right.YZeroSet = 2048;
//	Joystick_Right.XZeroSet = 2048;
//	
//	Joystick_Left.XShieldVal  = 150;
//	Joystick_Left.YShieldVal  = 150;
//	Joystick_Right.XShieldVal = 150;
//	Joystick_Right.YShieldVal = 150;
	
	ReadFlashJoyData();
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







