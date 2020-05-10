/**
  ******************************************************************************
  * @file    EnvironmentTask.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   普通环境数据采集
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "EnvironmentTask.h"

CLASS_Motor MotorA;
CLASS_Motor MotorB;

CLASS_Huimiture Huimiture;
CLASS_Gas       Smog;
CLASS_Gas       Hydrogen;
CLASS_Gas       CO;


static void Para_Init(void);
			 void UpGasData(void);
			 void canSendSht3xData(void);
			 void canSendGasData(void);
			 void TemperatureCon(void);
			 void HuimidityCon(void);
volatile TickType_t EnvTickCount; //用于上报数据的计时

void vTaskEnvironment( void * pvParameters )
{
	
	
	
	/* 初始化参数 */
	Para_Init();
	
	
	while(1)
	{
		
		SHT3x_Getdata(0x44,&Huimiture);
		UpGasData();
		
		TemperatureCon();
		HuimidityCon();
		
		if(xTaskGetTickCount() > (EnvTickCount+100))
		{
			canSendSht3xData();
			vTaskDelay( 10 );
			canSendGasData();
			EnvTickCount = xTaskGetTickCount();
		}
		if(EnvTickCount > xTaskGetTickCount())
		{
			EnvTickCount = xTaskGetTickCount();
		}
		
		vTaskDelay( 20 );
	}
	
}


static void Para_Init(void)
{
	EnvTickCount = xTaskGetTickCount();
	
	Huimiture.temp_offset = 0;
	Huimiture.huim_offset = 0;
	Huimiture.tempAdd_shieldVal = 10;
	Huimiture.tempRed_shieldVal = 35;
	Huimiture.huim_shieldVal    = 70;
	Huimiture.tempAdd_mode = enFre;
	Huimiture.tempRed_mode = enFre;
	Huimiture.huim_mode    = enFre;
	Huimiture.AddPwm       = 7200;
	Huimiture.RedPwm       = 7200;
	
	
	Smog.PriVal  = 0;
	Smog.ShieldVal = 2000;
	Hydrogen.PriVal  = 0;
	Hydrogen.ShieldVal = 2000;
	CO.PriVal  = 0;
	CO.ShieldVal = 2000;
	
	MotorA.name = enMotorA;
	MotorB.name = enMotorB;
	
	
	MotorA.pwmout     = 0;
	MotorB.pwmout     = 0;
	Set_Pwm(&MotorA);
	Set_Pwm(&MotorB);
	
//	digitalHi(Jsq.config.gpio_port,Jsq.config.gpio_pin);

}

void UpGasData(void)
{
	
	Smog.PriVal      = getAdcValue(ADC_GASA);
	Hydrogen.PriVal  = getAdcValue(ADC_GASB);
	CO.PriVal        = getAdcValue(ADC_GASC);
	
}

/* 控制 */
#define CloseHuimiture  MotorA.pwmout     = 0;
#define OpenHuimiture   MotorA.pwmout     = 7200;
#define CloseFan        MotorB.pwmout     = 0;
#define OpenFanAdd(a)   MotorB.pwmout     = -a;
#define OpenFanRed(a)   MotorB.pwmout     = a;
void TemperatureCon(void)
{
	/* 以下逻辑基于一个mode为enON时，另一个必为enOFF。 */
	if((Huimiture.tempAdd_mode == enOFF) && (Huimiture.tempRed_mode == enOFF))
	{
		CloseHuimiture;
		CloseFan;
	}
	else
	{
//		/* 防漏 */
//		CloseHuimiture;
//		CloseFan;
//		
		if(Huimiture.tempAdd_mode == enON)
		{
			OpenHuimiture;
			OpenFanAdd(Huimiture.AddPwm);
		}
		if(Huimiture.tempRed_mode == enON)
		{
			OpenHuimiture;
			OpenFanAdd(Huimiture.RedPwm);
		}
		/* 以下逻辑基于 tempAdd_shieldVal <= tempRed_shieldVal*/
		if((Huimiture.tempAdd_mode == enFre) || (Huimiture.tempRed_mode == enFre))
		{
			if(Huimiture.temperature <  Huimiture.tempAdd_shieldVal)
			{
				OpenHuimiture;
				OpenFanAdd(Huimiture.AddPwm);
			}
			else
			{
				if(Huimiture.temperature >  Huimiture.tempRed_shieldVal)
				{
					OpenHuimiture;
					OpenFanRed(Huimiture.RedPwm);				MotorB.pwmout     = 7200;
				}
				else
				{
					CloseHuimiture;
					CloseFan;
				}
			}
		}
	}
	
	Set_Pwm(&MotorA);
	Set_Pwm(&MotorB);	
}

void HuimidityCon(void)
{
	switch(Huimiture.huim_mode)
	{
		case enOFF:
			 digitalLo(Jsq.config.gpio_port,Jsq.config.gpio_pin);
			 break;
		case enON:
			 digitalHi(Jsq.config.gpio_port,Jsq.config.gpio_pin);
			 break;
		case enFre:
			 if(Huimiture.huimidity < Huimiture.huim_shieldVal)
			 {
				 digitalHi(Jsq.config.gpio_port,Jsq.config.gpio_pin);
			 }
			 else
			 {
				 digitalLo(Jsq.config.gpio_port,Jsq.config.gpio_pin);
			 }
			 break;
	}
}


/* 通讯 */
void canSendSht3xData(void)
{
	int intdata;
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
	p.Data[2] = CAN_SHTX;
	p.Data[3] = CAN_Temperature;
	intdata = (int)((Huimiture.temperature)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_TempAddShield;
	intdata = (int)((Huimiture.tempAdd_shieldVal)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_TempRedShield;
	intdata = (int)((Huimiture.tempRed_shieldVal)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_TempAddMode;
	p.Data[4] = Huimiture.tempAdd_mode;
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_TempRedMode;
	p.Data[4] = Huimiture.tempRed_mode;
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_TempOffset;
	intdata = (int)((Huimiture.temp_offset)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_TempAddPwm;
	u16data = (u16)(Huimiture.AddPwm);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	/* 发送sht3x的湿度数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_SHTX;
	p.Data[3] = CAN_Humidity;
	intdata = (int)((Huimiture.huimidity)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_HuimShield;
	intdata = (int)((Huimiture.huim_shieldVal)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_HuimMode;
	p.Data[4] = Huimiture.huim_mode;
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_HuimOffset;
	intdata = (int)((Huimiture.huim_offset)*100);
	memcpy(p.Data+4, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_TempRedPwm;
	u16data = (u16)(Huimiture.AddPwm);
	memcpy(p.Data+4, &(u16data), sizeof(u16data));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
}

void canSendGasData(void)
{
	CanTxMsg p;
	
	/* 发送数据 */
	p.StdId = CAN_EVNID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDEnvironment;   
    p.Data[1] = enDATA;
	p.Data[2] = CAN_MQ2;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(Smog.PriVal), sizeof(Smog.PriVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);	
	p.Data[3] = CAN_Shield;
	memcpy(p.Data+4, &(Smog.ShieldVal), sizeof(Smog.ShieldVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[2] = CAN_MQ8;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(Hydrogen.PriVal), sizeof(Hydrogen.PriVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	vTaskDelay( 5 );
	
	p.Data[3] = CAN_Shield;
	memcpy(p.Data+4, &(Hydrogen.ShieldVal), sizeof(Hydrogen.ShieldVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	
	p.Data[2] = CAN_MQ7;
	p.Data[3] = CAN_PriAD;
	memcpy(p.Data+4, &(CO.PriVal), sizeof(CO.PriVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
	p.Data[3] = CAN_Shield;
	memcpy(p.Data+4, &(CO.ShieldVal), sizeof(CO.ShieldVal));  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_canTx, &p, 30);
}
