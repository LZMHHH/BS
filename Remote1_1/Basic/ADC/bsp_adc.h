/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ң��ң��bsp
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
#define    ADC_GPIO_CLK2            RCC_APB2Periph_GPIOB
#define    ADC_GPIO_APBxClkCmd1     RCC_APB2PeriphClockCmd

#define    ADC_BAT_PORT             GPIOA
#define    ADC_BAT_PIN              GPIO_Pin_2
#define    ADC_BAT_CHANNEL          ADC_Channel_2
#define    ADC_LLINE_PORT           GPIOA
#define    ADC_LLINE_PIN            GPIO_Pin_0
#define    ADC_LLINE_CHANNEL        ADC_Channel_0
#define    ADC_LROW_PORT            GPIOA
#define    ADC_LROW_PIN             GPIO_Pin_1
#define    ADC_LROW_CHANNEL         ADC_Channel_1
#define    ADC_RLINE_PORT           GPIOB
#define    ADC_RLINE_PIN            GPIO_Pin_0
#define    ADC_RLINE_CHANNEL        ADC_Channel_8
#define    ADC_RROW_PORT            GPIOB
#define    ADC_RROW_PIN             GPIO_Pin_1
#define    ADC_RROW_CHANNEL         ADC_Channel_9



/* �豸���� */
typedef enum
{
	ADC_BAT=0, 
	ADC_LLINE,
	ADC_LROW,
	ADC_RLINE,
	ADC_RROW,         
}ADCx_Kind;	


/* ���� */
typedef  struct  class_joystick    CLASS_Joystick; 
/* ҡ������� */
struct class_joystick 
{
	
	int    PriY;     //ԭʼ��ҡ��ADֵ Y
	int    PriX;     //ԭʼ��ҡ��ADֵ X
	
	int    NorY;     //������ҡ��ADֵ Y
	int    NorX;     //������ҡ��ADֵ X
	
	int    YZeroSet; //����ֵ��2048�� Y
	int    XZeroSet; //����ֵ��2048�� X
	
	int    XShieldVal;//���η�����ֵ  X
	int    YShieldVal;//���η�����ֵ  Y
	
	u8     Mode;     //��ǰģʽ
	
};

void  Adc_Init(void);
void  ADC_Filter(u16* adc_val);
u16   getAdcValue(u8 axis);

extern u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC�ɼ�ֵ��Ż�����

#endif 















