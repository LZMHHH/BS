/**
  ******************************************************************************
  * @file    ClockTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   时钟任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _CLOCK_H
#define _CLOCK_H	 
#include "includes.h"

//防止报错
typedef struct class_clock CLASS_Clock;

/* 广播 */
extern CLASS_Clock ClockA; 


void vTaskClock( void * pvParameters );


#endif







