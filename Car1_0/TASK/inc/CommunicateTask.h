/**
  ******************************************************************************
  * @file    CommunicateTask.h
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
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
#ifndef __COMMUNICATETASK_H
#define __COMMUNICATETASK_H	 

#include "includes.h"

/* �¼���궨�� */
#define EVENT_MOTOR    (0x01 << 1)//�����¼������λ1:�ϴ�pwm�¼�
#define EVENT_ENCODER  (0x01 << 2)//�����¼������λ2:�ϴ��������¼�
#define EVENT_LED      (0x01 << 3)//�����¼������λ3:�ϴ�led�¼�
#define EVENT_KEYACK   (0x01 << 4)//�����¼������λ4:����EVENT_KEYACK�¼�



//Uart1������
void vTaskUart1Rx( void * pvParameters );
void vTaskUart1Tx( void * pvParameters );

//���ڵ��ϲ�����
void vTaskSendData( void * pvParameters );

#endif







