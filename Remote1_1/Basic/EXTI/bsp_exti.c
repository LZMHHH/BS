/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
  
#include "bsp_exti.h"
//一个工程  同一时间只能有一个分组    
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级  0-3
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
//高优先级的抢占优先级是可以打断正在进行的低抢占优先级中断的。
//抢占优先级相同的中断，高响应优先级不可以打断低响应优先级的中断。
//抢占优先级相同的中断，当两个中断同时发生的情况下，哪个响应优先级高，哪个先执行。
//如果两个中断的抢占优先级和响应优先级都是一样的话，则看哪个中断先发生就先执行

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
//  /* Configure one bit for preemption priority */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* 配置中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;  //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;         //子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //打开
  NVIC_Init(&NVIC_InitStructure);                           //完成配置
}


 /**
  * @brief  配置 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
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
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 // 上拉输入
  GPIO_Init(EXTI_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(EXTI_SOURCE_PORT, EXTI_SOURCE_PIN); 
  EXTI_InitStructure.EXTI_Line = EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = Exti_Trigger; //中断方式
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


