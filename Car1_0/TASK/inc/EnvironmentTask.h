/**
  ******************************************************************************
  * @file    EnvironmentTask.h
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
#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H	 
#include "includes.h"



void vTaskEnvironment( void * pvParameters );

void sendSht3xData(TickType_t xTicksToWait);
void sendGy30Data(TickType_t xTicksToWait);
void sendPmsData(TickType_t xTicksToWait);
void sendBmeData(TickType_t xTicksToWait);

#endif







