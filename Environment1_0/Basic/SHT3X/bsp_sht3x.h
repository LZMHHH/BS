/**
  ******************************************************************************
  * @file    bsp_sht3x.h
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
	
#ifndef _bsp_SHT3X_H
#define _bsp_SHT3X_H	

#include "includes.h"


/**************************I2C参数定义，I2C1或I2C2********************************/
//#define             SHT3X_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //硬件
//#define             SHT3X_I2C_CLK                             RCC_APB1Periph_I2C1      //硬件
#define             SHT3X_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             SHT3X_I2C_CLK_CLK                         RCC_APB2Periph_GPIOB 
#define             SHT3X_I2C_SDA_CLK                         RCC_APB2Periph_GPIOB    
#define             SHT3X_I2C_SCL_PORT                        GPIOB   
#define             SHT3X_I2C_SCL_PIN                         GPIO_Pin_15
#define             SHT3X_I2C_SDA_PORT                        GPIOB 
#define             SHT3X_I2C_SDA_PIN                         GPIO_Pin_14


//IO方向设置
//   CRL:0-7   CRH:8-15   第几个就移动4*x   且  0XFFFFFFF0 中 第x个至为0;
#define SHT3X_SDA_IN()  {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=8<<(4*6);}
#define SHT3X_SDA_OUT() {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=3<<(4*6);}

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

//IO操作函数	 
#define SHT3X_IIC_SCL    PBout(15) //SCL
#define SHT3X_IIC_SDA    PBout(14) //SDA	 
#define SHT3X_READ_SDA   PBin(14)  //输入SDA 




typedef struct class_huimiture CLASS_Huimiture;
	
struct class_huimiture
{
	float temperature;     //温度
	float huimidity;			 //湿度
};
	
/* soft iic*/
void SHT3X_IIC_ACK(void);
void SHT3X_IIC_NACK(void);
u8   SHT3X_IIC_wait_ACK(void);
void SHT3X_IIC_Start(void);
void SHT3X_IIC_Stop(void);
void SHT3X_IIC_SendByte(u8 byte);
u8   SHT3X_IIC_RcvByte(void);

/* API */
void bsp_SHT3x_Init(void);
void SHT3x_Getdata(u8 addr,CLASS_Huimiture* huimiture);


#endif  


























