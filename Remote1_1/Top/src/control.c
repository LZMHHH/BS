/**
  ******************************************************************************
  * @file    control.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "control.h"	
#include "bsp_mcuFlash.h"
/* 小车控制模式 */
ConMode_e        ConCarMode;
/* 小车移动值 */
CLASS_CarMoveVal CarMoveVal;

/* 数学公式 */
//转移范围
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 /****************************************************************************
  * @brief    绝对值函数
  * @param    a
  * @retval   |a|
  * @author   LZM
  * @note      
  */
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


void ConParaInit(void)
{
	/* 小车控制模式 */
	ConCarMode = enJoystick;
}


/*数据初始化*/
void ParaInit(void)
{
	ConParaInit();
	
	CommunicateParaInit();

}




//载入数据
//保存 往前天数的数据    
void SaveFlashJoyData(void)
{

	taskENTER_CRITICAL();
	
	//记录前必须先擦除
	FlashErase(INSector,1);
	

	Flash_Write(INSector,(const uint8 *)&Joystick_Left.Mode,2,0);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.Grade,2,2);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.XZeroSet,4,4);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.YZeroSet,4,8);
  Flash_Write(INSector,(const uint8 *)&Joystick_Left.XShieldVal,4,12);
  Flash_Write(INSector,(const uint8 *)&Joystick_Left.YShieldVal,4,16);
	
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.Mode,2,20);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.Grade,2,22);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.XZeroSet,4,24);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.YZeroSet,4,28);
  Flash_Write(INSector,(const uint8 *)&Joystick_Right.XShieldVal,4,32);
  Flash_Write(INSector,(const uint8 *)&Joystick_Right.YShieldVal,4,36);
	
	taskEXIT_CRITICAL();
}

void ReadFlashJoyData(void)
{

	taskENTER_CRITICAL();
	
	Joystick_Left.Mode = Flash_Read(INSector,0,u8);
	Joystick_Left.Grade = Flash_Read(INSector,2,u8);
	Joystick_Left.XZeroSet = Flash_Read(INSector,4,int);
	Joystick_Left.YZeroSet = Flash_Read(INSector,8,int);
  Joystick_Left.XShieldVal = Flash_Read(INSector,12,int);
  Joystick_Left.YShieldVal = Flash_Read(INSector,16,int);

	Joystick_Right.Mode = Flash_Read(INSector,20,u8);
	Joystick_Right.Grade = Flash_Read(INSector,22,u8);
	Joystick_Right.XZeroSet = Flash_Read(INSector,24,int);
	Joystick_Right.YZeroSet = Flash_Read(INSector,28,int);
  Joystick_Right.XShieldVal = Flash_Read(INSector,32,int);
  Joystick_Right.YShieldVal = Flash_Read(INSector,36,int);
	
	taskEXIT_CRITICAL();
}


