/**
  ******************************************************************************
  * @file    bsp_bme280.c
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


#include "bsp_bme280.h"

/* 移植时注意搜索“注意” */
void readTrim(void);
/*bme280 气压和温度过采样 工作模式*/
#define BME280_PRESSURE_OSR			  (BME280_OVERSAMP_8X)
#define BME280_TEMPERATURE_OSR		(BME280_OVERSAMP_16X)
#define BME280_HUMIDITY_OSR       (BME280_PRESSURE_OSR)
#define BME280_MODE					      (BME280_PRESSURE_OSR<<2|BME280_TEMPERATURE_OSR<<5|BME280_NORMAL_MODE)




bme280Calib  bme280Cal;

static u8 bme280ID=0;
static s32 bme280RawPressure=0;
static s32 bme280RawTemperature=0;
static s32 bme280RawHumidity=0;

static void bme280GetPressure(void);
static void presssureFilter(float* in,float* out);
static float bme280PressureToAltitude(float* pressure/*, float* groundPressure, float* groundTemp*/);

//接口
#define BME280delay_us DwtDelay_uS
#define BME280delay_ms DwtDelay_mS

//初始化BME280，根据需要请参考pdf进行修改****
void bsp_BME280_Init(void)
{

	
	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	BME280_I2C_GPIO_APBxClock_FUN(BME280_I2C_CLK_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCL_InitStructure.GPIO_Pin = BME280_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(BME280_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //初始化GPIOX
	
	BME280_I2C_GPIO_APBxClock_FUN(BME280_I2C_SDA_CLK, ENABLE);	 //使能C端口时钟	
	//没用到PB3和PB4时要删除这条语句	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//禁止JTAG功能，把PB3，PB4作为普通IO口使用
	GPIO_SDA_InitStructure.GPIO_Pin = BME280_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(BME280_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //初始化GPIOX
	
	BME280_IIC_SCL = 1;		
	BME280_IIC_SDA = 1;

	

}

//产生IIC起始信号
void BME280_IIC_Start(void)
{
	BME280_SDA_OUT();     //sda线输出
	BME280_IIC_SDA=1;	  	  
	BME280_IIC_SCL=1;
	BME280delay_us(4);
 	BME280_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	BME280delay_us(4);
	BME280_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}

//产生IIC停止信号
void BME280_IIC_Stop(void)
{
	BME280_SDA_OUT();//sda线输出
	BME280_IIC_SCL=0;
	BME280_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	BME280delay_us(4);
	BME280_IIC_SCL=1;  
	BME280_IIC_SDA=1;//发送I2C总线结束信号
	BME280delay_us(4);							   	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 BME280_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	BME280_SDA_IN();      //SDA设置为输入  
	BME280_IIC_SDA=1;BME280delay_us(1);   
	BME280_IIC_SCL=1;BME280delay_us(1);	 
	while(BME280_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			BME280_IIC_Stop();
			return 1;
		}
	}
	BME280_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 

//产生ACK应答
void BME280_IIC_Ack(void)
{
	BME280_IIC_SCL=0;
	BME280_SDA_OUT();
	BME280_IIC_SDA=0;
	BME280delay_us(2);
	BME280_IIC_SCL=1;
	BME280delay_us(2);
	BME280_IIC_SCL=0;
}

//不产生ACK应答		    
void BME280_IIC_NAck(void)
{
	BME280_IIC_SCL=0;
	BME280_SDA_OUT();
	BME280_IIC_SDA=1;
	BME280delay_us(2);
	BME280_IIC_SCL=1;
	BME280delay_us(2);
	BME280_IIC_SCL=0;
}	

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void BME280_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  BME280_SDA_OUT(); 	    
    BME280_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		BME280_IIC_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		BME280delay_us(2);
		BME280_IIC_SCL=1;
		BME280delay_us(2); 
		BME280_IIC_SCL=0;	
		BME280delay_us(2);
    }	 
}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 BME280_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	BME280_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        BME280_IIC_SCL=0; 
        BME280delay_us(2); 
		BME280_IIC_SCL=1;
        receive<<=1;
        if(BME280_READ_SDA) receive++;   
		BME280delay_us(1); 
    }					 
    if (!ack)
        BME280_IIC_NAck();//发送nACK
    else
        BME280_IIC_Ack(); //发送ACK   
    return receive;
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 BME280_Write_Byte(u8 addr,u8 reg,u8 data)
{
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(BME280_IIC_Wait_Ack())          //等待应答
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Send_Byte(reg);         //写寄存器地址
    BME280_IIC_Wait_Ack();             //等待应答
    BME280_IIC_Send_Byte(data);        //发送数据
    if(BME280_IIC_Wait_Ack())          //等待ACK
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Stop();
    return 0;
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
u8 BME280_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    BME280_IIC_Wait_Ack();             //等待应答
    BME280_IIC_Send_Byte(reg);         //写寄存器地址
    BME280_IIC_Wait_Ack();             //等待应答
	  BME280_IIC_Start();                
    BME280_IIC_Send_Byte((addr<<1)|1); //发送器件地址+读命令
    BME280_IIC_Wait_Ack();             //等待应答
    res=BME280_IIC_Read_Byte(0);		//读数据,发送nACK  
    BME280_IIC_Stop();                 //产生一个停止条件
    return res;  
}

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 BME280_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(BME280_IIC_Wait_Ack())          //等待应答
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Send_Byte(reg);         //写寄存器地址
    BME280_IIC_Wait_Ack();             //等待应答
	  BME280_IIC_Start();                
    BME280_IIC_Send_Byte((addr<<1)|1); //发送器件地址+读命令
    BME280_IIC_Wait_Ack();             //等待应答
    while(len)
    {
        if(len==1)*buf=BME280_IIC_Read_Byte(0);//读数据,发送nACK 
		else *buf=BME280_IIC_Read_Byte(1);		//读数据,发送ACK  
		len--;
		buf++;  
    }
    BME280_IIC_Stop();                 //产生一个停止条件
    return 0;       
}

/************************************************************ 
	上为 iIc 
	下为 BMP
*************************************************************/


void BME280_Init(void)
{	

	bsp_BME280_Init();		                                                           /*初始化I2C*/
	
	bme280ID=BME280_Read_Byte(BME280_SlaveAddr,BME280_CHIPID_REG);	                   /* 读取BME280 ID*/
	

	BME280_Write_Byte(BME280_SlaveAddr,BME280_CTRLHUM_REG,BME280_HUMIDITY_OSR);
	BME280_Write_Byte(BME280_SlaveAddr,BME280_CTRLMEAS_REG,BME280_MODE);
	BME280_Write_Byte(BME280_SlaveAddr,BME280_CONFIG_REG,5<<2);		               /*配置IIR滤波*/
	
	/* 读取校准数据 */
	readTrim();
	
//	printf("BME280 Calibrate Registor Are: \r\n");
//	for(i=0;i<24;i++)
//		printf("Registor %2d: 0x%X\n",i,p[i]);
	
}

void readTrim(void)
{
    uint8_t data[32];
	
	BME280_Read_Len(BME280_SlaveAddr,0x88,24,&data[0]); 
	BME280_Read_Len(BME280_SlaveAddr,0xA1,1,&data[24]); 
	BME280_Read_Len(BME280_SlaveAddr,0xE1,7,&data[25]); 

	bme280Cal.dig_T1 = (data[1] << 8) | data[0];
	bme280Cal.dig_T2 = (data[3] << 8) | data[2];
	bme280Cal.dig_T3 = (data[5] << 8) | data[4];
	bme280Cal.dig_P1 = (data[7] << 8) | data[6];
	bme280Cal.dig_P2 = (data[9] << 8) | data[8];
	bme280Cal.dig_P3 = (data[11]<< 8) | data[10];
	bme280Cal.dig_P4 = (data[13]<< 8) | data[12];
	bme280Cal.dig_P5 = (data[15]<< 8) | data[14];
	bme280Cal.dig_P6 = (data[17]<< 8) | data[16];
	bme280Cal.dig_P7 = (data[19]<< 8) | data[18];
	bme280Cal.dig_P8 = (data[21]<< 8) | data[20];
	bme280Cal.dig_P9 = (data[23]<< 8) | data[22];
	bme280Cal.dig_H1 = data[24];
	bme280Cal.dig_H2 = (data[26]<< 8) | data[25];
	bme280Cal.dig_H3 = data[27];
	bme280Cal.dig_H4 = (data[28]<< 4) | (0x0F & data[29]);
	bme280Cal.dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F);
	bme280Cal.dig_H6 = data[31];   
    
}

static void bme280GetPressure(void)
{
    u8 data[BME280_DATA_FRAME_SIZE];

    // read data from sensor
    BME280_Read_Len(BME280_SlaveAddr,BME280_PRESSURE_MSB_REG,BME280_DATA_FRAME_SIZE,data);
    bme280RawPressure=(s32)((((uint32_t)(data[0]))<<12)|(((uint32_t)(data[1]))<<4)|((uint32_t)data[2]>>4));
    bme280RawTemperature=(s32)((((uint32_t)(data[3]))<<12)|(((uint32_t)(data[4]))<<4)|((uint32_t)data[5]>>4));
		bme280RawHumidity=(s32)((((uint32_t)(data[6]))<<8)|(uint32_t)(data[7]));
}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of "5123" equals 51.23 DegC
// t_fine carries fine temperature as global value
static s32 bme280CompensateT(s32 adcT)
{
    s32 var1,var2,T;

    var1=((((adcT>>3)-((s32)bme280Cal.dig_T1<<1)))*((s32)bme280Cal.dig_T2))>>11;
    var2=(((((adcT>>4)-((s32)bme280Cal.dig_T1))*((adcT>>4)-((s32)bme280Cal.dig_T1)))>>12)*((s32)bme280Cal.dig_T3))>>14;
    bme280Cal.t_fine=var1+var2;
	
    T=(bme280Cal.t_fine*5+128)>>8;

    return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of "24674867" represents 24674867/256 = 96386.2 Pa = 963.862 hPa
static uint32_t bme280CompensateP(s32 adcP)
{
    int64_t var1,var2,p;
    var1=((int64_t)bme280Cal.t_fine)-128000;
    var2=var1*var1*(int64_t)bme280Cal.dig_P6;
    var2=var2+((var1*(int64_t)bme280Cal.dig_P5)<<17);
    var2=var2+(((int64_t)bme280Cal.dig_P4)<<35);
    var1=((var1*var1*(int64_t)bme280Cal.dig_P3)>>8)+((var1*(int64_t)bme280Cal.dig_P2)<<12);
    var1=(((((int64_t)1)<<47)+var1))*((int64_t)bme280Cal.dig_P1)>>33;
    if (var1==0)
        return 0;
    p=1048576-adcP;
    p=(((p<<31)-var2)*3125)/var1;
    var1=(((int64_t)bme280Cal.dig_P9)*(p>>13)*(p>>13))>>25;
    var2=(((int64_t)bme280Cal.dig_P8)*p)>>19;
    p=((p+var1+var2)>>8)+(((int64_t)bme280Cal.dig_P7)<<4);
    return(uint32_t)p;
}

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer bits and 10 fractional bits).
// Output value of "47445" represents 47445/1024 = 46.333 %RH
static uint32_t bme280CompensateH(s32 adcH)
{
	s32 var;
	var=(bme280Cal.t_fine-((s32)76800));
	var=(((((adcH<<14)-(((s32)bme280Cal.dig_H4)<<20)-(((s32)bme280Cal.dig_H5)*var))+((s32)16384))>>15)*(((((((var*(
		(s32)bme280Cal.dig_H6))>>10)*(((var*((s32)bme280Cal.dig_H3))>>11)+((s32)32768)))>>10)+((s32)2097152))*((s32)
		bme280Cal.dig_H2)+8192)>>14));
	var=(var-(((((var>>15)*(var>>15))>>7)*((s32)bme280Cal.dig_H1))>>4));
	var=(var<0?0:var);
	var=(var>419430400?419430400:var);
	return (uint32_t)(var>>12);
}


#define FILTER_NUM	5
#define FILTER_A	0.1f

/*限幅平均滤波法*/
static void presssureFilter(float* in,float* out)
{	
	static u8 i=0;
	static float filter_buf[FILTER_NUM]={0.0};
	double filter_sum=0.0;
	u8 cnt=0;	
	float deta;

	if(filter_buf[i]==0.0f)
	{
		filter_buf[i]=*in;
		*out=*in;
		if(++i>=FILTER_NUM)	
			i=0;
	} 
	else 
	{
		if(i)
			deta=*in-filter_buf[i-1];
		else 
			deta=*in-filter_buf[FILTER_NUM-1];
		
		if(fabs(deta)<FILTER_A)
		{
			filter_buf[i]=*in;
			if(++i>=FILTER_NUM)	
				i=0;
		}
		for(cnt=0;cnt<FILTER_NUM;cnt++)
		{
			filter_sum+=filter_buf[cnt];
		}
		*out=filter_sum /FILTER_NUM;
	}
}

void BME280_Getdata(CLASS_Bme *bme)
{
	static float t;
	static float p;
	static float h;
	
	bme280GetPressure();

	t=bme280CompensateT(bme280RawTemperature)/100.0;		
	p=bme280CompensateP(bme280RawPressure)/25600.0;	
	h=bme280CompensateH(bme280RawHumidity)/1024.0;

	presssureFilter(&p,&(bme->pressure));
	bme->temperature=(float)t;                                                     /*单位度*/
	//*pressure=(float)p ;	                                                   /*单位hPa*/	
	bme->humidity=(float)h;
	
	bme->asl=bme280PressureToAltitude(&(bme->pressure));	                               /*转换成海拔*/	
}

#define CONST_PF 0.1902630958	                                               //(1/5.25588f) Pressure factor
#define FIX_TEMP 25				                                               // Fixed Temperature. ASL is a function of pressure and temperature, but as the temperature changes so much (blow a little towards the flie and watch it drop 5 degrees) it corrupts the ASL estimates.
								                                               // TLDR: Adjusting for temp changes does more harm than good.
/*
 * Converts pressure to altitude above sea level (ASL) in meters
*/
static float bme280PressureToAltitude(float* pressure/*, float* groundPressure, float* groundTemp*/)
{
    if (*pressure>0)
    {
        return((pow((1015.7f/ *pressure),CONST_PF)-1.0f)*(FIX_TEMP+273.15f))/0.0065f;
    }
    else
    {
        return 0;
    }
}





