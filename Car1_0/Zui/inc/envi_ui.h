/**
  ******************************************************************************
  * @file    envi_ui.c
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
	
#ifndef _ENVI_UI_H
#define _ENVI_UI_H
#include "includes.h" 

/* 广播 */
extern struct  class_uiconfigParam Envi_uiconfigParam;



void Envi_ZUI(void);
void Envi_uiconfigParamInit(void);
void Envi_uictrl(void);

#endif
