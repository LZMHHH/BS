/**
  ******************************************************************************
  * @file    bsp_DS3231.h
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
	
#ifndef _bsp_DS3231_H
#define _bsp_DS3231_H	

#include "includes.h"


/**************************I2C�������壬I2C1��I2C2********************************/
//#define             DS3231_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //Ӳ��
//#define             DS3231_I2C_CLK                             RCC_APB1Periph_I2C1      //Ӳ��
#define             DS3231_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             DS3231_I2C_CLK_CLK                         RCC_APB2Periph_GPIOB 
#define             DS3231_I2C_SDA_CLK                         RCC_APB2Periph_GPIOB    
#define             DS3231_I2C_SCL_PORT                        GPIOB   
#define             DS3231_I2C_SCL_PIN                         GPIO_Pin_8
#define             DS3231_I2C_SDA_PORT                        GPIOB 
#define             DS3231_I2C_SDA_PIN                         GPIO_Pin_9


//IO��������
//   CRL:0-7   CRH:8-15   �ڼ������ƶ�4*x   ��  0XFFFFFFF0 �� ��x����Ϊ0;
#define DS3231_SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<(4*1);}
#define DS3231_SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<(4*1);}


#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

//IO��������	 
#define DS3231_IIC_SCL    PBout(8) //SCL
#define DS3231_IIC_SDA    PBout(9) //SDA	 
#define DS3231_READ_SDA   PBin(9)  //����SDA 


/**************************** defines *******************************/
#define DS3231Addr  0xd0    /* DS3231 slave address (write) */
//#define DS3231_WriteAddress 0xD0    //����д��ַ
//#define DS3231_ReadAddress  0xD1    //��������ַ

#define DS3231_SEC  0x00    //��
#define DS3231_MIN  0x01    //��
#define DS3231_HOUR 0x02    //ʱ
#define DS3231_WEEK 0x03    //����
#define DS3231_DATE 0x04    //��
#define DS3231_MONTH 0x05    //��
#define DS3231_YEAR 0x06    //��
//����1
#define DS3231_Al1SEC   0x07    //��
#define DS3231_AL1MIN   0x08    //��
#define DS3231_AL1HOUR  0x09    //ʱ
#define DS3231_AL1DAY   0x0A    //����/��
//����2
#define DS3231_AL2MIN   0x0b    //��
#define DS3231_AL2HOUR  0x0c    //ʱ
#define DS3231_AL2DAY   0x0d    //����/��
#define DS3231_CONTROL  0x0e    //���ƼĴ���
#define DS3231_STATUS   0x0f    //״̬�Ĵ���


#define BSY             2       //æ
#define OSF             7       //����ֹͣ��־
#define DS3231_XTAL     0x10    //�����ϻ��Ĵ���
#define DS3231_TEMP_H   0x11    //�¶ȼĴ������ֽ�(8λ)
#define DS3231_TEMP_L   0x12    //�¶ȼĴ������ֽ�(��2λ)  


typedef struct class_clock CLASS_Clock;
	
struct class_clock
{
	int    Second;
	int    Minute;
	int    Hour;
	int    Week;     
	int    Day;      
	int    Month;   
	int    Year;    
	float  Temp;
	char   Switch;  //���ӿ���
	u16    num_save;//���ο�������Ĵ���
};
	
/* soft iic*/
void DS3231_IIC_ACK(void);
void DS3231_IIC_NACK(void);
u8   DS3231_IIC_wait_ACK(void);
void DS3231_IIC_Start(void);
void DS3231_IIC_Stop(void);
void DS3231_IIC_SendByte(u8 byte);
u8   DS3231_IIC_RcvByte(void);
/* iic ����api */
u8   DS3231_IIC_Write ( u8 reg_addr, u8 bytedata );
u8   DS3231_IIC_Read(void);
u8   DS3231_I2C_Read_Add ( u8 reg_addr );


/* API */
void bsp_DS3231_Init(void);
void DS3231_Readtime(CLASS_Clock* clock);
void DS3231_SetTime ( CLASS_Clock* clock );

#endif  


























