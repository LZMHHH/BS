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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __JOYSTICK_H
#define __JOYSTICK_H	 
#include "includes.h"










/* ��ֹ���� */
typedef  struct  class_joystick    CLASS_Joystick; 

/* �㲥 */
extern CLASS_Joystick Joystick_Left; 
extern CLASS_Joystick Joystick_Right;

void vTaskJoystick( void * pvParameters );


#endif







