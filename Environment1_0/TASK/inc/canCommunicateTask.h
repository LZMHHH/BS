/**
  ******************************************************************************
  * @file    canCommunicateTask.h
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
#ifndef _CAN_COMMUNICATETASK_H
#define _CAN_COMMUNICATETASK_H	 

#include "includes.h"

void vTaskCanRx( void * pvParameters );
void vTaskCanTx( void * pvParameters );


/* �¼���궨�� */
#define EVENT_SHT3X    (0x01 << 1)//�����¼������λ1:�ϴ�pwm�¼�
#define EVENT_GY30     (0x01 << 2)
#define EVENT_PMS      (0x01 << 3)
#define EVENT_BME      (0x01 << 4)
#define EVENT_LED      (0x01 << 11)

//�ϴ���������
void vTaskcanSendData( void * pvParameters );

#endif







