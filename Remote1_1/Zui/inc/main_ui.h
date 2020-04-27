/**
  ******************************************************************************
  * @file    main_ui.c
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
#ifndef __MAIN_UI_H
#define __MAIN_UI_H
#include "includes.h" 


/* 广播 */
extern struct  class_uiconfigParam Main_uiconfigParam;

void Main_ZUI(void);
void Main_uiconfigParamInit(void);
void Main_uictrl(void);

#endif
