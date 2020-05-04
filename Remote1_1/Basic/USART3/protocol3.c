/**
  ******************************************************************************
  * @file    protocol3.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "protocol3.h"




	
	/**   
  * @brief  ����
  * @param  
  * @retval ������ͬ�ĵ�һλλ��
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
  * @brief    ֡����
* @param      pDst:ֻ�������ַ�
  * @retval 
  * @explain  $U,AP+12345#  ��  5λ����
  */	
long int Protocol_DecodeInt(const char *pSrc, const char *pDst)
{
	int      site;
	
	long int pI = 0;
	
	char     pStr[10] = {0};
		
	site = StringFind((const char *)pSrc, (const char *)pDst);

	memcpy(pStr,pSrc + site + 3,5);     //ע����ֵ��λ��
	 if(*(pSrc + site + 2) == '+')
		 pI = atof(pStr);
	 else
		 pI = -atof(pStr);
	 
	 return pI;
}

/**   
  * @brief    ֡����  ���� 3 
* @param      ProtocolString:���������� �� pSrc:  ����ַ��ı�ͷ��  pnum: ���֡�  pSite: pSrc�ַ��ĸ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  $A,R,AP+12345#  �� 4�ֽ�
  */	
char Protocol3_Encode(char* ProtocolString, const char *pSrc,u32 pnum, u8 pSite)
{
   	 
	 u8 numS[4];   //pnum���ַ���
	 u32 num;
	
	 num = pnum;
	 
		memset(numS, 0x00, sizeof(numS));  
		memset(ProtocolString, 0x00, DEBUG3_TX_BSIZE);  
	
		numS[0] = (num>>24)&0xff;
		
		/* �����ַ� */
		memcpy(ProtocolString,pSrc,pSite);
    
    return 0;		
}

/**   
  * @brief    ֡����  ���� 3 
  * @param      ProtocolString:���������� �� pSrc:  ����ַ��ı�ͷ��  pnum: ���֡�  pSite: pSrc�ַ��ĸ���
  * @retval   ���� 1 ֤�������Ѿ�������
  * @explain  $A,R,AP+12345#  ��  5λ����
  */	
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite)
{
   	 
	 char numS[10];   //pnum���ַ���
	 
		memset(numS, 0x00, sizeof(numS));  
		memset(ProtocolString, 0x00, DEBUG3_TX_BSIZE);  
	
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
  * @brief  ָ��ƫ��
  * @param  msg����Ҫ�������Ϣ
  * @retval 0���޴���1���Ҳ���
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
	��������ͨѶ
**********************************************************/

/******************** ���벿�� ********************/
/*��������*/
void sendCmd(downmsgID_e msg_id,u8 cmd, u8 data,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = msg_id;
	p.mcuID = enIDRemote;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = cmd;
	p.data[2] = data;
	xQueueSend(xQueue_uart3Tx, &p, xTicksToWait);
}
/*��������*/
void sendData(downmsgID_e msg_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = msg_id;
	p.mcuID = enIDRemote;
	p.dataLen = len + 2; 
	p.data[0] = enDATA;
	p.data[1] = kind;
	memcpy(p.data+2, data, len);  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_uart3Tx, &p, xTicksToWait);
}
/*����ң������*/
void sendRmotorCmd(MCU_ID mcu_id,u8 cmd, u8 data,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REMOTOR;
	p.mcuID = mcu_id;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = cmd;
	p.data[2] = data;
	xQueueSend(xQueue_uart3Tx, &p, xTicksToWait);
}
/*����ң�ؿ�������*/
void sendRmotorData(MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REMOTOR;
	p.mcuID = mcu_id;
	p.dataLen = len + 2; 
	p.data[0] = enDATA;
	p.data[1] = kind;
	memcpy(p.data+2, data, len);  /* �ر����⣬���ֽ���ǰ,�ṹ��Ҫע�ⲻͬ���͵�λ�á�ע���ֽڶ������� */
	xQueueSend(xQueue_uart3Tx, &p, xTicksToWait);
}



/******************** ���벿�� ********************/

/*���Դ��ڽ���*/
void msgAnalyze(msg_t *p)
{
	int intdata;
	u8  u8data;
	float floatdata;
	u8 Page_Index_Last;
	/*  */
	DataHeadFind(p,MSG_HEAD);
	
	/* ����С�� */
	if(p->mcuID == enIDCar)
	{
		if(p->msgID == UP_DATA)
		{
			if(p->data[0] == enDATA)
			{
				Page_Index_Last = Car_uiconfigParam.Page_Index;
				switch(p->data[1])
				{
					case KIND_MOTOR:
								intdata = (int)((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2));
								if(myabs(intdata) < 8000) Motorpwm.pwmoutA = intdata;
								intdata = (int)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));
								if(myabs(intdata) < 8000) Motorpwm.pwmoutB = intdata;
								intdata = (int)((*(p->data+13)<<24)|(*(p->data+12)<<16)|(*(p->data+11)<<8)|*(p->data+10));
								if(myabs(intdata) < 8000) Motorpwm.pwmoutC = intdata;
								intdata = (int)((*(p->data+17)<<24)|(*(p->data+16)<<16)|(*(p->data+15)<<8)|*(p->data+14));
								if(myabs(intdata) < 8000) Motorpwm.pwmoutD = intdata;
								break;
					case KIND_ENCODER:
								intdata = (int)((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2));
								if(myabs(intdata) < 500) Encoder.motorA = intdata;
								intdata = (int)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));
								if(myabs(intdata) < 500) Encoder.motorB = intdata;
								intdata = (int)((*(p->data+13)<<24)|(*(p->data+12)<<16)|(*(p->data+11)<<8)|*(p->data+10));
								if(myabs(intdata) < 500) Encoder.motorC = intdata;
								intdata = (int)((*(p->data+17)<<24)|(*(p->data+16)<<16)|(*(p->data+15)<<8)|*(p->data+14));
								if(myabs(intdata) < 500) Encoder.motorD = intdata;
								break;
								
					case KIND_LED:
								carLEDA.mode = (u8)*(p->data+2);
								intdata = (int)((*(p->data+6) <<24)|(*(p->data+5) <<16)|(*(p->data+4) <<8)|*(p->data+3));
								if(myabs(intdata) < 1000) carLEDA.cycle = intdata;
								carFMQ.mode = (u8)*(p->data+7);
								intdata = (int)((*(p->data+11) <<24)|(*(p->data+10) <<16)|(*(p->data+9) <<8)|*(p->data+8));
								if(myabs(intdata) < 1000) carFMQ.cycle = intdata;
								break;
								
					case KIND_UI:
								Car_uiconfigParam.Step_Index      = *(p->data+3);
								u8data                            = *(p->data+4);
								if(u8data<Car_uiconfigParam.Page_Index_Limit && u8data >=0)
								Car_uiconfigParam.Page_Index = u8data;
								Car_uiconfigParam.Page_Index_Last = *(p->data+5);
								Car_uiconfigParam.Para_Index      = *(p->data+6);
								Car_uiconfigParam.Para_IfControl  = *(p->data+7);
								break;
				}
				if(Page_Index_Last != Car_uiconfigParam.Page_Index)
				{
					xEventGroupSetBits(Event_uart3SendData,EVENT_uart3OLEDCLEAR);		
				}
			}
		}
	}
	/* ���Ի��� */
	if(p->mcuID == enIDEnvironment)
	{
		if(p->msgID == UP_DATA)
		{
			if(p->data[0] == enDATA)
			{
				Page_Index_Last = Envi_uiconfigParam.Page_Index;
				switch(p->data[1])
				{
					case KIND_SHT3X:
								floatdata = (float)(((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2))/100.0);
								if(myabs(floatdata) < 500.0) Huimiture.temperature = floatdata;
								floatdata = (float)(((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6))/100.0);
								if(myabs(floatdata) < 500.0) Huimiture.huimidity = floatdata;
								break;
					case KIND_GY30:
								floatdata = (float)(((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2))/100.0);
								if(myabs(floatdata) < 10000.0) Light.BH_Voltage = floatdata;
								break;
					case KIND_PMS:
								floatdata = (float)(((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2))/100.0);
								if(myabs(floatdata) < 1000.0) Pms.PM2_5_Vol = floatdata;
								floatdata = (float)(((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6))/100.0);
								if(myabs(floatdata) < 1000.0) Pms.PM10_Vol = floatdata;
								break;
					case KIND_BME:
								floatdata = (float)(((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2))/100.0);
								if(myabs(floatdata) < 5000.0) Bme.pressure = floatdata;
								floatdata = (float)(((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6))/100.0);
								if(myabs(floatdata) < 1000.0) Bme.asl = floatdata;
								floatdata = (float)(((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2))/100.0);
								if(myabs(floatdata) < 1000.0) Bme.temperature = floatdata;
								floatdata = (float)(((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6))/100.0);
								if(myabs(floatdata) < 1000.0) Bme.humidity = floatdata;
								break;
					
				}
				if(Page_Index_Last != Envi_uiconfigParam.Page_Index)
				{
//					xEventGroupSetBits(Event_uart3SendData,EVENT_uart3OLEDCLEAR);		
				}
			}
		}
	}
}










