/**
  ******************************************************************************
  * @file    bsp_exti.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_EXTI_H
#define	_BSP_EXTI_H


#include "includes.h"


/*�ⲿ�ж�EXIT��غ궨��*/   
#define             EXTI_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define             EXTI_GPIO_PORT                       GPIOA          //�ж�����
#define             EXTI_GPIO_PIN                        GPIO_Pin_5   //�ж�����
#define             EXTI_SOURCE_PORT                     GPIO_PortSourceGPIOA
#define             EXTI_SOURCE_PIN                      GPIO_PinSource5
#define             EXTI_LINE                            EXTI_Line5
#define             EXTI_IRQ                             EXTI9_5_IRQn
#define             EXTI_INT_FUNCTION                    EXTI9_5_IRQHandler

//�ٷ���ʽ
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





















