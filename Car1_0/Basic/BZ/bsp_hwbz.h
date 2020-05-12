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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __HWBZ_H
#define __HWBZ_H	 
#include "includes.h"


#define HWBZ_TURE  0
#define HWBZ_FALSE 1			

//����
typedef  struct  class_hwbz         CLASS_Hwbz;



/* �豸���� */
typedef enum
{
	enHwbz_NO,          
	enHwbz_LD,       
	enHwbz_LU,
	enHwbz_RU,
	enHwbz_RD,		
}HWBZx_Status;		


//��������
typedef struct class_hwbz_config
{
	uint32_t      gpio_clk;
	GPIO_TypeDef* gpio_port;
	uint32_t      gpio_pin;
}CLASS_Hwbz_config;

//������
struct class_hwbz 
{
	u8      name;       //�������֣�ö��
	u8      status;     //״̬
	
	CLASS_Hwbz_config   config;         //��������
};


//��������
extern CLASS_Hwbz   Hwbz_LD;  
extern CLASS_Hwbz   Hwbz_LU;  
extern CLASS_Hwbz   Hwbz_RU; 
extern CLASS_Hwbz   Hwbz_RD;

#define Hwbz_Pre(a)	       GPIO_ReadInputDataBit(a.config.gpio_port,a.config.gpio_pin) 

void   bsp_Hwbz_Init      (void);          //��ʼ��

#endif 
