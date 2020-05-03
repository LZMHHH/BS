/**
  ******************************************************************************
  * @file    bsp_DS3231.c
  * @author  fire
  * @version V1.1
  * @date    2020-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
	*
	*
  ******************************************************************************
  */


#include "bsp_DS3231.h" 



//�ӿ�
#define DS3231delay_us DwtDelay_uS
#define DS3231delay_ms DwtDelay_mS



#define DS3231_write 0
#define DS3231_read  1

/*��������ACK*/
void DS3231_IIC_ACK(void)
{ 
		DS3231_SDA_OUT();
		DS3231_IIC_SCL=0;
		DS3231delay_us(2);  
		DS3231_IIC_SDA=0;
		DS3231delay_us(2);
		DS3231_IIC_SCL=1;
		DS3231delay_us(2);
		DS3231_IIC_SCL=0;
		DS3231delay_us(1); 
}

 /*����������ACK*/
void DS3231_IIC_NACK(void)
{  
	DS3231_SDA_OUT();  
	DS3231_IIC_SCL=0;  
	DS3231delay_us(2);   
	DS3231_IIC_SDA=1;  
	DS3231delay_us(2);        
	DS3231_IIC_SCL=1;  
	DS3231delay_us(2);                     
	DS3231_IIC_SCL=0;                       
	DS3231delay_us(1);    
}

 
 
/*�����ȴ��ӻ���ACK
 *���أ�1 ����0������
 */
u8 DS3231_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	DS3231_SDA_OUT();    
	DS3231_IIC_SDA=1;//8λ��������ͷ������ߣ�׼������Ӧ��λ     
	DS3231delay_us(1);    
	DS3231_IIC_SCL=0;    
	DS3231delay_us(1);     
	DS3231_SDA_IN();    
	DS3231delay_us(1);     
	while(DS3231_READ_SDA)//�ȴ�DS3231Ӧ��    
	{	
			t--;
			DS3231delay_us(1); 	
			if(t==0)	
			{	  
				DS3231_IIC_SCL=0;	  
				return 1;	
			}	
			DS3231delay_us(1);     
	}    
	DS3231delay_us(1);          
	DS3231_IIC_SCL=1;    
	DS3231delay_us(1);    
	DS3231_IIC_SCL=0;                 
	DS3231delay_us(1);        
	return 0;	
}



/******************************************************************
 *����:����I2C����,������I2C��ʼ����.  
********************************************************************/
void DS3231_IIC_Start(void)
{  
	DS3231_SDA_OUT();  
	DS3231_IIC_SDA=1;  
	DS3231_IIC_SCL=1;  
	DS3231delay_us(4);	  
	DS3231_IIC_SDA=0;  
	DS3231delay_us(4);   
	DS3231_IIC_SCL=0;
}


/******************************************************************
*����:����I2C����,������I2C��������.  
********************************************************************/
void DS3231_IIC_Stop(void)
{	
	DS3231_SDA_OUT();	
	DS3231_IIC_SCL=0;	
	DS3231_IIC_SDA=0;  	
	DS3231delay_us(4);		
	DS3231_IIC_SCL=1;	
	DS3231delay_us(4);	
	DS3231_IIC_SDA=1;	
	DS3231delay_us(4);
}


/******************************************************************
*�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void DS3231_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	DS3231_SDA_OUT();	
	DS3231_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ	
	{		
		if(byte&0x80) 
			DS3231_IIC_SDA=1;//�жϷ���λ		
		else DS3231_IIC_SDA=0; 		
		byte<<=1;		
		DS3231delay_us(2); 		
		DS3231_IIC_SCL=1;		
		DS3231delay_us(2);		
		DS3231_IIC_SCL=0;		
		DS3231delay_us(2);	
	}
}


/******************************************************************
* �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
u8 DS3231_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	DS3231_SDA_IN();//��������Ϊ���뷽ʽ  
	DS3231delay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		DS3231_IIC_SCL=0;//��ʱ����Ϊ�ͣ�׼����������λ	
		DS3231delay_us(2);               	
		DS3231_IIC_SCL=1;//��ʱ����Ϊ��ʹ��������������Ч                	
		retc=retc<<1;	
		if(DS3231_READ_SDA) 
			retc |=1;//������λ,���յ�����λ����retc�� 	
		DS3231delay_us(1);  
	}  
	DS3231_IIC_SCL=0;      
	return(retc);
}

/********************** ��Ϊ iic����ΪDS3231 ****************************/

/******************************************************************
* BCDת��ΪByte         
����: BCDת��ΪByte
********************************************************************/    
u8 BCDtoHEX ( u8 val )  
{
    u8 i;
    i = val & 0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;

    return i;
}

/******************************************************************
* B��ת��ΪBCD��         
����: B��ת��ΪBCD��
********************************************************************/    
u8 B_BCD ( u8 val )  
{
    u8 i, j, k;

    i = val / 10;
    j = val % 10;
    k = j + ( i << 4 );
    return k;
}

/****************************************************/
/***********��һ���ֽ�д��DS3231ָ���ĵ�ַ***********/
u8 DS3231_IIC_Write ( u8 reg_addr, u8 bytedata )
{
    DS3231_IIC_Start();
    DS3231_IIC_SendByte ( DS3231Addr );
		DS3231_IIC_wait_ACK();	
    DS3231_IIC_SendByte ( reg_addr );
		DS3231_IIC_wait_ACK();	
    DS3231_IIC_SendByte ( bytedata );
		DS3231_IIC_wait_ACK();	
    DS3231_IIC_Stop();
    return 1;
}

/****************************************************/
/************��DS3231��ǰ��ַ��һ���ֽ�************/
u8 DS3231_IIC_Read(void)
{
    u8 read_data;

    DS3231_IIC_Start();
    DS3231_IIC_SendByte ( DS3231Addr + 1 );
		DS3231_IIC_wait_ACK();	
    read_data = DS3231_IIC_RcvByte();
    DS3231_IIC_Stop();
    return read_data;
}

/****************************************************/
/************��DS3231ָ����ַ��һ���ֽ�************/
u8 DS3231_I2C_Read_Add ( u8 reg_addr )
{
    DS3231_IIC_Start();
    DS3231_IIC_SendByte ( DS3231Addr );
		DS3231_IIC_wait_ACK();
    DS3231_IIC_SendByte ( reg_addr );
		DS3231_IIC_wait_ACK();
    return ( DS3231_IIC_Read() );
}

/************************* DS3213�㷨 ********************************************/
/*��������*/
void DS3231_Readtime(CLASS_Clock* clock);


//���ݲ��գ�Zeller����ʽ�������ڼ�
void autoweek()
{
		CLASS_Clock clock;
    DS3231_Readtime(&clock);
    if ( clock.Month == 1 || clock.Month == 2 )
    {
        clock.Month += 12;
        if ( clock.Year > 0 )
            clock.Year --;
        else
            clock.Year = 4;
    }
    clock.Week = ( 1 + ( ( clock.Day + 2 * clock.Month + 3 * ( clock.Month + 1 ) / 5 + clock.Year + clock.Year / 4 ) % 7 ) );
    DS3231_IIC_Write ( DS3231_WEEK, clock.Week );
}

/************************* API ********************************************/

/***************************************************/
/*********************��ȡʱ��**********************/
void DS3231_Readtime(CLASS_Clock* clock)
{
    u8 tempHbyte;
		u8 tempLbyte;
	
    clock->Second = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_SEC ) );//��
    clock->Minute = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_MIN ) );//��
    clock->Hour   = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_HOUR ) & 0x3f);//ʱ
    clock->Week   = DS3231_I2C_Read_Add ( DS3231_WEEK );//����
    clock->Day    = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_DATE ) );//��
    clock->Month  = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_MONTH ) );//��
    clock->Year   = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_YEAR ) )+2000;//��
		
		tempHbyte     = DS3231_I2C_Read_Add ( DS3231_TEMP_H );
		tempLbyte			= DS3231_I2C_Read_Add ( DS3231_TEMP_L );
		if(tempHbyte & 0x80) //check if -ve number
    {
       tempHbyte  ^= 0xff;  
       tempHbyte  += 0x1;
       clock->Temp = tempHbyte + ((tempLbyte >> 6) * 0.25);
       clock->Temp = clock->Temp * -1;
    }
    else
    {
       clock->Temp = tempHbyte + ((tempLbyte >> 6) * 0.25); 
    }
		

}

/***************************************************/
/****************�޸�ʱ��***************************/
void DS3231_SetTime ( CLASS_Clock* clock )
{
    int temp = 0;

    temp = B_BCD ( clock->Second );
    DS3231_IIC_Write ( DS3231_SEC, temp ); //�޸���
    temp = B_BCD ( clock->Minute );
    DS3231_IIC_Write ( DS3231_MIN, temp ); //�޸ķ�
    temp = B_BCD ( clock->Hour ) & 0xbf;//Make sure clock is still 24 Hour
    DS3231_IIC_Write ( DS3231_HOUR, temp ); //�޸�ʱ
    temp = B_BCD ( clock->Day );
    DS3231_IIC_Write ( DS3231_DATE, temp ); //�޸���
		temp = B_BCD ( clock->Week );
    DS3231_IIC_Write ( DS3231_WEEK, temp ); //�޸�����
    temp = B_BCD ( clock->Month );
    DS3231_IIC_Write ( DS3231_MONTH, temp ); //�޸���
    temp = B_BCD ( clock->Year - 2000);
    DS3231_IIC_Write ( DS3231_YEAR, temp ); //�޸���
}

//��ʼ��	    
void bsp_DS3231_Init(void)
{ 	
//	CLASS_Clock clock;
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	DS3231_I2C_GPIO_APBxClock_FUN(DS3231_I2C_CLK_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SCL_InitStructure.GPIO_Pin = DS3231_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(DS3231_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //��ʼ��GPIOX
	
	DS3231_I2C_GPIO_APBxClock_FUN(DS3231_I2C_SDA_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SDA_InitStructure.GPIO_Pin = DS3231_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(DS3231_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //��ʼ��GPIOX
	
	DS3231_IIC_SCL = 1;		
	DS3231_IIC_SDA = 1;
	
//	DS3231_IIC_Write ( DS3231_AL1DAY, 0x81 ); //A1M4��λ��ʱ����ƥ��ʱ������Ӧ
//	DS3231_IIC_Write ( DS3231_AL2DAY, 0x81 ); //A2M4��λ��ʱ��ƥ��ʱ������Ӧ
//	DS3231_IIC_Write ( DS3231_CONTROL, 0x04 ); //�ж���������1��2�ر�
	DS3231_IIC_Write ( DS3231_STATUS, 0x00 ); //32KHZ�����ֹ�����ӱ�־λ����
	
//	clock.Second = 2;
//	clock.Minute = 18;
//	clock.Hour = 17;
//	clock.Day = 18;
//	clock.Week = 6;
//	clock.Month = 4;
//	clock.Year = 2020;
//	DS3231_SetTime(&clock);

}

//�ۼӺ���
void SetTime_Add(CLASS_Clock *clock,SetT_Status timestatus,u8 add)  
{
	switch(timestatus)
	{
		case enSecond:
			if(add)
			{
			   clock->Second++;
				 if(clock->Second > 59) clock->Second=0;   //���60s
			}
			else 
			{
				if(clock->Second <= 0) clock->Second=60;  
				clock->Second--;
				
			}
		  break;
		case enMinute:
			if(add)
			{
			   clock->Minute++;
				 if(clock->Minute > 59) clock->Minute=0;   //���60min
			}
			else 
			{
				if(clock->Minute <= 0) clock->Minute=60;   
				clock->Minute--;
			}
		  break;
		case enHour:
			if(add)
			{
			   clock->Hour++;
				 if(clock->Hour > 23) clock->Hour=0;      //���24h
			}
			else 
			{
				if(clock->Hour <= 0) clock->Hour=24;      
				clock->Hour--;				
			}
		  break;
		case enDay:
			if(add)
			{
			   clock->Day++;
				 if(clock->Month==1||clock->Month==3||clock->Month==5||clock->Month==7||clock->Month==8||clock->Month==10||clock->Month==12)
				 {
					 if(clock->Day > 31) clock->Day=1;      //���31day
				 }
				 else 
					  if(clock->Day > 30) clock->Day=1;      //���30day
			}
			else 
			{
				clock->Day--;
				if(clock->Month==1||clock->Month==3||clock->Month==5||clock->Month==7||clock->Month==8||clock->Month==10||clock->Month==12)
				{
					if(clock->Day < 1) clock->Day=31;      //���31day
				}
				else 
					 if(clock->Day < 1) clock->Day=30;      //���30day
			}
		  break;
			
		case enWeek:
			if(add)
			{
			   clock->Week++;
				 if(clock->Week > 7) clock->Week=1;      //���7
			}
			else 
			{
				clock->Week--;
				if(clock->Week < 1) clock->Week=7;      
			}
		  break;
			
		case enMonth:
			if(add)
			{
			   clock->Month++;
				 if(clock->Month > 12) clock->Month=1;      \
			}
			else 
			{
				clock->Month--;
				if(clock->Month < 1) clock->Month=12;      
			}
		  break;
		case enYear:
			if(add)
			   clock->Year++;
			else clock->Year--;
		  break;
		default:break;
	}
}
