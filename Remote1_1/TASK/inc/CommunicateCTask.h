/**
  ******************************************************************************
  * @file    CommunicateCTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __COMMUNICATE_C_TASK_H
#define __COMMUNICATE_C_TASK_H	 

#include "includes.h"

/* �¼���궨�� */
#define EVENT_uart3OLEDCLEAR (0x01 << 8)
#define EVENT_uart3CARUI    (0x01 << 16)
#define EVENT_uart3CARUIREQ (0x01 << 17)




//Uart1�Ľ�������
void vTaskUart3Rx( void * pvParameters );
void vTaskUart3Tx( void * pvParameters );
void vTaskuart3SendData( void * pvParameters );
#endif







