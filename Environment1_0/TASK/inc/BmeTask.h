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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BMETASK_H
#define _BMETASK_H	 
#include "includes.h"


//��ֹ����
typedef struct class_bmp       CLASS_Bmp;


/* �㲥 */
extern struct class_bme       Bme;


void vTaskBme( void * pvParameters );


#endif







