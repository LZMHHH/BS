/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include <stdarg.h>
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*
*********************************************************************************************************
*                                                 ST
*********************************************************************************************************
*/

#include  "stm32f10x.h"

// �û�������ͷ�ļ�
#include "control.h"
#include "bsp.h"
#include "bsp_dwt_delay.h"
#include "delay.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart1.h"
#include "bsp_oled.h"
#include "bsp_adc.h"
#include "bsp_i2c.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "mpu6050.h"


#include "bmp.h"
#include "main_ui.h"
#include "car_ui.h"
#include "envi_ui.h"


//����ͷ�ļ�
#include "LedTask.h"
#include "KeyTask.h"
#include "DisplayTask.h"
#include "JoystickTask.h"
#include "MpuTask.h"
#include "CommunicateATask.h"

/* ===== �㲥 ===== */

/* ��Ϣ���еľ�� */		
/* �����ݶ��о�� */
extern TaskHandle_t xQueue_uart1Rx;  //uart1�Ľ�����Ϣ����
extern TaskHandle_t xQueue_uart1Tx;  //uart1�ķ�����Ϣ����

//��ֵͨ���о��
extern TaskHandle_t vQueue_JoystickLeft; //��ҡ��Data���
extern TaskHandle_t vQueue_JoystickRight; //��ҡ��Data���

/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif


