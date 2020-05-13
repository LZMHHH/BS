/**
  ******************************************************************************
  * @file    canCommunicateTask.h
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
#ifndef _CAN_COMMUNICATETASK_H
#define _CAN_COMMUNICATETASK_H	 

#include "includes.h"

void vTaskCanRx( void * pvParameters );
void vTaskCanTx( void * pvParameters );
void vTaskcanSendData( void * pvParameters );

/* 事件组宏定义 */
#define EVENT_canSHT3X    (0x01 << 1)//设置事件掩码的位1:上传pwm事件
#define EVENT_canGY30     (0x01 << 2)
#define EVENT_canPMS      (0x01 << 3)
#define EVENT_canBME      (0x01 << 4)
#define EVENT_canLED      (0x01 << 11)
#define EVENT_canOLEDCLEAR (0x01 << 8)
#define EVENT_canCARUI    (0x01 << 16)
#define EVENT_canENVUI    (0x01 << 17)
#define EVENT_canCARUIREQ (0x01 << 18)

//上传数据任务
void vTaskcanSendData( void * pvParameters );

#endif







