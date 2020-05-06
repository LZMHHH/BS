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


//防止报错
typedef struct   class_huimiture CLASS_Huimiture;
typedef  struct  class_gas       CLASS_Gas; 

/* 广播 */
extern CLASS_Huimiture Huimiture;
extern CLASS_Gas       Smog;
extern CLASS_Gas       Hydrogen;
extern CLASS_Gas       CO;

void vTaskEnvironment( void * pvParameters );


#endif







