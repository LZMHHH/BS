/**
  ******************************************************************************
  * @file    bsp_sht3x.c
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


#include "bsp_sht3x.h" 



//接口
#define Sht3xdelay_us DwtDelay_uS
#define Sht3xdelay_ms DwtDelay_mS





 

#define Sht3x_write 0
#define Sht3x_read  1

/*主机发送ACK*/
void SHT3X_IIC_ACK(void)
{ 
		SHT3X_SDA_OUT();
		SHT3X_IIC_SCL=0;
		Sht3xdelay_us(2);  
		SHT3X_IIC_SDA=0;
		Sht3xdelay_us(2);
		SHT3X_IIC_SCL=1;
		Sht3xdelay_us(2);
		SHT3X_IIC_SCL=0;
		Sht3xdelay_us(1); 
}

 /*主机不发送ACK*/
void SHT3X_IIC_NACK(void)
{  
	SHT3X_SDA_OUT();  
	SHT3X_IIC_SCL=0;  
	Sht3xdelay_us(2);   
	SHT3X_IIC_SDA=1;  
	Sht3xdelay_us(2);        
	SHT3X_IIC_SCL=1;  
	Sht3xdelay_us(2);                     
	SHT3X_IIC_SCL=0;                       
	Sht3xdelay_us(1);    
}

 
 
/*主机等待从机的ACK
 *返回：1 错误，0，正常
 */
u8 SHT3X_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	SHT3X_SDA_OUT();    
	SHT3X_IIC_SDA=1;//8位发送完后释放数据线，准备接收应答位     
	Sht3xdelay_us(1);    
	SHT3X_IIC_SCL=0;    
	Sht3xdelay_us(1);     
	SHT3X_SDA_IN();    
	Sht3xdelay_us(1);     
	while(SHT3X_READ_SDA)//等待SHT30应答    
	{	
			t--;
			Sht3xdelay_us(1); 	
			if(t==0)	
			{	  
				SHT3X_IIC_SCL=0;	  
				return 1;	
			}	
			Sht3xdelay_us(1);     
	}    
	Sht3xdelay_us(1);          
	SHT3X_IIC_SCL=1;    
	Sht3xdelay_us(1);    
	SHT3X_IIC_SCL=0;                 
	Sht3xdelay_us(1);        
	return 0;	
}



/******************************************************************
 *功能:启动I2C总线,即发送I2C起始条件.  
********************************************************************/
void SHT3X_IIC_Start(void)
{  
	SHT3X_SDA_OUT();  
	SHT3X_IIC_SDA=1;  
	SHT3X_IIC_SCL=1;  
	Sht3xdelay_us(4);	  
	SHT3X_IIC_SDA=0;  
	Sht3xdelay_us(4);   
	SHT3X_IIC_SCL=0;
}


/******************************************************************
*功能:结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void SHT3X_IIC_Stop(void)
{	
	SHT3X_SDA_OUT();	
	SHT3X_IIC_SCL=0;	
	SHT3X_IIC_SDA=0;  	
	Sht3xdelay_us(4);		
	SHT3X_IIC_SCL=1;	
	Sht3xdelay_us(4);	
	SHT3X_IIC_SDA=1;	
	Sht3xdelay_us(4);
}


/******************************************************************
*字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:将数据c发送出去,可以是地址,也可以是数据
********************************************************************/
void  SHT3X_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	SHT3X_SDA_OUT();	
	SHT3X_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//要传送的数据长度为8位	
	{		
		if(byte&0x80) 
			SHT3X_IIC_SDA=1;//判断发送位		
		else SHT3X_IIC_SDA=0; 		
		byte<<=1;		
		Sht3xdelay_us(2); 		
		SHT3X_IIC_SCL=1;		
		Sht3xdelay_us(2);		
		SHT3X_IIC_SCL=0;		
		Sht3xdelay_us(2);	
	}
}


/******************************************************************
* 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能: 用来接收从器件传来的数据  
********************************************************************/    
u8 SHT3X_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	SHT3X_SDA_IN();//置数据线为输入方式  
	Sht3xdelay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		SHT3X_IIC_SCL=0;//置时钟线为低，准备接收数据位	
		Sht3xdelay_us(2);               	
		SHT3X_IIC_SCL=1;//置时钟线为高使数据线上数据有效                	
		retc=retc<<1;	
		if(SHT3X_READ_SDA) 
			retc |=1;//读数据位,接收的数据位放入retc中 	
		Sht3xdelay_us(1);  
	}  
	SHT3X_IIC_SCL=0;      
	return(retc);
}


/************************* API ********************************************/

/******************************************************************* 
温湿度获取函数               
函数原型: SHT30_read_result(u8 addr);
					addr:器件地址，这里为：0x44
功能: 用来接收从器件采集并合成温湿度
说明：工作在单射模式（Single Shot Mode）（下面选择该模式）和 工作在周期获取模式（Periodic Data Acquisition Mode）
********************************************************************/ 
void SHT3x_Getdata(u8 addr,CLASS_Huimiture* huimiture)
{	
	u16 tem,hum;	
	u16 buff[6];	
	float Temperature=0;	
	float Humidity=0;		
	SHT3X_IIC_Start();	
	SHT3X_IIC_SendByte(addr<<1 | Sht3x_write);//写7位I2C设备地址加0作为写取位,1为读取位	
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_SendByte(0x2C);	  /* 写入0x2c06 表示高速测量，开启时钟拉伸 */
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_SendByte(0x06);	
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_Stop();	
	Sht3xdelay_us(50);	
	SHT3X_IIC_Start();	
	SHT3X_IIC_SendByte(addr<<1 | Sht3x_read);//写7位I2C设备地址加0作为写取位,1为读取位	
	if(SHT3X_IIC_wait_ACK()==0)	
	{		
		buff[0]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[1]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[2]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[3]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[4]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[5]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_NACK();		
		SHT3X_IIC_Stop();	
	}		
	tem = ((buff[0]<<8) | buff[1]);//温度拼接	
	hum = ((buff[3]<<8) | buff[4]);//湿度拼接
	
	/*转换实际温度*/	
	Temperature= (175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)	
	Humidity= (100.0*(float)hum/65535.0);// RH = hum*100 / (2^16-1)		
	
	if((Temperature>=-20)&&(Temperature<=125))//过滤错误数据	
	{		
		huimiture->temperature=Temperature;		
	}
	if((Humidity>=0)&&(Humidity<=100))//过滤错误数据	
	{				
		huimiture->huimidity=Humidity;		
	}
}



//初始化	    
void bsp_SHT3x_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	SHT3X_I2C_GPIO_APBxClock_FUN(SHT3X_I2C_CLK_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCL_InitStructure.GPIO_Pin = SHT3X_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(SHT3X_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //初始化GPIOX
	
	SHT3X_I2C_GPIO_APBxClock_FUN(SHT3X_I2C_SDA_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SDA_InitStructure.GPIO_Pin = SHT3X_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(SHT3X_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //初始化GPIOX
	
	SHT3X_IIC_SCL = 1;		
	SHT3X_IIC_SDA = 1;
	
}
