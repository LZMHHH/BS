/**
  ******************************************************************************
  * @file    bsp_adc.c
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
#include "bsp_adc.h"




u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC采集值存放缓冲区
 

/**************************************************************************
函数功能：获取全部ADC均值
入口参数：滤波后的ADC数据
返回  值：
**************************************************************************/

void ADC_Filter(u16* adc_val)
{
	u16 i=0;
	u8  j=0;
	u32 sum[NOFCHANEL]={0};
	
	for(;i<ADC_SAMPLE_NUM;i++)
	{
		for(j=0;j<NOFCHANEL;j++)
		{
			sum[j]+=AdcValue[NOFCHANEL*i+j];
		}
	}
	for(j=0;j<NOFCHANEL;j++)
	{
		adc_val[j]=sum[j]/ADC_SAMPLE_NUM;
	}
}	

/**************************************************************************
函数功能：获取ADC
入口参数：ADC1的通道 顺序
返回  值：AD转换结果
**************************************************************************/
u16 getAdcValue(u8 axis)
{
	u32 sum=0;
	for(u8 i=0;i<ADC_SAMPLE_NUM;i++)
	{
		sum += AdcValue[NOFCHANEL*i+axis];
	}
	return sum/ADC_SAMPLE_NUM;
}



void Adc_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	ADC_GPIO_APBxClkCmd1(ADC_GPIO_CLK1|ADC_GPIO_CLK2,ENABLE);
	
	//PA0 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = ADC_LLINE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(ADC_LLINE_PORT, &GPIO_InitStructure);	
	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = ADC_LROW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(ADC_LROW_PORT, &GPIO_InitStructure);	
	//PA2 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = ADC_RLINE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(ADC_RLINE_PORT, &GPIO_InitStructure);	
	//PB0 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = ADC_RROW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(ADC_RROW_PORT, &GPIO_InitStructure);	
	//PB1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(ADC_BAT_PORT, &GPIO_InitStructure);	

}

void Adc_Dma_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_APBxClkCmd, ENABLE);//使能DMA时钟
	
	//DMA 配置
	DMA_DeInit(ADC_DMA_Channel);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADCx->DR;	 //ADC1->DR地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AdcValue;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL*ADC_SAMPLE_NUM;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址增加
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC_DMA_Channel, &DMA_InitStructure);
	DMA_Cmd(ADC_DMA_Channel, ENABLE);
	
}

void Adc_Adc_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	
	ADC_APBxClkCmd(ADC_CLK,ENABLE);//使ADC1时钟
	
	ADC_DeInit(ADCx);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//扫描模式，用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADCx, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	ADC_Cmd(ADCx, ENABLE);	//使能指定的ADC1
	ADC_DMACmd(ADCx, ENABLE);//使能ADC1 DMA
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	/* 配置连续转换通道，55.5个采样周期 */
	ADC_RegularChannelConfig(ADCx, ADC_BAT_CHANNEL, ADC_BAT+1, ADC_SampleTime_239Cycles5);	//1个通道转换一次耗时21us 4个通道
	ADC_RegularChannelConfig(ADCx, ADC_LLINE_CHANNEL,  ADC_LLINE+1, ADC_SampleTime_239Cycles5);	//采样个数ADC_SAMPLE_NUM
	ADC_RegularChannelConfig(ADCx, ADC_LROW_CHANNEL, ADC_LROW+1, ADC_SampleTime_239Cycles5);	//总共耗时4*21*ADC_SAMPLE_NUM（64）=5.4ms<10ms
	ADC_RegularChannelConfig(ADCx, ADC_RLINE_CHANNEL,  ADC_RLINE+1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_RROW_CHANNEL,   ADC_RROW+1, ADC_SampleTime_239Cycles5);
	
	ADC_ResetCalibration(ADCx);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADCx));	//等待复位校准结束
	
	ADC_StartCalibration(ADCx);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADCx));	 //等待校准结束
 
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//使能指定的ADC1的软件转换启动功能
	
}

void  Adc_Init(void)
{    
 	
	Adc_Gpio_Init();
	Adc_Dma_Init();
	Adc_Adc_Init();
	
}	

