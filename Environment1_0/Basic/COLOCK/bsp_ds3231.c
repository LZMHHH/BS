/**
  ******************************************************************************
  * @file    bsp_DS3231.c
  * @author  fire
  * @version V1.1
  * @date    2020-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
	*
	*
  ******************************************************************************
  */


#include "bsp_DS3231.h" 



//接口
#define DS3231delay_us DwtDelay_uS
#define DS3231delay_ms DwtDelay_mS



#define DS3231_write 0
#define DS3231_read  1

/*主机发送ACK*/
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

 /*主机不发送ACK*/
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

 
 
/*主机等待从机的ACK
 *返回：1 错误，0，正常
 */
u8 DS3231_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	DS3231_SDA_OUT();    
	DS3231_IIC_SDA=1;//8位发送完后释放数据线，准备接收应答位     
	DS3231delay_us(1);    
	DS3231_IIC_SCL=0;    
	DS3231delay_us(1);     
	DS3231_SDA_IN();    
	DS3231delay_us(1);     
	while(DS3231_READ_SDA)//等待DS3231应答    
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
 *功能:启动I2C总线,即发送I2C起始条件.  
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
*功能:结束I2C总线,即发送I2C结束条件.  
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
*字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:将数据c发送出去,可以是地址,也可以是数据
********************************************************************/
void DS3231_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	DS3231_SDA_OUT();	
	DS3231_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//要传送的数据长度为8位	
	{		
		if(byte&0x80) 
			DS3231_IIC_SDA=1;//判断发送位		
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
* 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能: 用来接收从器件传来的数据  
********************************************************************/    
u8 DS3231_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	DS3231_SDA_IN();//置数据线为输入方式  
	DS3231delay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		DS3231_IIC_SCL=0;//置时钟线为低，准备接收数据位	
		DS3231delay_us(2);               	
		DS3231_IIC_SCL=1;//置时钟线为高使数据线上数据有效                	
		retc=retc<<1;	
		if(DS3231_READ_SDA) 
			retc |=1;//读数据位,接收的数据位放入retc中 	
		DS3231delay_us(1);  
	}  
	DS3231_IIC_SCL=0;      
	return(retc);
}

/********************** 上为 iic。下为DS3231 ****************************/

/******************************************************************
* BCD转换为Byte         
功能: BCD转换为Byte
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
* B码转换为BCD码         
功能: B码转换为BCD码
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
/***********将一个字节写入DS3231指定的地址***********/
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
/************从DS3231当前地址读一个字节************/
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
/************从DS3231指定地址读一个字节************/
u8 DS3231_I2C_Read_Add ( u8 reg_addr )
{
    DS3231_IIC_Start();
    DS3231_IIC_SendByte ( DS3231Addr );
		DS3231_IIC_wait_ACK();
    DS3231_IIC_SendByte ( reg_addr );
		DS3231_IIC_wait_ACK();
    return ( DS3231_IIC_Read() );
}

/************************* DS3213算法 ********************************************/
/*函数声明*/
void DS3231_Readtime(CLASS_Clock* clock);


//根据蔡勒（Zeller）公式计算星期几
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
/*********************读取时间**********************/
void DS3231_Readtime(CLASS_Clock* clock)
{
    u8 tempHbyte;
		u8 tempLbyte;
	
    clock->Second = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_SEC ) );//秒
    clock->Minute = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_MIN ) );//分
    clock->Hour   = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_HOUR ) & 0x3f);//时
    clock->Week   = DS3231_I2C_Read_Add ( DS3231_WEEK );//星期
    clock->Day    = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_DATE ) );//日
    clock->Month  = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_MONTH ) );//月
    clock->Year   = BCDtoHEX ( DS3231_I2C_Read_Add ( DS3231_YEAR ) )+2000;//年
		
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
/****************修改时间***************************/
void DS3231_SetTime ( CLASS_Clock* clock )
{
    int temp = 0;

    temp = B_BCD ( clock->Second );
    DS3231_IIC_Write ( DS3231_SEC, temp ); //修改秒
    temp = B_BCD ( clock->Minute );
    DS3231_IIC_Write ( DS3231_MIN, temp ); //修改分
    temp = B_BCD ( clock->Hour ) & 0xbf;//Make sure clock is still 24 Hour
    DS3231_IIC_Write ( DS3231_HOUR, temp ); //修改时
    temp = B_BCD ( clock->Day );
    DS3231_IIC_Write ( DS3231_DATE, temp ); //修改日
		temp = B_BCD ( clock->Week );
    DS3231_IIC_Write ( DS3231_WEEK, temp ); //修改星期
    temp = B_BCD ( clock->Month );
    DS3231_IIC_Write ( DS3231_MONTH, temp ); //修改月
    temp = B_BCD ( clock->Year - 2000);
    DS3231_IIC_Write ( DS3231_YEAR, temp ); //修改年
}

//初始化	    
void bsp_DS3231_Init(void)
{ 	
//	CLASS_Clock clock;
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	DS3231_I2C_GPIO_APBxClock_FUN(DS3231_I2C_CLK_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCL_InitStructure.GPIO_Pin = DS3231_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(DS3231_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //初始化GPIOX
	
	DS3231_I2C_GPIO_APBxClock_FUN(DS3231_I2C_SDA_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SDA_InitStructure.GPIO_Pin = DS3231_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(DS3231_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //初始化GPIOX
	
	DS3231_IIC_SCL = 1;		
	DS3231_IIC_SDA = 1;
	
//	DS3231_IIC_Write ( DS3231_AL1DAY, 0x81 ); //A1M4置位，时分秒匹配时闹钟响应
//	DS3231_IIC_Write ( DS3231_AL2DAY, 0x81 ); //A2M4置位，时分匹配时闹钟响应
//	DS3231_IIC_Write ( DS3231_CONTROL, 0x04 ); //中断允许，闹钟1和2关闭
	DS3231_IIC_Write ( DS3231_STATUS, 0x00 ); //32KHZ输出禁止，闹钟标志位清零
	
//	clock.Second = 2;
//	clock.Minute = 18;
//	clock.Hour = 17;
//	clock.Day = 18;
//	clock.Week = 6;
//	clock.Month = 4;
//	clock.Year = 2020;
//	DS3231_SetTime(&clock);

}

//累加函数
void SetTime_Add(CLASS_Clock *clock,SetT_Status timestatus,u8 add)  
{
	switch(timestatus)
	{
		case enSecond:
			if(add)
			{
			   clock->Second++;
				 if(clock->Second > 59) clock->Second=0;   //最大60s
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
				 if(clock->Minute > 59) clock->Minute=0;   //最大60min
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
				 if(clock->Hour > 23) clock->Hour=0;      //最大24h
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
					 if(clock->Day > 31) clock->Day=1;      //最大31day
				 }
				 else 
					  if(clock->Day > 30) clock->Day=1;      //最大30day
			}
			else 
			{
				clock->Day--;
				if(clock->Month==1||clock->Month==3||clock->Month==5||clock->Month==7||clock->Month==8||clock->Month==10||clock->Month==12)
				{
					if(clock->Day < 1) clock->Day=31;      //最大31day
				}
				else 
					 if(clock->Day < 1) clock->Day=30;      //最大30day
			}
		  break;
			
		case enWeek:
			if(add)
			{
			   clock->Week++;
				 if(clock->Week > 7) clock->Week=1;      //最大7
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
