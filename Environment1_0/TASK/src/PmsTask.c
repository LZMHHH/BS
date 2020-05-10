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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
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
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	uint8_t    ReadBuff[DEBUG2_RX_BSIZE];  /* 实数组 接收copy数据*/\
	//const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	Para_Init();
	
	while(1)
	{
		xReturn = xQueueReceive( xQueue_uart2Rx,           /* 消息队列的句柄 */
                             (void *)&ReadBuff,        /* 发送的消息内容 */
                             portMAX_DELAY);           /* 等待时间 一直等 */
														 
		UpdataPms(ReadBuff,&Pms);
							 
		PmsCon();
		AQI_Scan();
							 
		/* 因为pms器件隔200-800ms才发送一次数据上来，所以，可以直接can出去 */
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
		Pms.AQI = 7;  //毒
		LedA.cycle = 5;  
	}
	else
	{
		if(APMx < 50)
		{
			Pms.AQI = 1;  //优
			LedA.cycle = 70; 
		}
		else
		{
			if(APMx < 100)
			{
				Pms.AQI = 2;  //良
				LedA.cycle = 50; 
		  }
			else
			{
				if(APMx < 150)
				{
					Pms.AQI = 3;  //轻度
					LedA.cycle = 40; 
				}
				else
				{
					if(APMx < 200)
					{
						Pms.AQI = 4;  //中度
						LedA.cycle = 30; 
					}
					else
					{
						if(APMx < 300)
						{
							Pms.AQI = 5;  //重度
							LedA.cycle = 20; 
						}
						else
						{
							Pms.AQI = 6;  //严重
							LedA.cycle = 10; 
						}
					}
				}
			}
		}
	}
}
/* 控制 */
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
	
	/* 发送sht3x的温度数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM2_5;
	u16data = (u16)(Pms.PM2_5_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	/* 发送sht3x的温度数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_PMS;
	p.Data[3] = CAN_PM10;
	u16data = (u16)(Pms.PM10_Vol);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_PM2_5Shield;
	u16data = (u16)(Pms.shieldPM2_5Val);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[3] = CAN_PM10Shield;
	u16data = (u16)(Pms.shieldPM10Val);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_AQI;
	p.Data[4] = Pms.AQI;
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[3] = CAN_MODE;
	p.Data[4] = Pms.mode;
	xQueueSend(xQueue_canTx, &p, 30);
	
}

