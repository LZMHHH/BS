/**
  ******************************************************************************
  * @file    MoveCtrlTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   �ƶ���������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __MOVECTRLTASK_H
#define __MOVECTRLTASK_H	 
#include "includes.h"

/* �㲥 */
typedef struct class_motor CLASS_Motor;

extern   CLASS_Motor MotorA;
extern   CLASS_Motor MotorB;
extern   CLASS_Motor MotorC;
extern   CLASS_Motor MotorD;

void vTaskMoveCtrl( void * pvParameters );


#endif







