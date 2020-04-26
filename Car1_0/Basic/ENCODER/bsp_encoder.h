/**
  ******************************************************************************
  * @file    bsp_encoder.h
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_ENCODER_H
#define _BSP_ENCODER_H

#include "includes.h"

/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������ʹ��TIM2    "ע����ӳ��"
#define            ENCODE1_TIM                    TIM2
#define            ENCODE1_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE1_TIM_CLK                RCC_APB1Periph_TIM2
//#define            ENCODE1_TIM_PERIOD            0XFFFF
//#define            ENCODE1_TIM_PSC               (72-1)
// TIM ���벶��ͨ��GPIO��غ궨��
#define            ENCODE1_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE1_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE1_TIM_A_PORT             GPIOA
#define            ENCODE1_TIM_A_PIN              GPIO_Pin_15
#define            ENCODE1_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE1_TIM_B_PORT             GPIOB
#define            ENCODE1_TIM_B_PIN              GPIO_Pin_3
// �ж���غ궨��
//#define            ENCODE1_TIM_IRQ                 TIM2_IRQn
#define            ENCODE1_TIM_INT_FUN            TIM2_IRQHandler

// ��������ʹ��TIM3
#define            ENCODE2_TIM                    TIM3
#define            ENCODE2_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE2_TIM_CLK                RCC_APB1Periph_TIM3
//#define            ENCODE2_TIM_PERIOD            0XFFFF
//#define            ENCODE2_TIM_PSC               (72-1)
// TIM ���벶��ͨ��GPIO��غ궨��
#define            ENCODE2_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE2_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE2_TIM_A_PORT             GPIOA
#define            ENCODE2_TIM_A_PIN              GPIO_Pin_6
#define            ENCODE2_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE2_TIM_B_PORT             GPIOA
#define            ENCODE2_TIM_B_PIN              GPIO_Pin_7
// �ж���غ궨��
//#define            ENCODE2_TIM_IRQ                 TIM3_IRQn
#define            ENCODE2_TIM_INT_FUN             TIM3_IRQHandler

// ��������ʹ��TIM4
#define            ENCODE3_TIM                    TIM4
#define            ENCODE3_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE3_TIM_CLK                RCC_APB1Periph_TIM4
//#define            ENCODE3_TIM_PERIOD            0XFFFF
//#define            ENCODE3_TIM_PSC               (72-1)
// TIM ���벶��ͨ��GPIO��غ궨��
#define            ENCODE3_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE3_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE3_TIM_A_PORT             GPIOB
#define            ENCODE3_TIM_A_PIN              GPIO_Pin_6
#define            ENCODE3_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOB
#define            ENCODE3_TIM_B_PORT             GPIOB
#define            ENCODE3_TIM_B_PIN              GPIO_Pin_7
// �ж���غ궨��
//#define            ENCODE3_TIM_IRQ                 TIM4_IRQn
#define            ENCODE3_TIM_INT_FUN             TIM4_IRQHandler

// ��������ʹ��TIM5
#define            ENCODE4_TIM                    TIM5
#define            ENCODE4_TIM_APBxClock_FUN      RCC_APB1PeriphClockCmd
#define            ENCODE4_TIM_CLK                RCC_APB1Periph_TIM5
//#define            ENCODE4_TIM_PERIOD            0XFFFF
//#define            ENCODE4_TIM_PSC               (72-1)
// TIM ���벶��ͨ��GPIO��غ궨��
#define            ENCODE4_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ENCODE4_TIM_A_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE4_TIM_A_PORT             GPIOA
#define            ENCODE4_TIM_A_PIN              GPIO_Pin_0
#define            ENCODE4_TIM_B_GPIO_CLK         RCC_APB2Periph_GPIOA
#define            ENCODE4_TIM_B_PORT             GPIOA
#define            ENCODE4_TIM_B_PIN              GPIO_Pin_1
// �ж���غ궨��
//#define            ENCODE4_TIM_IRQ                 TIM4_IRQn
#define            ENCODE4_TIM_INT_FUN             TIM4_IRQHandler

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�


/* ���� */
typedef  struct  class_encoderdata    CLASS_EncoderData;
/* ������ʾ���� */
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
