/**
  ******************************************************************************
  * @file    bsp_bme280.c
  * @author  fire
  * @version V1.0
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
	*
  ******************************************************************************
  */


#include "bsp_bme280.h"

/* ��ֲʱע��������ע�⡱ */
void readTrim(void);
/*bme280 ��ѹ���¶ȹ����� ����ģʽ*/
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

//�ӿ�
#define BME280delay_us DwtDelay_uS
#define BME280delay_ms DwtDelay_mS

//��ʼ��BME280��������Ҫ��ο�pdf�����޸�****
void bsp_BME280_Init(void)
{

	
	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	BME280_I2C_GPIO_APBxClock_FUN(BME280_I2C_CLK_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SCL_InitStructure.GPIO_Pin = BME280_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(BME280_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //��ʼ��GPIOX
	
	BME280_I2C_GPIO_APBxClock_FUN(BME280_I2C_SDA_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	//û�õ�PB3��PB4ʱҪɾ���������	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//��ֹJTAG���ܣ���PB3��PB4��Ϊ��ͨIO��ʹ��
	GPIO_SDA_InitStructure.GPIO_Pin = BME280_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(BME280_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //��ʼ��GPIOX
	
	BME280_IIC_SCL = 1;		
	BME280_IIC_SDA = 1;

	

}

//����IIC��ʼ�ź�
void BME280_IIC_Start(void)
{
	BME280_SDA_OUT();     //sda�����
	BME280_IIC_SDA=1;	  	  
	BME280_IIC_SCL=1;
	BME280delay_us(4);
 	BME280_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	BME280delay_us(4);
	BME280_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����IICֹͣ�ź�
void BME280_IIC_Stop(void)
{
	BME280_SDA_OUT();//sda�����
	BME280_IIC_SCL=0;
	BME280_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	BME280delay_us(4);
	BME280_IIC_SCL=1;  
	BME280_IIC_SDA=1;//����I2C���߽����ź�
	BME280delay_us(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 BME280_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	BME280_SDA_IN();      //SDA����Ϊ����  
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
	BME280_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
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

//������ACKӦ��		    
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

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void BME280_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  BME280_SDA_OUT(); 	    
    BME280_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
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

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 BME280_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	BME280_SDA_IN();//SDA����Ϊ����
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
        BME280_IIC_NAck();//����nACK
    else
        BME280_IIC_Ack(); //����ACK   
    return receive;
}

//IICдһ���ֽ� 
//devaddr:����IIC��ַ
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 BME280_Write_Byte(u8 addr,u8 reg,u8 data)
{
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //����������ַ+д����
    if(BME280_IIC_Wait_Ack())          //�ȴ�Ӧ��
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Send_Byte(reg);         //д�Ĵ�����ַ
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
    BME280_IIC_Send_Byte(data);        //��������
    if(BME280_IIC_Wait_Ack())          //�ȴ�ACK
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Stop();
    return 0;
}

//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 BME280_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //����������ַ+д����
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
    BME280_IIC_Send_Byte(reg);         //д�Ĵ�����ַ
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
	  BME280_IIC_Start();                
    BME280_IIC_Send_Byte((addr<<1)|1); //����������ַ+������
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
    res=BME280_IIC_Read_Byte(0);		//������,����nACK  
    BME280_IIC_Stop();                 //����һ��ֹͣ����
    return res;  
}

//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 BME280_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    BME280_IIC_Start();
    BME280_IIC_Send_Byte((addr<<1)|0); //����������ַ+д����
    if(BME280_IIC_Wait_Ack())          //�ȴ�Ӧ��
    {
        BME280_IIC_Stop();
        return 1;
    }
    BME280_IIC_Send_Byte(reg);         //д�Ĵ�����ַ
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
	  BME280_IIC_Start();                
    BME280_IIC_Send_Byte((addr<<1)|1); //����������ַ+������
    BME280_IIC_Wait_Ack();             //�ȴ�Ӧ��
    while(len)
    {
        if(len==1)*buf=BME280_IIC_Read_Byte(0);//������,����nACK 
		else *buf=BME280_IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++;  
    }
    BME280_IIC_Stop();                 //����һ��ֹͣ����
    return 0;       
}

/************************************************************ 
	��Ϊ iIc 
	��Ϊ BMP
*************************************************************/


void BME280_Init(void)
{	

	bsp_BME280_Init();		                                                           /*��ʼ��I2C*/
	
	bme280ID=BME280_Read_Byte(BME280_SlaveAddr,BME280_CHIPID_REG);	                   /* ��ȡBME280 ID*/
	

	BME280_Write_Byte(BME280_SlaveAddr,BME280_CTRLHUM_REG,BME280_HUMIDITY_OSR);
	BME280_Write_Byte(BME280_SlaveAddr,BME280_CTRLMEAS_REG,BME280_MODE);
	BME280_Write_Byte(BME280_SlaveAddr,BME280_CONFIG_REG,5<<2);		               /*����IIR�˲�*/
	
	/* ��ȡУ׼���� */
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

/*�޷�ƽ���˲���*/
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
	bme->temperature=(float)t;                                                     /*��λ��*/
	//*pressure=(float)p ;	                                                   /*��λhPa*/	
	bme->humidity=(float)h;
	
	bme->asl=bme280PressureToAltitude(&(bme->pressure));	                               /*ת���ɺ���*/	
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





