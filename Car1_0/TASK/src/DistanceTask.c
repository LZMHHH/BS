/**
  ******************************************************************************
  * @file    DistanceTask.c
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
#include "DistanceTask.h"

CLASS_Distance Distance;

static void Para_Init(void);

void vTaskDistance( void * pvParameters )
{
	
	/* ��ʼ������ */
	Para_Init();
	
	while(1)
	{

		DistanceRead(&Distance);
		
		
		vTaskDelay( 50 );
	}
	
}

static void Para_Init(void)
{
	Distance.offset = 0;
}

void canSendVl53l0xData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_BZID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_VL53L0X;
					p.Data[3] = CAN_Val;
					memcpy(p.Data+4, &(Distance.xmm), sizeof(Distance.xmm));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[2] = CAN_VL53L0X;
					p.Data[3] = CAN_Offset;
					memcpy(p.Data+4, &(Distance.offset), sizeof(Distance.offset));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					p.StdId = CAN_BZID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_VL53L0X;
					p.Data[3] = CAN_Shield;
					memcpy(p.Data+4, &(Distance.shieldVal), sizeof(Distance.shieldVal));  /* �ر����⣬���ֽ���ǰ */
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
					flag = 0;	
					break;
	}
	
}	

void uart1SendVl53l0xData(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDCar;
	p.dataLen = sizeof(Distance) + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_Vl53l0XDATA;
	memcpy(p.data+2, &Distance, sizeof(Distance));
	xQueueSend(xQueue_uart1Tx, &p, 10);
}	



