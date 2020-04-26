/**
  ******************************************************************************
  * @file    bsp_encoder.h
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_ENCODER_H
#define _BSP_ENCODER_H

#include "includes.h"

/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里使用TIM2    "注意重映射"
#define            ENCODE1_TIM                    TIM2
#define            ENCODE1_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE1_TIM_CLK                RCC_APB1Periph_TIM2
//#define            ENCODE1_TIM_PERIOD            0XFFFF
//#define            ENCODE1_TIM_PSC               (72-1)
// TIM 输入捕获通道GPIO相关宏定义
#define            ENCODE1_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE1_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE1_TIM_A_PORT             GPIOA
#define            ENCODE1_TIM_A_PIN              GPIO_Pin_15
#define            ENCODE1_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE1_TIM_B_PORT             GPIOB
#define            ENCODE1_TIM_B_PIN              GPIO_Pin_3
// 中断相关宏定义
//#define            ENCODE1_TIM_IRQ                 TIM2_IRQn
#define            ENCODE1_TIM_INT_FUN            TIM2_IRQHandler

// 我们这里使用TIM3
#define            ENCODE2_TIM                    TIM3
#define            ENCODE2_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE2_TIM_CLK                RCC_APB1Periph_TIM3
//#define            ENCODE2_TIM_PERIOD            0XFFFF
//#define            ENCODE2_TIM_PSC               (72-1)
// TIM 输入捕获通道GPIO相关宏定义
#define            ENCODE2_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE2_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE2_TIM_A_PORT             GPIOA
#define            ENCODE2_TIM_A_PIN              GPIO_Pin_6
#define            ENCODE2_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE2_TIM_B_PORT             GPIOA
#define            ENCODE2_TIM_B_PIN              GPIO_Pin_7
// 中断相关宏定义
//#define            ENCODE2_TIM_IRQ                 TIM3_IRQn
#define            ENCODE2_TIM_INT_FUN             TIM3_IRQHandler

// 我们这里使用TIM4
#define            ENCODE3_TIM                    TIM4
#define            ENCODE3_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE3_TIM_CLK                RCC_APB1Periph_TIM4
//#define            ENCODE3_TIM_PERIOD            0XFFFF
//#define            ENCODE3_TIM_PSC               (72-1)
// TIM 输入捕获通道GPIO相关宏定义
#define            ENCODE3_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE3_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE3_TIM_A_PORT             GPIOB
#define            ENCODE3_TIM_A_PIN              GPIO_Pin_6
#define            ENCODE3_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE3_TIM_B_PORT             GPIOB
#define            ENCODE3_TIM_B_PIN              GPIO_Pin_7
// 中断相关宏定义
//#define            ENCODE3_TIM_IRQ                 TIM4_IRQn
#define            ENCODE3_TIM_INT_FUN             TIM4_IRQHandler

// 我们这里使用TIM5
#define            ENCODE4_TIM                    TIM5
#define            ENCODE4_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE4_TIM_CLK                RCC_APB1Periph_TIM5
//#define            ENCODE4_TIM_PERIOD            0XFFFF
//#define            ENCODE4_TIM_PSC               (72-1)
// TIM 输入捕获通道GPIO相关宏定义
#define            ENCODE4_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE4_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE4_TIM_A_PORT             GPIOA
#define            ENCODE4_TIM_A_PIN              GPIO_Pin_0
#define            ENCODE4_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE4_TIM_B_PORT             GPIOA
#define            ENCODE4_TIM_B_PIN              GPIO_Pin_1
// 中断相关宏定义
//#define            ENCODE4_TIM_IRQ                 TIM4_IRQn
#define            ENCODE4_TIM_INT_FUN             TIM4_IRQHandler

#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。


/* 别名 */
typedef  struct  class_encoderdata    CLASS_EncoderData;
/* 界面显示参数 */
struct class_encoderdata 
{
	int   encoderAVal;
	int   encoderBVal;
	int   encoderCVal;
	int   encoderDVal;
};





void Encoder1_Init_TIM(void);
void Encoder2_Init_TIM(void);
void Encoder3_Init_TIM(void);
void Encoder4_Init_TIM(void);
int Read_Encoder(u8 TIMX);
void TIM4_IRQHandler(void);
void TIM2_IRQHandler(void);
#endif
