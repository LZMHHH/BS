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
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "communicate.h"

connect_t   uart1Connect;


/*********************** 外发 ***********************/
encoder_t Encoder;
motor_t   Motorpwm;

/*********************** 接收 ***********************/
led_t carLEDA;
led_t carFMQ;
led_t envLEDA;
led_t envLEDB;
led_t envFMQ;


/* 声明 */
static void LedCommunicateParaInit(void);

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
}





