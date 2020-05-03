 /**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   CAN驱动
  ******************************************************************************
  * @attention
  *	实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  ******************************************************************************
  */
  
#include "bsp_can.h"


//1.初始化CAN外设、波特率，位的组成
//2.配置筛选器，方便接收数据
//3.发送数据，并接收，使用回环模式测试

/* 定义全局变量 */
CanTxMsg tCanTxMsg;	/* 用于发送 */
CanRxMsg tCanRxMsg;	/* 用于接收 */

/**
  * @brief  CAN_GPIO_Config初始化
  * @param  无
  * @retval 无
  */
void CAN_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能CAN时钟 */
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1 , ENABLE );
	
	/* 使能CAN引脚相关的时钟 */
 	RCC_APB2PeriphClockCmd ( CAN_GPIO_CLK, ENABLE );	
//	/* 使能CAN引脚相关的时钟 */
// 	RCC_APB2PeriphClockCmd ( CAN_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE );	
//	//使用PA8 9引脚的第二功能
//	GPIO_PinRemapConfig (GPIO_Remap1_CAN1 ,ENABLE);
	
  /* 配置CAN的 引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = CAN_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(CAN_TX_GPIO_PROT, &GPIO_InitStructure);
	
	/* 配置CAN的 引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
	
}


void CAN_Mode_Config(void)	
{

	CAN_InitTypeDef CAN_InitTypeStruct;
	
	CAN_DeInit(CAN1);						/* 复位CAN寄存器 */
	CAN_StructInit(&CAN_InitTypeStruct);		/* 填充CAN参数结构体成员为缺省值 */
	
	CAN_InitTypeStruct.CAN_ABOM = ENABLE;
	CAN_InitTypeStruct.CAN_AWUM = ENABLE;
	CAN_InitTypeStruct.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_Normal;//调试时建议使用回环模式（CAN_Mode_LoopBack），调试完再改成NORMAL
	CAN_InitTypeStruct.CAN_NART = ENABLE; //错误重传
	CAN_InitTypeStruct.CAN_RFLM = ENABLE;
	CAN_InitTypeStruct.CAN_TTCM = DISABLE;
	CAN_InitTypeStruct.CAN_TXFP = DISABLE; //按ID优先级发送
	
	//配置成1Mbps
	CAN_InitTypeStruct.CAN_BS1 = CAN_BS1_5tq;
	CAN_InitTypeStruct.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitTypeStruct.CAN_SJW = CAN_SJW_2tq;
	CAN_InitTypeStruct.CAN_Prescaler = 4;
	
	
	CAN_Init(CAN1,&CAN_InitTypeStruct);

}



void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitTypeStruct;
	
	CAN_FilterInitTypeStruct.CAN_FilterActivation = ENABLE;
	CAN_FilterInitTypeStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0  ;
	CAN_FilterInitTypeStruct.CAN_FilterNumber = 0;
	CAN_FilterInitTypeStruct.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitTypeStruct.CAN_FilterMode = CAN_FilterMode_IdMask  ;
	
	/* 如果需要滤掉不需要的ID，百度即可 */
//	CAN_FilterInitTypeStruct.CAN_FilterIdHigh = ((PASS_ID<<3 |CAN_Id_Standard |CAN_RTR_Data)&0xFFFF0000)>>16;
//	CAN_FilterInitTypeStruct.CAN_FilterIdLow = ((PASS_ID<<3 |CAN_Id_Standard |CAN_RTR_Data)&0xFFFF);
	CAN_FilterInitTypeStruct.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitTypeStruct.CAN_FilterIdLow = 0x0000;	
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdLow =0x0000;	

	
	
	CAN_FilterInit(&CAN_FilterInitTypeStruct);
	
	CAN_ITConfig (CAN1,CAN_IT_FMP0,ENABLE);
	
}	

void CAN_NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void bsp_CAN_Init(void)	
{
	CAN_GPIO_Config();
  CAN_Mode_Config();
	CAN_Filter_Config();
	CAN_NVIC_Config();

}
 
/*
*********************************************************************************************************
*	函 数 名: USB_LP_CAN1_RX0_IRQHandler
*	功能说明: CAN中断服务程序.
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/ 
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	CAN_Receive(CAN1, CAN_FIFO0, &tCanRxMsg);
	
	xQueueSendFromISR(  xQueue_canRx,               /* 消息队列的句柄 */
                    (void *)&tCanRxMsg,                   /* 发送的消息内容 */
                            &xHigherPriorityTaskWoken); /* 高优先级任务是否被唤醒的状态保存 */
					  
	/* 如果xHigherPriorityTaskWoken = pdTRUE，那么退出中断后切到当前最高优先级任务执行 */
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	
}

/*********************************************END OF FILE**********************/
