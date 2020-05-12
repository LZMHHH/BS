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
ui_t        carUIPara;

led_t     carLEDA;
led_t     carFMQ;
encoder_t Encoder;
motor_t   Motorpwm;
car_t     Car;
hwbz_t    Hwbz_LD;
hwbz_t    Hwbz_LU;
hwbz_t    Hwbz_RU;
hwbz_t    Hwbz_RD;
distance_t Distance;
pid_t     MotorAllPID;


void canCommunicateParaInit(void)
{
	canConnect.tickCount = xTaskGetTickCount();
	canConnect.status    = enBreak;
	
}







