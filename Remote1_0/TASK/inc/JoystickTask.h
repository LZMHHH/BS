/**
  ******************************************************************************
  * @file    JoystickTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
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
#ifndef __JOYSTICK_H
#define __JOYSTICK_H	 
#include "includes.h"


/* 别名 */
typedef  struct  class_joystick    CLASS_Joystick; 
/* 摇杆类参数 */
struct class_joystick 
{
	
	u16    PriY;     //原始的摇杆AD值 Y
	u16    PriX;     //原始的摇杆AD值 X
	
	int    NorY;     //正常的摇杆AD值 Y
	int    NorX;     //正常的摇杆AD值 X
	
	u16    YZeroSet; //调零值（2048） Y
	u16    XZeroSet; //调零值（2048） X
	
	u8     Mode;     //当前模式
	
};


void vTaskJoystick( void * pvParameters );


#endif







