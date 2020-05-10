/**
  ******************************************************************************
  * @file    LightTask.c
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
#include "LightTask.h"

CLASS_Light Light; 


static void Para_Init(void);
void canSendGy30Data(void);


void vTaskLight( void * pvParameters )
{
	Para_Init();
	
	/* ����ʱ����ģ��׼������ */
	vTaskDelay( 200 );
	
	while(1)
	{

		Updata_BH1750(&Light);
		
		canSendGy30Data();
		
		vTaskDelay( 200 );
	}
	
}

static void Para_Init(void)
{
	Light.shieldVal = 2000;
	Light.a         = 1.0;
}

void canSendGy30Data(void)
{
	int intdata;
	CanTxMsg p;
	
	/* �������� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_GY30;
	p.Data[3] = CAN_Light;
	intdata = (int)((Light.BH_Voltage)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_Shield;
	intdata = (int)((Light.shieldVal)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_MODE;
	p.Data[4] = Light.a;
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_FactorA;
	intdata = (int)((Light.a)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
}



