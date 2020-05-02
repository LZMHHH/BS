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
	公共部分通讯
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
	
	/* 小车 */
	if(p->mcuID == enIDCar)
	{
		if(p->msgID == DOWN_REMOTOR)
		{
			if(p->data[0] == enCMD)
			{
				switch(p->data[1])
				{
					case KIND_KEY:
									if(p->data[2] == NAME_KEYU) Key_PU.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYD) Key_PD.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYL) Key_PL.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYR) Key_PR.Key_RetVal = enKey_Click;
									if(p->data[2] == NAME_KEYM) Key_PM.Key_RetVal = enKey_Click;
									/* 触发一个上传keyack数据的事件  目的是回传更新数据*/
									xEventGroupSetBits(Event_SendData,EVENT_KEYACK);		
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
									if(myabs(intdata) < 3000) Car.speedZ = intdata;
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
									break;
						case KIND_UI:
									if(*(p->data+2) == true)
									{
										Main_uiconfigParam.Sync = true;
										
										Main_uiconfigParam.Step_Index      = *(p->data+3);
										Main_uiconfigParam.Page_Index      = *(p->data+4);
										Main_uiconfigParam.Page_Index_Last = *(p->data+5);
										Main_uiconfigParam.Para_Index      = *(p->data+6);
										Main_uiconfigParam.Para_IfControl  = *(p->data+7);
										
										Show_Para_Con(&Main_uiconfigParam);
										OLED_Fill(0,0,128,64,0);
									}
									/* 触发一个上传led数据的事件  目的是回传更新数据*/
									xEventGroupSetBits(Event_SendData,EVENT_LED);		
									break;
					}
				}
			}
		}
	}
}









