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
#define EVENT_canOLEDCLEAR (0x01 << 1)
#define EVENT_canLED      (0x01 << 2)
#define EVENT_canCARPAGE0 (0x01 << 3)
#define EVENT_canCARPAGE1 (0x01 << 4)
#define EVENT_canCARPAGE2 (0x01 << 5)
#define EVENT_canCARPAGE3 (0x01 << 6)
#define EVENT_canCARUI    (0x01 << 7)
#define EVENT_canENVUIREQ (0x01 << 8)
#define EVENT_canMOTOR    (0x01 << 18)
#define EVENT_canENCODER  (0x01 << 19)
#endif







