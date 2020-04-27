/**
  ******************************************************************************
  * @file    CommunicateCTask.h
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
#ifndef __COMMUNICATE_C_TASK_H
#define __COMMUNICATE_C_TASK_H	 

#include "includes.h"

//Uart1的接收任务
void vTaskUart3Rx( void * pvParameters );
void vTaskUart3Tx( void * pvParameters );

#endif







