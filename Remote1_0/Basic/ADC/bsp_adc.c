/**
  ******************************************************************************
  * @file    bsp_adc.c
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
#include "bsp_adc.h"




u16 AdcValue[NOFCHANEL*ADC_SAMPLE_NUM];//ADC�ɼ�ֵ��Ż�����
 

/**************************************************************************
�������ܣ���ȡȫ��ADC��ֵ
��ڲ������˲����ADC����
����  ֵ��
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
�������ܣ���ȡADC
��ڲ�����ADC1��ͨ�� ˳��
����  ֵ��ADת�����
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
	
	//PA0 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = ADC_LLINE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(ADC_LLINE_PORT, &GPIO_InitStructure);	
	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = ADC_LROW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(ADC_LROW_PORT, &GPIO_InitStructure);	
	//PA2 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = ADC_RLINE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(ADC_RLINE_PORT, &GPIO_InitStructure);	
	//PB0 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = ADC_RROW_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(ADC_RROW_PORT, &GPIO_InitStructure);	
	//PB1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(ADC_BAT_PORT, &GPIO_InitStructure);	

}

void Adc_Dma_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(ADC_DMA_APBxClkCmd, ENABLE);//ʹ��DMAʱ��
	
	//DMA ����
	DMA_DeInit(ADC_DMA_Channel);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADCx->DR;	 //ADC1->DR��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AdcValue;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL*ADC_SAMPLE_NUM;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC_DMA_Channel, &DMA_InitStructure);
	DMA_Cmd(ADC_DMA_Channel, ENABLE);
	
}

void Adc_Adc_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	
	ADC_APBxClkCmd(ADC_CLK,ENABLE);//ʹADC1ʱ��
	
	ADC_DeInit(ADCx);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//ɨ��ģʽ�����ڶ�ͨ���ɼ�
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADCx, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADCx, ENABLE);	//ʹ��ָ����ADC1
	ADC_DMACmd(ADCx, ENABLE);//ʹ��ADC1 DMA
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	/* ��������ת��ͨ����55.5���������� */
	ADC_RegularChannelConfig(ADCx, ADC_BAT_CHANNEL, ADC_BAT+1, ADC_SampleTime_239Cycles5);	//1��ͨ��ת��һ�κ�ʱ21us 4��ͨ��
	ADC_RegularChannelConfig(ADCx, ADC_LLINE_CHANNEL,  ADC_LLINE+1, ADC_SampleTime_239Cycles5);	//��������ADC_SAMPLE_NUM
	ADC_RegularChannelConfig(ADCx, ADC_LROW_CHANNEL, ADC_LROW+1, ADC_SampleTime_239Cycles5);	//�ܹ���ʱ4*21*ADC_SAMPLE_NUM��64��=5.4ms<10ms
	ADC_RegularChannelConfig(ADCx, ADC_RLINE_CHANNEL,  ADC_RLINE+1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_RROW_CHANNEL,   ADC_RROW+1, ADC_SampleTime_239Cycles5);
	
	ADC_ResetCalibration(ADCx);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADCx));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADCx);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADCx));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	
}

void  Adc_Init(void)
{    
 	
	Adc_Gpio_Init();
	Adc_Dma_Init();
	Adc_Adc_Init();
	
}	

