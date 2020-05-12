/**
  ******************************************************************************
  * @file    DistanceTask.h
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
#ifndef __DISTANCETASK_H
#define __DISTANCETASK_H	 
#include "includes.h"

void vTaskDistance( void * pvParameters );

typedef struct class_distance CLASS_Distance;

extern CLASS_Distance Distance;

void canSendVl53l0xData(void);
void uart1SendVl53l0xData(void);

#endif







