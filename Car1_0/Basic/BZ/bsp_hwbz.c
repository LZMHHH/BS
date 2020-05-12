/**
  ******************************************************************************
  * @file    bsp_hwbz.h
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
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
#include "bsp_hwbz.h"

//创建按键 + 配置
CLASS_Hwbz   Hwbz_LD={.name             = enHwbz_LD,
										.config.gpio_clk  = RCC_APB2Periph_GPIOB,
										.config.gpio_port = GPIOB,
										.config.gpio_pin  = GPIO_Pin_5
										};    
CLASS_Hwbz   Hwbz_LU={.name             = enHwbz_LU,
										.config.gpio_clk  = RCC_APB2Periph_GPIOB,
										.config.gpio_port = GPIOB,
										.config.gpio_pin  = GPIO_Pin_4
										};    
CLASS_Hwbz   Hwbz_RU={.name             = enHwbz_RU,
										.config.gpio_clk  = RCC_APB2Periph_GPIOC,
										.config.gpio_port = GPIOC,
										.config.gpio_pin  = GPIO_Pin_3
										};     
CLASS_Hwbz   Hwbz_RD={.name             = enHwbz_RD,
										.config.gpio_clk  = RCC_APB2Periph_GPIOC,
										.config.gpio_port = GPIOC,
										.config.gpio_pin  = GPIO_Pin_2
										};     



/**************************************************************************
函数功能：单个按键引脚初始化
入口参数：无
返回  值：无 
**************************************************************************/
static void Hwbz_config(CLASS_Hwbz *hwbz_n)
{
	GPIO_InitTypeDef    KEY_GPIO_IniStruct;
	
	RCC_APB2PeriphClockCmd(hwbz_n->config.gpio_clk, ENABLE);	
	KEY_GPIO_IniStruct.GPIO_Pin  = hwbz_n->config.gpio_pin;
	KEY_GPIO_IniStruct.GPIO_Mode = GPIO_Mode_IPD;   //上拉输入
	GPIO_Init(hwbz_n->config.gpio_port,&KEY_GPIO_IniStruct);
}
										
										
/**************************************************************************
函数功能：按键初始化
入口参数：无
返回  值：无 
**************************************************************************/
void bsp_Hwbz_Init(void)
{
	Hwbz_config(&Hwbz_LD);
	Hwbz_config(&Hwbz_LU);
	Hwbz_config(&Hwbz_RU);
	Hwbz_config(&Hwbz_RD);

} 




