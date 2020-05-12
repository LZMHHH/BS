/**
  ******************************************************************************
  * @file    bsp_hwbz.h
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __HWBZ_H
#define __HWBZ_H	 
#include "includes.h"


#define HWBZ_TURE  0
#define HWBZ_FALSE 1			

//别名
typedef  struct  class_hwbz         CLASS_Hwbz;



/* 设备机表 */
typedef enum
{
	enHwbz_NO,          
	enHwbz_LD,       
	enHwbz_LU,
	enHwbz_RU,
	enHwbz_RD,		
}HWBZx_Status;		


//引脚配置
typedef struct class_hwbz_config
{
	uint32_t      gpio_clk;
	GPIO_TypeDef* gpio_port;
	uint32_t      gpio_pin;
}CLASS_Hwbz_config;

//按键类
struct class_hwbz 
{
	u8      name;       //按键名字，枚举
	u8      status;     //状态
	
	CLASS_Hwbz_config   config;         //引脚配置
};


//创建按键
extern CLASS_Hwbz   Hwbz_LD;  
extern CLASS_Hwbz   Hwbz_LU;  
extern CLASS_Hwbz   Hwbz_RU; 
extern CLASS_Hwbz   Hwbz_RD;

#define Hwbz_Pre(a)	       GPIO_ReadInputDataBit(a.config.gpio_port,a.config.gpio_pin) 

void   bsp_Hwbz_Init      (void);          //初始化

#endif 
