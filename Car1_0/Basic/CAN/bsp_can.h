 /**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   CAN����
  ******************************************************************************
  * @attention
  *	ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  ******************************************************************************
  */
#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "includes.h"


#define PASS_ID   ((uint32_t)CAN_EVNID)


#define  CAN_TX_GPIO_PROT  		GPIOA
#define  CAN_TX_GPIO_PIN   		GPIO_Pin_12

#define  CAN_RX_GPIO_PORT     GPIOA
#define  CAN_RX_GPIO_PIN      GPIO_Pin_11

#define  CAN_GPIO_CLK					RCC_APB2Periph_GPIOA



/* �㲥 */
/* ����ȫ�ֱ��� */
extern CanTxMsg tCanTxMsg;	/* ���ڷ��� */
extern CanRxMsg tCanRxMsg;	/* ���ڽ��� */


void bsp_CAN_Init(void)	;     


#endif /* __BSP_CAN_H */

