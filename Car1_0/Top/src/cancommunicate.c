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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
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


/*********************** �ⷢ ***********************/



/*********************** ���� ***********************/




void canCommunicateParaInit(void)
{
	canConnect.tickCount = xTaskGetTickCount();
	canConnect.status    = enBreak;
	
}







