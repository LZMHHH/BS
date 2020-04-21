/**
  ******************************************************************************
  * @file    BmeTask.h
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
#ifndef _BMETASK_H
#define _BMETASK_H	 
#include "includes.h"


//防止报错
typedef struct class_bmp       CLASS_Bmp;


/* 广播 */
extern struct class_bme       Bme;


void vTaskBme( void * pvParameters );


#endif







