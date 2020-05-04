/**
  ******************************************************************************
  * @file    cancommunicate.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "cancommunicate.h"

connect_t   canConnect;
ui_t        envUIPara;
ui_t        carUIPara;

huimiture_t Huimiture;
light_t     Light;
pms_t       Pms;
bme_t       Bme;
clock_t     ClockA;
clock_t     SetClock;


/*********************** 外发 ***********************/



/*********************** 接收 ***********************/




void canCommunicateParaInit(void)
{
	canConnect.tickCount = xTaskGetTickCount();
	canConnect.status    = enBreak;
	
}







