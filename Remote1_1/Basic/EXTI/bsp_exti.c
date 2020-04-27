/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
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
  
#include "bsp_exti.h"
//һ������  ͬһʱ��ֻ����һ������    
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:2λ��ռ���ȼ�,2λ��Ӧ���ȼ�  0-3
//��3:3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//�����ȼ�����ռ���ȼ��ǿ��Դ�����ڽ��еĵ���ռ���ȼ��жϵġ�
//��ռ���ȼ���ͬ���жϣ�����Ӧ���ȼ������Դ�ϵ���Ӧ���ȼ����жϡ�
//��ռ���ȼ���ͬ���жϣ��������ж�ͬʱ����������£��ĸ���Ӧ���ȼ��ߣ��ĸ���ִ�С�
//��������жϵ���ռ���ȼ�����Ӧ���ȼ�����һ���Ļ������ĸ��ж��ȷ�������ִ��

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
//  /* Configure one bit for preemption priority */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;  //��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;         //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //��
  NVIC_Init(&NVIC_InitStructure);                           //�������
}


 /**
  * @brief  ���� Ϊ���жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Pxy_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(EXTI_GPIO_CLK,ENABLE);
												
	/* config the NVIC */
	NVIC_Configuration();

	/* EXTI line gpio config*/	
  GPIO_InitStructure.GPIO_Pin = EXTI_GPIO_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 // ��������
  GPIO_Init(EXTI_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(EXTI_SOURCE_PORT, EXTI_SOURCE_PIN); 
  EXTI_InitStructure.EXTI_Line = EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = Exti_Trigger; //�жϷ�ʽ
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


void EnableInvInterrupt(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  /* Configure EXTI Line1 */
  EXTI_InitStructure.EXTI_Line = EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = Exti_Trigger;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
void DisableInvInterrupt(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
    /* Configure EXTI Line1 */
  EXTI_InitStructure.EXTI_Line = EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = Exti_Trigger;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_ClearITPendingBit(EXTI_LINE);
}
/*********************************************END OF FILE**********************/


