/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   遥控遥感bsp
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



/* 设备机表 */
typedef enum
{
	ADC_BAT=0, 
	ADC_LLINE,
	ADC_LROW,
	ADC_RLINE,
	ADC_RROW,         
}ADCx_Kind;	


/* 别名 */
typedef  struct  class_joystick    CLASS_Joystick; 
/* 摇杆类参数 */
struct class_joystick 
{
	
	int    PriY;     //原始的摇杆AD值 Y
	int    PriX;     //原始的摇杆AD值 X
	
	int    NorY;     //正常的摇杆AD值 Y
	int    NorX;     //正常的摇杆AD值 X
	
	int    YZeroSet; //调零值（2048） Y
	int    XZeroSet; //调零值（2048） X
	
	int    XShieldVal;//屏蔽发送阈值  X
	int    YShieldVal;//屏蔽发送阈值  Y
	
	u8     Mode;     //当前模式
	
};

void  Adc_Init(void);
void  ADC_Filter(u16* adc_val);
u16   getAdcValue(u8 axis);

extern u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC采集值存放缓冲区

#endif 















