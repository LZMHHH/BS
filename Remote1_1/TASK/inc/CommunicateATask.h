/**
  ******************************************************************************
  * @file    CommunicateATask.h
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
#ifndef __COMMUNICATE_A_TASK_H
#define __COMMUNICATE_A_TASK_H	 

#include "includes.h"

//Uart1的接收任务
void vTaskUart1Rx( void * pvParameters );
void vTaskUart1Tx( void * pvParameters );

#endif







