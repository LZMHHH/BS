/**
  ******************************************************************************
  * @file    CommunicateTask.h
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
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
#ifndef __COMMUNICATETASK_H
#define __COMMUNICATETASK_H	 

#include "includes.h"

/* 事件组宏定义 */
#define EVENT_MOTOR    (0x01 << 1)//设置事件掩码的位1:上传pwm事件
#define EVENT_ENCODER  (0x01 << 2)//设置事件掩码的位2:上传编码器事件
#define EVENT_LED      (0x01 << 3)//设置事件掩码的位3:上传led事件
#define EVENT_KEYACK   (0x01 << 4)//设置事件掩码的位4:返回EVENT_KEYACK事件
#define EVENT_uart1CARUI   (0x01 << 5)
#define EVENT_uart1ENVUI   (0x01 << 6)
#define EVENT_uart1SHT3X   (0x01 << 7)//设置事件掩码的位1:上传pwm事件
#define EVENT_uart1GY30    (0x01 << 8)
#define EVENT_uart1PMS     (0x01 << 9)
#define EVENT_uart1BME     (0x01 << 10)
#define EVENT_uart1CARPAGE0 (0x01 << 11)
#define EVENT_uart1CARPAGE1 (0x01 << 12)
#define EVENT_uart1CARPAGE2 (0x01 << 13)
#define EVENT_uart1CARPAGE3 (0x01 << 14)
#define EVENT_uart1ENVPAGE0 (0x01 << 15)
#define EVENT_uart1ENVPAGE1 (0x01 << 16)
#define EVENT_uart1ENVPAGE2 (0x01 << 17)
#define EVENT_uart1ENVPAGE3 (0x01 << 18)
#define EVENT_uart1ENVPAGE4 (0x01 << 19)
#define EVENT_uart1ENVPAGE5 (0x01 << 20)

//Uart1的任务
void vTaskUart1Rx( void * pvParameters );
void vTaskUart1Tx( void * pvParameters );

//串口的上层任务
void vTaskSendData( void * pvParameters );

#endif







