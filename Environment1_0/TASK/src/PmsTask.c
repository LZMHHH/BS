/**
  ******************************************************************************
  * @file    PmsTask.c
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
#include "PmsTask.h"

CLASS_Pms Pms; 

static void Para_Init(void);
void canSendPmsData(void);
void UpdataPms(uint8_t *databuff,CLASS_Pms *pms);
void PmsCon(void);
void AQI_Scan(void);

void vTaskPms( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	uint8_t    ReadBuff[DEBUG2_RX_BSIZE];  /* ʵ���� ����copy����*/\
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	Para_Init();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart2Rx,           /* ��Ϣ���еľ�� */
                             (void *)&ReadBuff,        /* ���͵���Ϣ���� */
                             portMAX_DELAY);           /* �ȴ�ʱ�� һֱ�� */
														 
		UpdataPms(ReadBuff,&Pms);
							 
		PmsCon();
		AQI_Scan();
							 
		/* ��Ϊpms������200-800ms�ŷ���һ���������������ԣ�����ֱ��can��ȥ */
		canSendPmsData();

	}
	
}


static void Para_Init(void)
{
	Pms.shieldPM2_5Val = 100;
	Pms.shieldPM10Val  = 100;
	
	Pms.mode           = enFre;
	
//	digitalHi(Flz.config.gpio_port,Flz.config.gpio_pin);
}

void AQI_Scan(void)
{
	u16 APMx;
	APMx  =  (Pms.PM2_5_Vol + Pms.PM10_Vol)/2;
	if( ((Smog.PriVal > Smog.ShieldVal || Hydrogen.PriVal > Hydrogen.ShieldVal || CO.PriVal > CO.ShieldVal) 
	  && (Smog.PriVal < 6500 && Hydrogen.PriVal < 6500  && CO.PriVal < 6500)))
	{
		Pms.AQI = 7;  //��
		LedA.cycle = 5;  
	}
	else
	{
		if(APMx < 50)
		{
			Pms.AQI = 1;  //��
			LedA.cycle = 70; 
		}
		else
		{
			if(APMx < 100)
			{
				Pms.AQI = 2;  //��
				LedA.cycle = 50; 
		  }
			else
			{
				if(APMx < 150)
				{
					Pms.AQI = 3;  //���
					LedA.cycle = 40; 
				}
				else
				{
					if(APMx < 200)
					{
						Pms.AQI = 4;  //�ж�
						LedA.cycle = 30; 
					}
					else
					{
						if(APMx < 300)
						{
							Pms.AQI = 5;  //�ض�
							LedA.cycle = 20; 
						}
						else
						{
							Pms.AQI = 6;  //����
							LedA.cycle = 10; 
						}
					}
				}
			}
		}
	}
}
/* ���� */
void PmsCon(void)
{
	switch(Huimiture.huim_mode)
	{
		case enOFF:
			 digitalLo(Flz.config.gpio_port,Flz.config.gpio_pin);
			 break;
		case enON:
			 digitalHi(Flz.config.gpio_port,Flz.config.gpio_pin);
			 break;
		case enFre:
			 if(Pms.PM2_5_Vol > Pms.shieldPM2_5Val || Pms.PM10_Vol > Pms.shieldPM10Val)
			 {
				 digitalHi(Flz.config.gpio_port,Flz.config.gpio_pin);
			 }
			 else
			 {
				 digitalLo(Flz.config.gpio_port,Flz.config.gpio_pin);
			 }
			 break;
	}
}


void UpdataPms(uint8_t *databuff,CLASS_Pms *pms)
{
	if(databuff[0] == 0x42)
	{
		if(databuff[1] == 0x4d)
		{
			 pms->PM2_5_Vol = (databuff[12] << 8) | databuff[13];
			 pms->PM10_Vol  = (databuff[14] << 8) | databuff[15]; 
		}
	}
}


void canSendPmsData(void)
{
	u16 u16data;
	
	CanTxMsg p;
	
	/* ����sht3x���¶����� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM2_5;
	u16data = (u16)(Pms.PM2_5_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* ����sht3x���¶����� */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM10;
	u16data = (u16)(Pms.PM10_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_PM2_5Shield;
	u16data = (u16)(Pms.shieldPM2_5Val);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[3] = CAN_PM10Shield;
	u16data = (u16)(Pms.shieldPM10Val);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_AQI;
	p.Data[4] = Pms.AQI;
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[3] = CAN_MODE;
	p.Data[4] = Pms.mode;
	xQueueSend(xQueue_canTx, &p, 30);
	
}

