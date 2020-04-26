/**
  ******************************************************************************
  * @file    MoveCtrlTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   移动控制任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __MOVECTRLTASK_H
#define __MOVECTRLTASK_H	 
#include "includes.h"

/* 广播 */
typedef struct class_motor CLASS_Motor;

extern   CLASS_Motor MotorA;
extern   CLASS_Motor MotorB;
extern   CLASS_Motor MotorC;
extern   CLASS_Motor MotorD;

void vTaskMoveCtrl( void * pvParameters );


#endif







