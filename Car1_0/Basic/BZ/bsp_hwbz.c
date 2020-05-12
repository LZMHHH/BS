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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "bsp_hwbz.h"

//�������� + ����
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
�������ܣ������������ų�ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
static void Hwbz_config(CLASS_Hwbz *hwbz_n)
{
	GPIO_InitTypeDef    KEY_GPIO_IniStruct;
	
	RCC_APB2PeriphClockCmd(hwbz_n->config.gpio_clk, ENABLE);	
	KEY_GPIO_IniStruct.GPIO_Pin  = hwbz_n->config.gpio_pin;
	KEY_GPIO_IniStruct.GPIO_Mode = GPIO_Mode_IPD;   //��������
	GPIO_Init(hwbz_n->config.gpio_port,&KEY_GPIO_IniStruct);
}
										
										
/**************************************************************************
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void bsp_Hwbz_Init(void)
{
	Hwbz_config(&Hwbz_LD);
	Hwbz_config(&Hwbz_LU);
	Hwbz_config(&Hwbz_RU);
	Hwbz_config(&Hwbz_RD);

} 




