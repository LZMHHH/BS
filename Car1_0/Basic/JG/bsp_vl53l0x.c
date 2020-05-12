/**
  ******************************************************************************
  * @file    bsp_vl53l0x.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "bsp_vl53l0x.h"

//接口
#define Vl53l0xdelay_us DwtDelay_uS
#define Vl53l0xdelay_ms DwtDelay_mS



#define Vl53l0x_write 0
#define Vl53l0x_read  1

/*
*********************************************************************************************************
*	函 数 名: VL53L0X_IIC_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void VL53L0X_IIC_Start(void)
{
	VL53L0X_SDA_OUT();  
	VL53L0X_IIC_SDA=1;  
	VL53L0X_IIC_SCL=1;  
	Vl53l0xdelay_us(3);	  
	VL53L0X_IIC_SDA=0;  
	Vl53l0xdelay_us(3);   
	VL53L0X_IIC_SCL=0;
}

/*
*********************************************************************************************************
*	函 数 名: VL53L0X_IIC_Start
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void VL53L0X_IIC_Stop(void)
{
	VL53L0X_SDA_OUT();	
	VL53L0X_IIC_SCL=0;	
	VL53L0X_IIC_SDA=0;  	
	Vl53l0xdelay_us(3);		
	VL53L0X_IIC_SCL=1;	
	Vl53l0xdelay_us(3);	
	VL53L0X_IIC_SDA=1;	
	Vl53l0xdelay_us(3);
}

/*
*********************************************************************************************************
*	函 数 名: VL53L0X_IIC_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：_ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
void VL53L0X_IIC_SendByte(uint8_t byte)
{
	uint8_t i;

	u8  BitCnt;	
	VL53L0X_SDA_OUT();	
	VL53L0X_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//要传送的数据长度为8位	
	{		
		if(byte&0x80) 
			VL53L0X_IIC_SDA=1;//判断发送位		
		else VL53L0X_IIC_SDA=0; 		
		byte<<=1;		
		Vl53l0xdelay_us(2); 		
		VL53L0X_IIC_SCL=1;		
		Vl53l0xdelay_us(2);		
		VL53L0X_IIC_SCL=0;		
		Vl53l0xdelay_us(2);	
	}
}

/*
*********************************************************************************************************
*	函 数 名: VL53L0X_IIC_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_ReadByte(void)
{
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	VL53L0X_SDA_IN();//置数据线为输入方式  
	Vl53l0xdelay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		VL53L0X_IIC_SCL=0;//置时钟线为低，准备接收数据位	
		Vl53l0xdelay_us(2);               	
		VL53L0X_IIC_SCL=1;//置时钟线为高使数据线上数据有效                	
		retc=retc<<1;	
		if(VL53L0X_READ_SDA) 
			retc |=1;//读数据位,接收的数据位放入retc中 	
		Vl53l0xdelay_us(1);  
	}  
	VL53L0X_IIC_SCL=0;      
	return(retc);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_WaitAck(void)
{
	u8 t = 200;    
	VL53L0X_SDA_OUT();    
	VL53L0X_IIC_SDA=1;//8位发送完后释放数据线，准备接收应答位     
	Vl53l0xdelay_us(1);    
	VL53L0X_IIC_SCL=0;    
	Vl53l0xdelay_us(1);     
	VL53L0X_SDA_IN();    
	Vl53l0xdelay_us(1);     
	while(VL53L0X_READ_SDA)//等待SHT30应答    
	{	
			t--;
			Vl53l0xdelay_us(1); 	
			if(t==0)	
			{	  
				VL53L0X_IIC_SCL=0;	  
				return 1;	
			}	
			Vl53l0xdelay_us(1);     
	}    
	Vl53l0xdelay_us(1);          
	VL53L0X_IIC_SCL=1;    
	Vl53l0xdelay_us(1);    
	VL53L0X_IIC_SCL=0;                 
	Vl53l0xdelay_us(1);        
	return 0;	
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void VL53L0X_IIC_Ack(void)
{
	VL53L0X_SDA_OUT();
	VL53L0X_IIC_SCL=0;
	Vl53l0xdelay_us(2);  
	VL53L0X_IIC_SDA=0;
	Vl53l0xdelay_us(2);
	VL53L0X_IIC_SCL=1;
	Vl53l0xdelay_us(2);
	VL53L0X_IIC_SCL=0;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void VL53L0X_IIC_NAck(void)
{
	VL53L0X_SDA_OUT();  
	VL53L0X_IIC_SCL=0;  
	Vl53l0xdelay_us(2);   
	VL53L0X_IIC_SDA=1;  
	Vl53l0xdelay_us(2);        
	VL53L0X_IIC_SCL=1;  
	Vl53l0xdelay_us(2);                     
	VL53L0X_IIC_SCL=0;                       
	Vl53l0xdelay_us(1);  
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SHT3x_Init
*	功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

//初始化	    
void bsp_VL53L0X_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	VL53L0X_I2C_GPIO_APBxClock_FUN(VL53L0X_I2C_CLK_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCL_InitStructure.GPIO_Pin = VL53L0X_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(VL53L0X_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //初始化GPIOX
	
	VL53L0X_I2C_GPIO_APBxClock_FUN(VL53L0X_I2C_SDA_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SDA_InitStructure.GPIO_Pin = VL53L0X_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(VL53L0X_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //初始化GPIOX
	
	VL53L0X_IIC_SCL = 1;		
	VL53L0X_IIC_SDA = 1;
	VL53L0X_IIC_Stop();			/* 发送停止信号 */
	
}

/*
*********************************************************************************************************
*	函 数 名: i2c_CheckDevice
*	功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
*	形    参：_Address：设备的I2C总线地址
*	返 回 值: 返回值 0 表示正确， 返回1表示未探测到
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	bsp_VL53L0X_Init();		/* 配置GPIO */

	
	VL53L0X_IIC_Start();		/* 发送启动信号 */

	/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
	VL53L0X_IIC_SendByte(_Address | Vl53l0x_write);
	ucAck = VL53L0X_IIC_WaitAck();	/* 检测设备的ACK应答 */

	VL53L0X_IIC_Stop();			/* 发送停止信号 */

	return ucAck;
}


/*
*********************************************************************************************************
*	上为iic
* 下为设备
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*	函 数 名: ee_CheckOk
*	功能说明: 判断串行EERPOM是否正常
*	形    参：无
*	返 回 值: 1 表示正常， 0 表示不正常
*********************************************************************************************************
*/
uint8_t vl53l0x_CheckOk(void)
{
	if (VL53L0X_IIC_CheckDevice(VL53L0X_DEV_ADDR) == 0)
	{
		return 1;
	}
	else
	{
		/* 失败后，切记发送I2C总线停止信号 */
		VL53L0X_IIC_Stop();		
		return 0;
	}
}

/*
*********************************************************************************************************
*	函 数 名: ee_ReadBytes
*	功能说明: 从串行EEPROM指定地址处开始读取若干数据
*	形    参：_usAddress : 起始地址
*			 _usSize : 数据长度，单位为字节
*			 _pReadBuf : 存放读到的数据的缓冲区指针
*	返 回 值: 0 表示失败，1表示成功
*********************************************************************************************************
*/
uint8_t vl53l0x_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i;
	
	/* 采用串行EEPROM随即读取指令序列，连续读取若干字节 */
	
	/* 第1步：发起I2C总线启动信号 */
	VL53L0X_IIC_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_write);	/* 此处是写指令 */
	 
	/* 第3步：等待ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}

	/* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
	VL53L0X_IIC_SendByte((uint8_t)_usAddress);
	
	/* 第5步：等待ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}
	
	/* 第6步：重新启动I2C总线。前面的代码的目的向EEPROM传送地址，下面开始读取数据 */
	VL53L0X_IIC_Start();
	
	/* 第7步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_read);	/* 此处是读指令 */
	
	/* 第8步：发送ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM器件无应答 */
	}	
	
	/* 第9步：循环读取数据 */
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = VL53L0X_IIC_ReadByte();	/* 读1个字节 */
		
		/* 每读完1个字节后，需要发送Ack， 最后一个字节不需要Ack，发Nack */
		if (i != _usSize - 1)
		{
			VL53L0X_IIC_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */
		}
		else
		{
			VL53L0X_IIC_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
		}
	}
	/* 发送I2C总线停止信号 */
	VL53L0X_IIC_Stop();
	return 1;	/* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	VL53L0X_IIC_Stop();
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: ee_WriteBytes
*	功能说明: 向串行EEPROM指定地址写入若干数据，采用页写操作提高写入效率
*	形    参：_usAddress : 起始地址
*			 _usSize : 数据长度，单位为字节
*			 _pWriteBuf : 存放读到的数据的缓冲区指针
*	返 回 值: 0 表示失败，1表示成功
*********************************************************************************************************
*/
uint8_t vl53l0x_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	uint16_t usAddr;
	
	/* 
		写串行EEPROM不像读操作可以连续读取很多字节，每次写操作只能在同一个page。
		对于24xx02，page size = 8
		简单的处理方法为：按字节写操作模式，没写1个字节，都发送地址
		为了提高连续写的效率: 本函数采用page wirte操作。
	*/

	usAddr = _usAddress;	
	for (i = 0; i < _usSize; i++)
	{
		/* 当发送第1个字节或是页面首地址时，需要重新发起启动信号和地址 */
		if (i == 0)
		{
			/*　第０步：发停止信号，启动内部写操作　*/
			VL53L0X_IIC_Stop();
			
			/* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
				CLK频率为200KHz时，查询次数为30次左右
			*/
			for (m = 0; m < 1000; m++)
			{				
				/* 第1步：发起I2C总线启动信号 */
				VL53L0X_IIC_Start();
				
				/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
				VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_write);	/* 此处是写指令 */
				
				/* 第3步：发送一个时钟，判断器件是否正确应答 */
				if (VL53L0X_IIC_WaitAck() == 0)
				{
					break;
				}
			}
			if (m  == 1000)
			{
				goto cmd_fail;	/* EEPROM器件写超时 */
			}
		
			/* 第4步：发送字节地址，24C02只有256字节，因此1个字节就够了，如果是24C04以上，那么此处需要连发多个地址 */
			VL53L0X_IIC_SendByte((uint8_t)usAddr);
			
			/* 第5步：等待ACK */
			if (VL53L0X_IIC_WaitAck() != 0)
			{
				goto cmd_fail;	/* EEPROM器件无应答 */
			}
		}
	
		/* 第6步：开始写入数据 */
		VL53L0X_IIC_SendByte(_pWriteBuf[i]);
	
		/* 第7步：发送ACK */
		if (VL53L0X_IIC_WaitAck() != 0)
		{
			goto cmd_fail;	/* EEPROM器件无应答 */
		}

		//usAddr++;	/* 地址增1 */		
	}
	
	/* 命令执行成功，发送I2C总线停止信号 */
	VL53L0X_IIC_Stop();
	return 1;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	VL53L0X_IIC_Stop();
	return 0;
}

uint8_t vl53l0x_WriteByte(uint8_t _pWriteBuf, uint16_t _usAddress)
{
   return vl53l0x_WriteBytes(&_pWriteBuf, _usAddress, 1);
}

void VL53L0X_Init(void)							  //VL53L0X初始化
{
  vl53l0x_CheckOk();
  vl53l0x_WriteByte(0x01, 0x00);
}

void DistanceRead(CLASS_Distance* diatance)
{
  uint8_t buff[12];
  vl53l0x_WriteByte(0x01, 0x00);                   //MCU通过I2C向VL53L0X发送器件地址，寄存器地址，数据。让VL53L0X工作
	vl53l0x_ReadBytes(buff, 0x14, 12);	               //同理MCU通过I2C读取VL53L0X寄存器的数据
  diatance->xmm = ((buff[10] & 0xFF) << 8) | (buff[11] & 0xFF);	 //对第10，,11帧数据处理
 	diatance->xmm += diatance->offset;									
}

