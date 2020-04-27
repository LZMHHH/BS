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










/* 防止报错 */
typedef  struct  class_joystick    CLASS_Joystick; 

/* 广播 */
extern CLASS_Joystick Joystick_Left; 
extern CLASS_Joystick Joystick_Right;

void vTaskJoystick( void * pvParameters );


#endif







