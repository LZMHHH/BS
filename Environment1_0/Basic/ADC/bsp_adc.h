/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   气体adc
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_ADC_H
#define _BSP_ADC_H	
#include "includes.h"

/* DMA配置
   ADC占据的DMA通道：如AD1只占DMA1的通道1
*/
#define  ADC_DMA_APBxClkCmd     RCC_AHBPeriph_DMA1
#define  ADC_DMA_Channel        DMA1_Channel1   // DMA请求通道
#define  ADC_DMA_FLAG           DMA1_FLAG_GL1//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 


/* ADC配置 */
/* 转换通道个数 */
#define    NOFCHANEL								5
#define    ADC_SAMPLE_NUM	          10     /* 每个ADC通道的样品数量 */
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




/* 设备机表 */
typedef enum
{
	ADC_BAT=0, 
	ADC_GASA,
	ADC_GASB,
	ADC_GASC,        
}ADCx_Kind;	


/* 别名 */
typedef  struct  class_gas    CLASS_Gas; 
/* 摇杆类参数 */
struct class_gas 
{	
	int    PriVal;      //原始的气体AD值
	int    ShieldVal;   //阈值
	
};

void  Adc_Init(void);
void  ADC_Filter(u16* adc_val);
u16   getAdcValue(u8 axis);

extern u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC采集值存放缓冲区

#endif 















