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


/* ���� */
typedef  struct  class_joystick    CLASS_Joystick; 
/* ҡ������� */
struct class_joystick 
{
	
	u16    PriY;     //ԭʼ��ҡ��ADֵ Y
	u16    PriX;     //ԭʼ��ҡ��ADֵ X
	
	int    NorY;     //������ҡ��ADֵ Y
	int    NorX;     //������ҡ��ADֵ X
	
	u16    YZeroSet; //����ֵ��2048�� Y
	u16    XZeroSet; //����ֵ��2048�� X
	
	u8     Mode;     //��ǰģʽ
	
};


void vTaskJoystick( void * pvParameters );


#endif







