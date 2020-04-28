/**
  ******************************************************************************
  * @file    car_ui.h
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
	
#ifndef __CAR_UI_H
#define __CAR_UI_H
#include "includes.h" 


/* 广播 */
extern struct  class_uiconfigParam Car_uiconfigParam;

void Car_ZUI(void);
void Car_uiconfigParamInit(void);
void Car_uictrl(void);



#endif
