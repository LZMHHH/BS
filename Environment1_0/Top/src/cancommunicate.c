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
ui_t        carUIPara;



/*********************** �ⷢ ***********************/


/*********************** ���� ***********************/




void canCommunicateParaInit(void)
{
	canConnect.tickCount = xTaskGetTickCount();
	canConnect.status    = enBreak;
	
}







