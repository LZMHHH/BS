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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "protocol.h"




	
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
char Protocol_Encode(char* ProtocolString, const char *pSrc,u32 pnum, u8 pSite)
{
   	 
	 u8 numS[4];   //pnum���ַ���
	 u32 num;
	
	 num = pnum;
	 
		memset(numS, 0x00, sizeof(numS));  
		memset(ProtocolString, 0x00, DEBUG1_TX_BSIZE);  
	
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
char Protocol_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite)
{
   	 
	 char numS[10];   //pnum���ַ���
	 
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
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}
/*����ң�ؿ�������*/
void sendRmotorData(MCU_ID mcu_id,u8 kind,u8 *data, u8 len,TickType_t xTicksToWait)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REMOTOR;
	p.mcuID = mcu_id;
	p.dataLen = len + 3; 
	p.data[0] = enDATA;
	p.data[1] = kind;
	memcpy(p.data+2, data, len);  /* �ر����⣬���ֽ���ǰ */
	xQueueSend(xQueue_uart1Tx, &p, xTicksToWait);
}


/******************** ���벿�� ********************/

/*���Դ��ڽ���*/
void msgAnalyze(msg_t *p)
{
	/*  */
	DataHeadFind(p,MSG_HEAD);
	
	if(p->mcuID == enIDCAR)
	{
		if(p->msgID == DOWN_REMOTOR)
		{
			if(p->data[0] == enDATA)
			{
				switch(p->data[1])
				{
					case KIND_MOVE:
								Car.speedX = (float)((*(p->data+5) <<24)|(*(p->data+4) <<16)|(*(p->data+3) <<8)|*(p->data+2));
								Car.speedY = (float)((*(p->data+9) <<24)|(*(p->data+8) <<16)|(*(p->data+7) <<8)|*(p->data+6));
								Car.speedZ = (float)((*(p->data+13)<<24)|(*(p->data+12)<<16)|(*(p->data+11)<<8)|*(p->data+10));
								CarTickCount = xTaskGetTickCount();
								break;
				}
			}
		}
	}
}









