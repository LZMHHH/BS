/**
  ******************************************************************************
  * @file    PmsTask.h
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
#ifndef __PMSTASK_H
#define __PMSTASK_H	 
#include "includes.h"


//防止报错
typedef struct class_pms CLASS_Pms;

/* 广播 */
extern CLASS_Pms Pms; 

void vTaskPms( void * pvParameters );


#endif







