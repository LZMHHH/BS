/**
  ******************************************************************************
  * @file    protocol.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "protocol.h"




	
	/**   
  * @brief  搜索
  * @param  
  * @retval 返回相同的第一位位置
  */
int StringFind(const char *pSrc, const char *pDst)  
{  
    int i, j;  
    for (i=0; pSrc[i]!='\0'; i++)  
    {  
        if(pSrc[i]!=pDst[0])  
            continue;         
        j = 0;  
        while(pDst[j]!='\0' && pSrc[i+j]!='\0')  
        {  
            j++;  
            if(pDst[j]!=pSrc[i+j])  
            break;  
        }  
        if(pDst[j]=='\0')  
            return i;  
    }  
    return -1;  
} 



/**   
  * @brief    帧解码
* @param      pDst:只能两个字符
  * @retval 
  * @explain  $U,AP+12345#  。  5位整数
  */	
long int Protocol_DecodeInt(const char *pSrc, const char *pDst)
{
	int      site;
	
	long int pI = 0;
	
	char     pStr[10] = {0};
		
	site = StringFind((const char *)pSrc, (const char *)pDst);

	memcpy(pStr,pSrc + site + 3,5);     //注意数值的位数
	 if(*(pSrc + site + 2) == '+')
		 pI = atof(pStr);
	 else
		 pI = -atof(pStr);
	 
	 return pI;
}

/**   
  * @brief    帧编码  串口 3 
* @param      ProtocolString:编码后的数据 。 pSrc:  五个字符的标头。  pnum: 数字。  pSite: pSrc字符的个数
  * @retval   返回 1 证明数据已经发出。
  * @explain  $A,R,AP+12345#  。 4字节
  */	
char Protocol_Encode(char* ProtocolString, const char *pSrc,u32 pnum, u8 pSite)
{
   	 
	 u8 numS[4];   //pnum的字符串
	 u32 num;
	
	 num = pnum;
	 
		memset(numS, 0x00, sizeof(numS));  
		memset(ProtocolString, 0x00, DEBUG1_TX_BSIZE);  
	
		numS[0] = (num>>24)&0xff;
		
		/* 拷贝字符 */
		memcpy(ProtocolString,pSrc,pSite);
    
    return 0;		
}

/**   
  * @brief    帧编码  串口 3 
* @param      ProtocolString:编码后的数据 。 pSrc:  五个字符的标头。  pnum: 数字。  pSite: pSrc字符的个数
  * @retval   返回 1 证明数据已经发出。
  * @explain  $A,R,AP+12345#  。  5位整数
  */	
char Protocol_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite)
{
   	 
	 char numS[10];   //pnum的字符串
	 
		memset(numS, 0x00, sizeof(numS));  
		memset(ProtocolString, 0x00, DEBUG1_TX_BSIZE);  
	
		if(pnum>0)
		{
			memcpy(ProtocolString,pSrc,pSite);
			memcpy(ProtocolString+pSite,"+",1);
		}
		else
		{
			memcpy(ProtocolString,pSrc,pSite);
			memcpy(ProtocolString+pSite,"-",1);
			pnum = -pnum;
		}
		sprintf(numS,"%ld",pnum);
		if(pnum < 100000 && pnum >9999)
		{
			memcpy(ProtocolString+pSite+1,numS,5);
			
		}
		if(pnum < 10000 && pnum >999)
		{
			memcpy(ProtocolString+pSite+1,"0",1);
			memcpy(ProtocolString+pSite+2,numS,4);
		}
		if(pnum < 1000 && pnum >99)
		{
			memcpy(ProtocolString+pSite+1,"00",2);
			memcpy(ProtocolString+pSite+3,numS,3);
		}
		if(pnum < 100 && pnum >9)
		{
			memcpy(ProtocolString+pSite+1,"000",3);
			memcpy(ProtocolString+pSite+4,numS,2);
		}
		if(pnum < 10)
		{
			memcpy(ProtocolString+pSite+1,"0000",4);
			memcpy(ProtocolString+pSite+5,numS,1);
		}
		*(ProtocolString+pSite+6)= '#';
    
    return 0;		
}

	/**   
  * @brief  指针偏移
  * @param  msg：需要处理的消息
  * @retval 0：无错误，1：找不到
  */
u8 DataHeadFind(msg_t *msg,u8 Dst)  
{  
    int i;  
		u8 *msgb;
		msgb = (u8 *)(msg);
	
    for (i=0; i < DEBUG1_RX_BSIZE; i++)  
    {  
        if(msgb[i] != Dst)  
            continue;         
        else
				{
					msg = (msg_t *)(msgb+i);
					return 0;  
				}
						
    }  
		
    return 1;  
} 

/********************************************************** 
	串口通讯
**********************************************************/

/******************** 编码部分 ********************/
/*发送命令*/
void sendCmd(upmsgID_e msg_id,MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = msg_id;
	p.mcuID = mcu_id;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = cmd;
	p.data[2] = data;
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
/*发送数据*/
void sendData(upmsgID_e msg_id,MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = msg_id;
	p.mcuID = mcu_id;
	p.dataLen = len + 2; 
	p.data[0] = enDATA;
	p.data[1] = kind;
	memcpy(p.data+2, data, len);  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
/*发送遥控命令*/
void sendRmotorCmd(MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REMOTOR;
	p.mcuID = mcu_id;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = cmd;
	p.data[2] = data;
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
/*发送遥控控制数据*/
void sendRmotorData(MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REMOTOR;
	p.mcuID = mcu_id;
	p.dataLen = len + 2; 
	p.data[0] = enDATA;
	p.data[1] = kind;
	memcpy(p.data+2, data, len);  /* 特别留意，低字节在前 */
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}


/******************** 解码部分 ********************/

/*来自串口解码*/
void msgAnalyze(msg_t *p)
{
	int intdata;
	
	/*  */
	DataHeadFind(p,MSG_HEAD);
	
	/* 来自遥控 */
	if(p->mcuID == enIDRemote)
	{
		if(p->msgID == DOWN_REMOTOR)
		{
			if(p->data[0] == enCMD)
			{
				switch(p->data[1])
				{
					case KIND_CARKEY:
									if(p->data[2] == NAME_KEYU) Key_PU.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYD) Key_PD.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYL) Key_PL.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYR) Key_PR.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYM) Key_PM.Key_RetVal = enKey_Click;
									break;
					case KIND_ENVKEY:
									if(p->data[2] == NAME_KEYU) canSendKeyClickData(CAN_KEYU,30);
									if(p->data[2] == NAME_KEYD) canSendKeyClickData(CAN_KEYD,30);
									if(p->data[2] == NAME_KEYL) canSendKeyClickData(CAN_KEYL,30);
									if(p->data[2] == NAME_KEYR) canSendKeyClickData(CAN_KEYR,30);
									if(p->data[2] == NAME_KEYM) canSendKeyClickData(CAN_KEYM,30);
									break;
					case KIND_UIREQ:
									if(p->data[2] == UIREQ_CAR) 
									{
										xEventGroupSetBits(Event_SendData,EVENT_uart1CARUI);	
									}		
									if(p->data[2] == UIREQ_ENVIRONMENT) 
									{
										xEventGroupSetBits(Event_SendData,EVENT_uart1ENVUI);	
									}		
									break;
				}
			}
			else
			{
				if(p->data[0] == enDATA)
				{
					switch(p->data[1])
					{
						case KIND_MOVE:
									intdata = (int)((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2));
									if(myabs(intdata) < 3000) Car.speedX = intdata;
									intdata = (int)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));
									if(myabs(intdata) < 3000) Car.speedY = intdata;
									intdata = (int)((*(p->data+13)<<24)|(*(p->data+12)<<16)|(*(p->data+11)<<8)|*(p->data+10));
									if(myabs(intdata) < 3000) Car.speedZ = intdata;
									CarTickCount = xTaskGetTickCount();
									break;
						case KIND_LED:
									switch((u8)(*(p->data+2)))
									{
										case NAME_LEDA:
													LedA.flag_mode = (u8)(*(p->data+3));
													LedA.cycle = (int)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));						
													break;
										case NAME_FMQ:
													Fmq.flag_mode = (u8)(*(p->data+3));
													Fmq.cycle = (int)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));						
													break;
									}
					}
				}
			}
		}
		if(p->msgID == DOWN_REQ)
		{
			if(p->data[0] == enCMD)
			{
				switch(p->data[1])
				{
					case KIND_UIPAGEREQ:
									switch(p->data[2])
									{
										case KIND_CARUIPAGE0:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1CARPAGE0);		
														break;
										case KIND_CARUIPAGE1:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1CARPAGE1);		
														break;
										case KIND_CARUIPAGE2:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1CARPAGE2);		
														break;
										case KIND_CARUIPAGE3:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1CARPAGE3);		
														break;
										case KIND_ENVUIPAGE0:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE0);		
														break;
										case KIND_ENVUIPAGE1:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE1);		
														break;
										case KIND_ENVUIPAGE2:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE2);		
														break;
										case KIND_ENVUIPAGE3:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE3);		
														break;
										case KIND_ENVUIPAGE4:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE4);		
														break;
										case KIND_ENVUIPAGE5:
														/* 触发一个回传据的事件  目的是回传更新数据*/
														xEventGroupSetBits(Event_SendData,EVENT_uart1ENVPAGE5);		
														break;
									}
									break;
					
				}
			}
		}
	}
}


/********************************************************** 
	can通讯
**********************************************************/



/******************** 解码部分 ********************/

/*来自can解码*/
void canmsgAnalyze(CanRxMsg *p)
{
	u8 Page_Index_Last;
	
	/* 环境ID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_EVNID))
	{
		if(*(p->Data) == enIDEnvironment)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_SHTX:
						   switch(*(p->Data+3))
								{
									case CAN_Temperature:
												Huimiture.temperature = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_TempAddShield:
												Huimiture.tempAdd_shieldVal   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_TempRedShield:
												Huimiture.tempRed_shieldVal   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_TempOffset:
												Huimiture.temp_offset   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_TempAddMode:
												Huimiture.tempAdd_mode = (u8)(*(p->Data+4));
												break;
									case CAN_TempRedMode:
												Huimiture.tempRed_mode = (u8)(*(p->Data+4));
												break;
									case CAN_TempAddPwm:
												Huimiture.AddPwm = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
									case CAN_Humidity:
												Huimiture.huimidity   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_HuimShield:
												Huimiture.huim_shieldVal   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_HuimOffset:
												Huimiture.huim_offset   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_HuimMode:
												Huimiture.huim_mode = (u8)(*(p->Data+4));
												break;
									case CAN_TempRedPwm:
												Huimiture.RedPwm = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
								}
								break;
					case CAN_GY30:
						   switch(*(p->Data+3))
								{
									case CAN_Light:
												Light.BH_Voltage = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_Shield:
												Light.shieldVal   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_FactorA:
												Light.a   = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_MODE:
												Light.mode = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_PMS:
						   switch(*(p->Data+3))
								{
									case CAN_PM2_5:
												Pms.PM2_5_Vol = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
									case CAN_PM10:
												Pms.PM10_Vol = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
									case CAN_PM2_5Shield:
												Pms.shieldPM2_5Val = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
									case CAN_PM10Shield:
												Pms.shieldPM10Val = (u16)(((*(p->Data+5) <<8)|*(p->Data+4)));
												break;
									case CAN_AQI:
												Pms.AQI = (u8)(*(p->Data+4));
												break;
									case CAN_MODE:
												Pms.mode = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_BME:
						   switch(*(p->Data+3))
								{
									case CAN_Pressure:
												Bme.pressure = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_Hight:
												Bme.asl = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_Temperature:
												Bme.temperature = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_Humidity:
												Bme.humidity = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
								}
								break;
					
				}
			}
		}
	}
	/* LEDID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_LEDID))
	{
		if(*(p->Data) == enIDEnvironment)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_LEDA:
						   switch(*(p->Data+3))
								{
									case CAN_LedMode:
												envLEDA.mode = (u8)(*(p->Data+4));
												break;
									case CAN_LedFre:
												envLEDA.cycle = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_LEDB:
						   switch(*(p->Data+3))
								{
									case CAN_LedMode:
												envLEDB.mode = (u8)(*(p->Data+4));
												break;
									case CAN_LedFre:
												envLEDB.cycle = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_FMQ:
						   switch(*(p->Data+3))
								{
									case CAN_LedMode:
												envFMQ.mode = (u8)(*(p->Data+4));
												break;
									case CAN_LedFre:
												envFMQ.cycle = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					
				}
			}
		}
	}
	/* KEYID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_KEYID))
	{
		if(*(p->Data) == enIDEnvironment)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_KEYU:
						   switch(*(p->Data+3))
								{
									case CAN_KeyRet:
												Key_PU.Key_RetVal = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_KEYD:
						   switch(*(p->Data+3))
								{
									case CAN_KeyRet:
												Key_PD.Key_RetVal = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_KEYL:
						   switch(*(p->Data+3))
								{
									case CAN_KeyRet:
												Key_PL.Key_RetVal = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_KEYR:
						   switch(*(p->Data+3))
								{
									case CAN_KeyRet:
												Key_PR.Key_RetVal = (u8)(*(p->Data+4));
												break;
								}
								break;
					case CAN_KEYM:
						   switch(*(p->Data+3))
								{
									case CAN_KeyRet:
												Key_PM.Key_RetVal = (u8)(*(p->Data+4));
												break;
								}
								break;
					
				}
			}
		}
	}
	/* TIMEID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_TIMEID))
	{
		if(*(p->Data) == enIDEnvironment)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_DS3231:
						   switch(*(p->Data+3))
								{
									case CAN_Second:
												ClockA.Second = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Minute:
												ClockA.Minute = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Hour:
												ClockA.Hour = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Week:
												ClockA.Week = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Day:
												ClockA.Day = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Month:
												ClockA.Month = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Year:
												ClockA.Year = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Temperature:
												ClockA.Temp = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_ClockMode:
												ClockA.Switch = (char)(*(p->Data+4));
												break;
									case CAN_SaveNum:
												ClockA.num_save = (u16)((*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_SETCLOCK:
						   switch(*(p->Data+3))
								{
									case CAN_Second:
												SetClock.Second = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Minute:
												SetClock.Minute = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Hour:
												SetClock.Hour = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Week:
												SetClock.Week = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Day:
												SetClock.Day = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Month:
												SetClock.Month = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Year:
												SetClock.Year = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Temperature:
												SetClock.Temp = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_ClockMode:
												SetClock.Switch = (char)(*(p->Data+4));
												break;
									case CAN_SaveNum:
												SetClock.num_save = (u16)((*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
				}
			}
		}
	}
	/* UIID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_UIID))
	{
		if(*(p->Data) == enIDEnvironment)
		{
			if(*(p->Data+1) == enDATA)
			{
				Page_Index_Last = Envi_uiconfigParam.Page_Index;
				switch(*(p->Data+2))
				{
					case CAN_CARUI:
						   switch(*(p->Data+3))
								{
									case CAN_UIStepIndex:
												Main_uiconfigParam.Step_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndex:
												Main_uiconfigParam.Page_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndexLast:
												Main_uiconfigParam.Page_Index_Last = (u8)(*(p->Data+4));
												break;
									case CAN_UIPareIndex:
												Main_uiconfigParam.Para_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIParaIfControl:
												Main_uiconfigParam.Para_IfControl = (u8)(*(p->Data+4));
												break;
								}
								break;
						case CAN_ENVUI:
						   switch(*(p->Data+3))
								{
									case CAN_UIStepIndex:
												Envi_uiconfigParam.Step_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndex:
												Envi_uiconfigParam.Page_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndexLast:
												Envi_uiconfigParam.Page_Index_Last = (u8)(*(p->Data+4));
												break;
									case CAN_UIPareIndex:
												Envi_uiconfigParam.Para_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIParaIfControl:
												Envi_uiconfigParam.Para_IfControl = (u8)(*(p->Data+4));
												break;
								}
								break;
				}
				if(Page_Index_Last != Envi_uiconfigParam.Page_Index)
				{
					xEventGroupSetBits(Event_canSendData,EVENT_canOLEDCLEAR);		
				}
			}
			if(*(p->Data+1) == enCMD)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_CARUI:
							 switch(*(p->Data+3))
								{
									case CAN_UIReq:
												xEventGroupSetBits(Event_canSendData,EVENT_canCARUI);		
												break;
									case CAN_UIPageReq:
												switch(*(p->Data+4))
												{
													case 0:
															 xEventGroupSetBits(Event_canSendData,EVENT_canCARPAGE0);		
															 break;
													case 1:
															 xEventGroupSetBits(Event_canSendData,EVENT_canCARPAGE1);		
															 break;
													case 2:
															 xEventGroupSetBits(Event_canSendData,EVENT_canCARPAGE2);		
															 break;
													case 3:
															 xEventGroupSetBits(Event_canSendData,EVENT_canCARPAGE3);		
															 break;
												}
												break;
								}
								break;
					}
			}
		}
	}
}


