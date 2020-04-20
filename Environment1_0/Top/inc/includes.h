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

/* 是否打印任务信息 */
#define IFPRINTTASK  false
/* 是否适用文件系统 */
#define IFFILESYSTEM  false
	




/*
*********************************************************************************************************
*                                              p
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


// 用户开发的头文件
/* soft */
#include "control.h"
#include "gather.h"	

/* bsp */
#include "bsp.h"
#include "bsp_dwt_delay.h"
#include "delay.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_oled.h"
#include "config_param.h"
#include "bsp_sht3x.h"
#include "bsp_DS3231.h"  
#include "bsp_gy30.h"
#include "bsp_bme280.h"

#include "bmp.h"
#include "main_ui.h"



#if IFPRINTTASK
#include "bsp_tim_pwm.h"
#endif
#if IFFILESYSTEM
#include "sdio_sdcard.h"	
#include "integer.h"
#include "ff.h"
#include "ffconf.h"
#include "diskio.h"
#include "file_sys.h"
#endif




//任务实体
#include "LedTask.h"
#include "KeyTask.h"
#include "CommunicateTask.h"
#include "DisplayTask.h"
#include "EnvironmentTask.h"
#include "ClockTask.h"
#include "LightTask.h"
#include "PmsTask.h"
#if IFPRINTTASK
#include "CpuTask.h"
#endif
#if IFFILESYSTEM
#include "FileTask.h"
#include "CheckTask.h"
#include "InitTask.h"
#endif


/*  
*******************************************************************************************************
		通用状态机
*******************************************************************************************************
*/
/* 设备状态机表 */
typedef enum
{
	U_IDLE,   //空闲在状态
	U_ING,    //进行中
	U_ED,     //完成状态
}U_Status;


/* 通用bit位表 */
#define BIT_0	(1 << 0)
#define BIT_1	(1 << 1)

/* ===== 广播 ===== */
//调试专用
/* 在主函数中调用 */
extern void vSetupSysInfoTest(void);

//消息广播
extern TaskHandle_t xQueue_uart1Rx;  //uart1的接收消息队列
extern TaskHandle_t xQueue_uart1Tx;  //uart1的发送消息队列
extern TaskHandle_t xQueue_uart2Rx;  //uart2的接收消息队列


//事件标志组涉及的函数句柄广播
extern TaskHandle_t xHandleTaskInit;  //file任务
#if IFFILESYSTEM
//文件系統
extern FATFS fs_sd;  //sd卡
#endif
/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif


