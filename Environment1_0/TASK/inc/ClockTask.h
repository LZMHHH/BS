/**
  ******************************************************************************
  * @file    ClockTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ʱ������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _CLOCK_H
#define _CLOCK_H	 
#include "includes.h"

//��ֹ����
typedef struct class_clock CLASS_Clock;

/* �㲥 */
extern CLASS_Clock ClockA; 


void vTaskClock( void * pvParameters );


#endif







