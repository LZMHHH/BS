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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __PMSTASK_H
#define __PMSTASK_H	 
#include "includes.h"


//��ֹ����
typedef struct class_pms CLASS_Pms;

/* �㲥 */
extern CLASS_Pms Pms; 

void vTaskPms( void * pvParameters );


#endif







