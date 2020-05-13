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
void vTaskcanSendData( void * pvParameters );

/* �¼���궨�� */
#define EVENT_canSHT3X    (0x01 << 1)//�����¼������λ1:�ϴ�pwm�¼�
#define EVENT_canGY30     (0x01 << 2)
#define EVENT_canPMS      (0x01 << 3)
#define EVENT_canBME      (0x01 << 4)
#define EVENT_canLED      (0x01 << 11)
#define EVENT_canOLEDCLEAR (0x01 << 8)
#define EVENT_canCARUI    (0x01 << 16)
#define EVENT_canENVUI    (0x01 << 17)
#define EVENT_canCARUIREQ (0x01 << 18)

//�ϴ���������
void vTaskcanSendData( void * pvParameters );

#endif







