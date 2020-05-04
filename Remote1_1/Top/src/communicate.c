/**
  ******************************************************************************
  * @file    communicate.c
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
#include "communicate.h"

/* ���� */
static void LedCommunicateParaInit(void);

connect_t   uart3Connect;

/*********************** �ⷢ ***********************/
led_t carLEDA;
led_t carFMQ;
led_t envLEDA;
led_t envLEDB;
led_t envFMQ;

ui_t   carUIPara;
ui_t   envUIPara;

/*********************** ���� ***********************/
encoder_t Encoder;
motor_t   Motorpwm;
huimiture_t Huimiture;
light_t     Light;
pms_t       Pms;
bme_t       Bme;
clock_t     ClockA;
clock_t     SetClock;

void CommunicateParaInit(void)
{
	LedCommunicateParaInit();
	
}


static void LedCommunicateParaInit(void)
{
	carLEDA.name = NAME_LEDA;
	carLEDA.mode = enFre;
	carLEDA.cycle  = 100;
	
	carFMQ.name = NAME_FMQ;
	carFMQ.mode = enFre;
	carFMQ.cycle  = 100;
	
	envLEDA.name = NAME_LEDA;
	envLEDA.mode = enFre;
	envLEDA.cycle  = 100;
	
	envLEDB.name = NAME_LEDB;
	envLEDB.mode = enFre;
	envLEDB.cycle  = 100;
	
	envFMQ.name = NAME_FMQ;
	envFMQ.mode = enFre;
	envFMQ.cycle  = 100;
	
	carUIPara.Step_Index          = 1;
	carUIPara.Page_Index          = 1;
	carUIPara.Page_Index_Last     = 0;
	carUIPara.Para_Index          = 0;
	carUIPara.Para_IfControl      = false;
	carUIPara.Sync                = 0;
}





