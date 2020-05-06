/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ����adc
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_ADC_H
#define _BSP_ADC_H	
#include "includes.h"

/* DMA����
   ADCռ�ݵ�DMAͨ������AD1ֻռDMA1��ͨ��1
*/
#define  ADC_DMA_APBxClkCmd     RCC_AHBPeriph_DMA1
#define  ADC_DMA_Channel        DMA1_Channel1   // DMA����ͨ��
#define  ADC_DMA_FLAG           DMA1_FLAG_GL1//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 


/* ADC���� */
/* ת��ͨ������ */
#define    NOFCHANEL								5
#define    ADC_SAMPLE_NUM	          10     /* ÿ��ADCͨ������Ʒ���� */
#define    ADCx                     ADC1
#define    ADC_CLK                  RCC_APB2Periph_ADC1
#define    ADC_APBxClkCmd           RCC_APB2PeriphClockCmd

#define    ADC_GPIO_CLK1            RCC_APB2Periph_GPIOA
#define    ADC_GPIO_CLK2            RCC_APB2Periph_GPIOC
#define    ADC_GPIO_APBxClkCmd1     RCC_APB2PeriphClockCmd


#define    ADC_BAT_PORT             GPIOA
#define    ADC_BAT_PIN              GPIO_Pin_4
#define    ADC_BAT_CHANNEL          ADC_Channel_4
#define    ADC_GASA_PORT            GPIOC
#define    ADC_GASA_PIN             GPIO_Pin_2
#define    ADC_GASA_CHANNEL         ADC_Channel_12
#define    ADC_GASB_PORT            GPIOC
#define    ADC_GASB_PIN             GPIO_Pin_3
#define    ADC_GASB_CHANNEL         ADC_Channel_13
#define    ADC_GASC_PORT            GPIOC
#define    ADC_GASC_PIN             GPIO_Pin_4
#define    ADC_GASC_CHANNEL         ADC_Channel_14




/* �豸���� */
typedef enum
{
	ADC_BAT=0, 
	ADC_GASA,
	ADC_GASB,
	ADC_GASC,        
}ADCx_Kind;	


/* ���� */
typedef  struct  class_gas    CLASS_Gas; 
/* ҡ������� */
struct class_gas 
{	
	int    PriVal;      //ԭʼ������ADֵ
	int    ShieldVal;   //��ֵ
	
};

void  Adc_Init(void);
void  ADC_Filter(u16* adc_val);
u16   getAdcValue(u8 axis);

extern u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC�ɼ�ֵ��Ż�����

#endif 















