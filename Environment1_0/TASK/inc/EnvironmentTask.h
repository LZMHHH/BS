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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H	 
#include "includes.h"


//��ֹ����
typedef struct class_huimiture CLASS_Huimiture;
typedef struct class_bmp       CLASS_Bmp;


/* �㲥 */
extern CLASS_Huimiture Huimiture;
extern struct class_bme       Bme;


void vTaskEnvironment( void * pvParameters );


#endif







