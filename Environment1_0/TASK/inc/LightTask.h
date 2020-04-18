/**
  ******************************************************************************
  * @file    LightTask.h
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
#ifndef __LIGHTTASK_H
#define __LIGHTTASK_H	 
#include "includes.h"


//防止报错
typedef struct class_light CLASS_Light;

/* 广播 */
extern CLASS_Light Light; 

void vTaskLight( void * pvParameters );


#endif







