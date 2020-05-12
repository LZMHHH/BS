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

void uart1SendSht3xData(TickType_t xTicksToWait);
void uart1SendGy30Data(TickType_t xTicksToWait);
void uart1SendPmsData(TickType_t xTicksToWait);
void uart1SendBmeData(TickType_t xTicksToWait);
void uart1SendClockData(TickType_t xTicksToWait);
void uart1SendSetClockData(TickType_t xTicksToWait);
void uart1SendSmogData(TickType_t xTicksToWait);
void uart1SendHydrogenData(TickType_t xTicksToWait);
void uart1SendCOData(TickType_t xTicksToWait);
void uart1SendHuimitureData(TickType_t xTicksToWait);
#endif







