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

static void Para_Init(void);


void vTaskEnvironment( void * pvParameters )
{
	
	
	
	/* 初始化参数 */
	Para_Init();
	
	
	while(1)
	{
	
//		uart1SendSht3xData(30);
//		vTaskDelay( 10 );
//		uart1SendGy30Data(30);
//		vTaskDelay( 10 );
//		uart1SendPmsData(30);
//		vTaskDelay( 10 );
//		uart1SendBmeData(30);
		
		vTaskDelay( 200 );
	}
	
}


static void Para_Init(void)
{

}

/*发送数据*/
void uart1SendSht3xData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SHT3X;
	intdata   = (int)((Huimiture.temperature)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata)); 
	intdata   = (int)((Huimiture.huimidity)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	intdata   = (int)((Huimiture.temp_offset)*100);
	memcpy(p.data+10, &(intdata), sizeof(intdata)); 
	intdata   = (int)((Huimiture.huim_offset)*100);
	memcpy(p.data+14, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
	p.dataLen = 4*4 + 2; 
	p.data[1] = KIND_SHT3XCON;
	intdata   = (int)((Huimiture.tempAdd_shieldVal)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata)); 
	intdata   = (int)((Huimiture.tempRed_shieldVal)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	intdata   = (int)((Huimiture.huim_shieldVal)*100);
	memcpy(p.data+10, &(intdata), sizeof(intdata)); 
	memcpy(p.data+14, &(Huimiture.AddPwm), sizeof(Huimiture.AddPwm));
	memcpy(p.data+16, &(Huimiture.RedPwm), sizeof(Huimiture.RedPwm));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
	p.dataLen = 3 + 2; 
	p.data[1] = KIND_SHT3XMODE;
	memcpy(p.data+2, &(Huimiture.tempAdd_mode), sizeof(Huimiture.tempAdd_mode)); 
	memcpy(p.data+3, &(Huimiture.tempRed_mode), sizeof(Huimiture.tempRed_mode)); 
	memcpy(p.data+4, &(Huimiture.huim_mode), sizeof(Huimiture.huim_mode)); 
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
}
/*发送数据*/
void uart1SendHuimitureData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SHT3X;
	intdata   = (int)((Huimiture.temperature)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata)); 
	intdata   = (int)((Huimiture.huimidity)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);

}



void uart1SendGy30Data(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*3+1 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_GY30;
	intdata   = (int)((Light.BH_Voltage)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Light.shieldVal)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	intdata   = (int)((Light.a)*100);
	memcpy(p.data+10, &(intdata), sizeof(intdata));
	memcpy(p.data+12, &(Light.mode), sizeof(Light.mode));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
void uart1SendPmsData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 2*4+2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_PMS;
	memcpy(p.data+2, &(Pms.PM2_5_Vol), sizeof(Pms.PM2_5_Vol));
	memcpy(p.data+4, &(Pms.PM10_Vol), sizeof(Pms.PM10_Vol));
	memcpy(p.data+6, &(Pms.shieldPM2_5Val), sizeof(Pms.shieldPM2_5Val));
	memcpy(p.data+8, &(Pms.shieldPM10Val), sizeof(Pms.shieldPM10Val));
	memcpy(p.data+11, &(Pms.AQI), sizeof(Pms.AQI));
	memcpy(p.data+12, &(Pms.mode), sizeof(Pms.mode));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
void uart1SendBmeData(TickType_t xTicksToWait)
{
	int intdata;
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_BME;
	intdata   = (int)((Bme.pressure)*100);
	memcpy(p.data+2, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Bme.asl)*100);
	memcpy(p.data+6, &(intdata), sizeof(intdata));
	intdata   = (int)((Bme.temperature)*100);
	memcpy(p.data+10, &(intdata), sizeof(intdata));  /* 特别留意，低字节在前 */
	intdata   = (int)((Bme.humidity)*100);
	memcpy(p.data+14, &(intdata), sizeof(intdata));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}

void uart1SendClockData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*3+1 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_TIME;
	memcpy(p.data+2, &(ClockA.Second), sizeof(ClockA.Second));  
	memcpy(p.data+6, &(ClockA.Minute), sizeof(ClockA.Minute));
	memcpy(p.data+10, &(ClockA.Hour), sizeof(ClockA.Hour));
	memcpy(p.data+14, &(ClockA.num_save), sizeof(ClockA.num_save));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_DATE;
	memcpy(p.data+2, &(ClockA.Day), sizeof(ClockA.Day));  
	memcpy(p.data+6, &(ClockA.Week), sizeof(ClockA.Week));
	memcpy(p.data+10, &(ClockA.Month), sizeof(ClockA.Month));
	memcpy(p.data+14, &(ClockA.Year), sizeof(ClockA.Year));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}

void uart1SendSetClockData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*3+1 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SETTIME;
	memcpy(p.data+2, &(SetClock.Second), sizeof(SetClock.Second));  
	memcpy(p.data+6, &(SetClock.Minute), sizeof(SetClock.Minute));
	memcpy(p.data+10, &(SetClock.Hour), sizeof(SetClock.Hour));
	memcpy(p.data+14, &(SetClock.num_save), sizeof(SetClock.num_save));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
	p.dataLen = 4*4 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SETDATE;
	memcpy(p.data+2, &(SetClock.Day), sizeof(SetClock.Day));  
	memcpy(p.data+6, &(SetClock.Week), sizeof(SetClock.Week));
	memcpy(p.data+10, &(SetClock.Month), sizeof(SetClock.Month));
	memcpy(p.data+14, &(SetClock.Year), sizeof(SetClock.Year));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}

void uart1SendSmogData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_SMOG;
	memcpy(p.data+2, &(Smog.PriVal), sizeof(Smog.PriVal));  
	memcpy(p.data+6, &(Smog.ShieldVal), sizeof(Smog.ShieldVal));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
}

void uart1SendHydrogenData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_HYDROGEN;
	memcpy(p.data+2, &(Hydrogen.PriVal), sizeof(Hydrogen.PriVal));  
	memcpy(p.data+6, &(Hydrogen.ShieldVal), sizeof(Hydrogen.ShieldVal));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
	
}

void uart1SendCOData(TickType_t xTicksToWait)
{
	msg_t p;
	
	p.msg_head = MSG_HEAD;
	p.msgID = UP_DATA;
	p.mcuID = enIDEnvironment;
	p.dataLen = 4*2 + 2; 
	p.data[0] = enDATA;
	p.data[1] = KIND_CO;
	memcpy(p.data+2, &(CO.PriVal), sizeof(CO.PriVal));  
	memcpy(p.data+6, &(CO.ShieldVal), sizeof(CO.ShieldVal));
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}



