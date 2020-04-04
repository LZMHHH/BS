/**
  ******************************************************************************
  * @file    bsp_exti.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_EXTI_H
#define	_BSP_EXTI_H


#include "includes.h"


/*外部中断EXIT相关宏定义*/   
#define             EXTI_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define             EXTI_GPIO_PORT                       GPIOA          //中断引脚
#define             EXTI_GPIO_PIN                        GPIO_Pin_5   //中断引脚
#define             EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOA
#define             EXTI_SOURCE_PIN                      GPIO_PinSource5
#define             EXTI_LINE                            EXTI_Line5
#define             EXTI_IRQ                             EXTI9_5_IRQn
#define             EXTI_INT_FUNCTION                    EXTI9_5_IRQHandler

//促发方式
#if       Interrupt_Trigger    // 0
#define   Exti_Trigger EXTI_Trigger_Rising   //1

#else  
#define   Exti_Trigger EXTI_Trigger_Falling   //0
#endif

#define   ENABLE_INV_INTERRUPTS  EnableInvInterrupt()
#define   DISABLE_INV_INTERRUPTS DisableInvInterrupt()



void EXTI_Pxy_Config(void);

void EnableInvInterrupt(void);
void DisableInvInterrupt(void);




#endif /* __EXTI_H */

/*********************************************END OF FILE**********************/





















