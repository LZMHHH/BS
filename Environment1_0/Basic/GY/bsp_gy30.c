/**
  ******************************************************************************
  * @file    bsp_gy30.c
  * @author  fire
  * @version V1.0
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
	*
  ******************************************************************************
  */


#include "bsp_gy30.h"

/* 移植时注意搜索“注意” */

u8    BH_Buf[8];                //接收数据缓存区

//接口
#define GY30delay_us DwtDelay_uS
#define GY30delay_ms DwtDelay_mS


#define GY30_write 0
#define GY30_read  1

/*主机发送ACK*/
void GY30_IIC_ACK(void)
{ 
		GY30_SDA_OUT();
		GY30_IIC_SCL=0;
		GY30delay_us(1);  
		GY30_IIC_SDA=0;
		GY30delay_us(1);
		GY30_IIC_SCL=1;
		GY30delay_us(1);
		GY30_IIC_SCL=0;
		GY30delay_us(1); 
}

 /*主机不发送ACK*/
void GY30_IIC_NACK(void)
{  
		GY30_SDA_OUT();  
		GY30_IIC_SCL=0;  
		GY30delay_us(1);   
		GY30_IIC_SDA=1;  
		GY30delay_us(1);        
		GY30_IIC_SCL=1;  
		GY30delay_us(1);                     
		GY30_IIC_SCL=0;                       
		GY30delay_us(1);    
}

 
 
/*主机等待从机的ACK
 *返回：1 错误，0，正常
 */
u8 GY30_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	GY30_SDA_OUT();    
	GY30_IIC_SDA=1;//8位发送完后释放数据线，准备接收应答位     
	GY30delay_us(1);    
	GY30_IIC_SCL=0;    
	GY30delay_us(1);     
	GY30_SDA_IN();    
	GY30delay_us(1);     
	while(GY30_READ_SDA)//等待GY30应答    
	{	
			t--;
			GY30delay_us(1); 	
			if(t==0)	
			{	  
				GY30_IIC_SCL=0;	  
				return 1;	
			}	
			GY30delay_us(1);     
	}    
	GY30delay_us(1);          
	GY30_IIC_SCL=1;    
	GY30delay_us(1);    
	GY30_IIC_SCL=0;                 
	GY30delay_us(1);        
	return 0;	
}



/******************************************************************
 *功能:启动I2C总线,即发送I2C起始条件.  
********************************************************************/
int GY30_IIC_Start(void)
{  
	GY30_SDA_OUT();  
	GY30_IIC_SDA=1; 
	if(!GY30_READ_SDA)return 0;	
	GY30_IIC_SCL=1;  
	GY30delay_us(1);	  
	GY30_IIC_SDA=0; 
	if(GY30_READ_SDA)return 0;	
	GY30delay_us(1);   
	GY30_IIC_SCL=0;
	return 1;	
}


/******************************************************************
*功能:结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void GY30_IIC_Stop(void)
{	
	GY30_SDA_OUT();	
	GY30_IIC_SCL=0;	
	GY30_IIC_SDA=0;  	
	GY30delay_us(1);		
	GY30_IIC_SCL=1;	
	GY30delay_us(1);	
	GY30_IIC_SDA=1;	
	GY30delay_us(1);
}


/******************************************************************
*字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:将数据c发送出去,可以是地址,也可以是数据
********************************************************************/
void GY30_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	GY30_SDA_OUT();	
	GY30_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//要传送的数据长度为8位	
	{		
		if(byte&0x80) 
			GY30_IIC_SDA=1;//判断发送位		
		else GY30_IIC_SDA=0; 		
		byte<<=1;		
		GY30delay_us(1); 		
		GY30_IIC_SCL=1;		
		GY30delay_us(1);		
		GY30_IIC_SCL=0;		
		GY30delay_us(1);	
	}
	GY30_SDA_IN(); 	   //注意：以下7句不可少，否则读到的数据是不正常的，如00212等
	GY30_IIC_SDA=0;  
	GY30delay_us(1); 
	GY30_IIC_SCL=1;
	GY30delay_us(1); 
	GY30_IIC_SCL=0;  
	GY30delay_us(1); 
}


/******************************************************************
* 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能: 用来接收从器件传来的数据  
********************************************************************/    
u8 GY30_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	GY30_SDA_IN();//置数据线为输入方式  
	GY30delay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		GY30_IIC_SCL=0;//置时钟线为低，准备接收数据位	
		GY30delay_us(2);               	
		GY30_IIC_SCL=1;//置时钟线为高使数据线上数据有效                	
		retc=retc<<1;	
		if(GY30_READ_SDA) 
			retc |=1;//读数据位,接收的数据位放入retc中 	
		GY30delay_us(1);  
	}  
	GY30_IIC_SCL=0;      
	return(retc);
}

/********************** 上为 iic。下为GY30 ****************************/


void Single_Write_BH1750(u8 REG_Address)
{
    GY30_IIC_Start();                  //起始信号
    GY30_IIC_SendByte(BH1750_ADDR);    //发送设备地址+写信号
    GY30_IIC_SendByte(REG_Address);    //内部寄存器地址，
    GY30_IIC_Stop();                   //发送停止信号
}
u8 Single_Read_BH1750(u8 REG_Address)
{  u8 REG_data;
    GY30_IIC_Start();                          //起始信号
    GY30_IIC_SendByte(BH1750_ADDR);           //发送设备地址+写信号
    GY30_IIC_SendByte(REG_Address);           //发送存储单元地址，从0开始	
    GY30_IIC_Start();                          //起始信号
    GY30_IIC_SendByte(BH1750_ADDR+1);         //发送设备地址+读信号
    REG_data=GY30_IIC_RcvByte();             //读出寄存器数据
	  GY30_IIC_NACK();   
	  GY30_IIC_Stop();                           //停止信号
    return REG_data; 
}
//连续读出BH1750内部数据
void Multiple_Read_BH1750(void)
{   
	  u8 i;	
    GY30_IIC_Start();                          //起始信号
    GY30_IIC_SendByte(BH1750_ADDR+1);         //发送设备地址+读信号
	  for(i=0; i<3; i++)                      //连续读取2个地址数据，存储中BUF
    {
        BH_Buf[i] = GY30_IIC_RcvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 3)
        {

           GY30_IIC_NACK();                //最后一个数据需要回NOACK
        }
        else
        {		
          GY30_IIC_ACK();                //回应ACK
       }
   }
   GY30_IIC_Stop();                          //停止信号
}
//初始化BH1750，根据需要请参考pdf进行修改****
void bsp_BH1750_Init(void)
{
	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	GY30_I2C_GPIO_APBxClock_FUN(GY30_I2C_CLK_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCL_InitStructure.GPIO_Pin = GY30_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(GY30_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //初始化GPIOX
	
	GY30_I2C_GPIO_APBxClock_FUN(GY30_I2C_SDA_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SDA_InitStructure.GPIO_Pin = GY30_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(GY30_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //初始化GPIOX
	
	
	
	GY30_IIC_SCL = 1;		
	GY30_IIC_SDA = 1;
	
	GY30_IIC_Stop();                          //重要
	
  Single_Write_BH1750(0x01);  

	
}
//更新光强数据 。  注意：需要维持一段时间才能得到数据 180ms左右
void Updata_BH1750(CLASS_Light *light)
{

		Multiple_Read_BH1750();       //连续读出数据，存储在BUF中

	  /* 重新开始 :读出数据后 马上准备下一次读取数据*/
		Single_Write_BH1750(0x01);   // power on
		Single_Write_BH1750(0x10);   // H- resolution mode
	
		/* 数据处理 */
    light->BH_Data=BH_Buf[0];
    light->BH_Data=(light->BH_Data<<8)+BH_Buf[1];//合成数据，即光照数据
    light->BH_Voltage=(float)light->BH_Data/1.2;
}




