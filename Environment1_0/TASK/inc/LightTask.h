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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __LIGHTTASK_H
#define __LIGHTTASK_H	 
#include "includes.h"


//��ֹ����
typedef struct class_light CLASS_Light;

/* �㲥 */
extern CLASS_Light Light; 

void vTaskLight( void * pvParameters );


#endif







