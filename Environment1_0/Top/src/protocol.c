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

/******************** 解码部分 ********************/



/********************************************************** 
	can通讯
**********************************************************/



/******************** 解码部分 ********************/

/*来自串口解码*/
void canmsgAnalyze(CanRxMsg *p)
{
	u8 Page_Index_Last;
	
	/* LEDID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_LEDID))
	{
		if(*(p->Data) == enIDCar)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_LEDA:
						   switch(*(p->Data+3))
								{
									case CAN_LedMode:
												carLEDA.mode = (u8)(*(p->Data+4));
												break;
									case CAN_LedFre:
												carLEDA.cycle = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_FMQ:
						   switch(*(p->Data+3))
								{
									case CAN_LedMode:
												carFMQ.mode = (u8)(*(p->Data+4));
												break;
									case CAN_LedFre:
												carFMQ.cycle = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
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
		if(*(p->Data) == enIDCar)
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
	/* UIID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_UIID))
	{
		Page_Index_Last = Car_uiconfigParam.Page_Index;
		
		if(*(p->Data) == enIDCar)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_CARUI:
						   switch(*(p->Data+3))
								{
									case CAN_UIStepIndex:
												Car_uiconfigParam.Step_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndex:
												Car_uiconfigParam.Page_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIPageIndexLast:
												Car_uiconfigParam.Page_Index_Last = (u8)(*(p->Data+4));
												break;
									case CAN_UIPareIndex:
												Car_uiconfigParam.Para_Index = (u8)(*(p->Data+4));
												break;
									case CAN_UIParaIfControl:
												Car_uiconfigParam.Para_IfControl = (u8)(*(p->Data+4));
												break;
								}
								break;
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
								}
								break;
					case CAN_ENVUI:
							 switch(*(p->Data+3))
								{
									case CAN_UIReq:
												xEventGroupSetBits(Event_canSendData,EVENT_canENVUI);		
												break;
								}
								break;
				}
			}
		}
		if(Page_Index_Last != Car_uiconfigParam.Page_Index)
		{
			xEventGroupSetBits(Event_canSendData,EVENT_canOLEDCLEAR);		
		}
	}
	/* 电机ID */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_MOTORID))
	{
		if(*(p->Data) == enIDCar)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_CARMOTOR:
						   switch(*(p->Data+3))
								{
									case CAN_P:
												MotorAllPID.p = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_I:
												MotorAllPID.i = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
									case CAN_D:
												MotorAllPID.d = (float)(((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4))/100.0);
												break;
								}
								break;
					case CAN_CARMOTORA:
						   switch(*(p->Data+3))
								{
									case CAN_PwmOut:
												Motorpwm.pwmoutA = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Encoder:
												Encoder.motorA = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_CARMOTORB:
						   switch(*(p->Data+3))
								{
									case CAN_PwmOut:
												Motorpwm.pwmoutB = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Encoder:
												Encoder.motorB = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_CARMOTORC:
						   switch(*(p->Data+3))
								{
									case CAN_PwmOut:
												Motorpwm.pwmoutC = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Encoder:
												Encoder.motorC = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
					case CAN_CARMOTORD:
						   switch(*(p->Data+3))
								{
									case CAN_PwmOut:
												Motorpwm.pwmoutD = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Encoder:
												Encoder.motorD = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
				}
			}
		}
	}
	
	/* 小车数据 */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_CARDATAID))
	{
		if(*(p->Data) == enIDCar)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_EMPTY:
						   switch(*(p->Data+3))
								{
									case CAN_MODE:
												Car.mode = (u8)*(p->Data+4);
												break;
									case CAN_MaxVal:
												Car.MaxPwm = (u16)((*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
				}
			}
		}
	}
	
	/* 避障 */
	if((p->IDE == CAN_ID_STD) && (p->StdId == CAN_BZID))
	{
		if(*(p->Data) == enIDCar)
		{
			if(*(p->Data+1) == enDATA)
			{
				
				switch(*(p->Data+2))
				{
					case CAN_HWBZ:
						   switch(*(p->Data+3))
								{
									case CAN_Empty:
												Hwbz_LD.status = (u8)*(p->Data+4);
												Hwbz_LU.status = (u8)*(p->Data+5);
												Hwbz_RU.status = (u8)*(p->Data+6);
												Hwbz_RD.status = (u8)*(p->Data+7);
												break;
								}
								break;
					case CAN_VL53L0X:
						   switch(*(p->Data+3))
								{
									case CAN_Val:
												Distance.xmm = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Offset:
												Distance.offset = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
									case CAN_Shield:
												Distance.shieldVal = (int)((*(p->Data+7) <<24)|(*(p->Data+6) <<16)|(*(p->Data+5) <<8)|*(p->Data+4));
												break;
								}
								break;
				}
			}
		}
	}
}


