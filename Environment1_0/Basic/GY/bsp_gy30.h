/**
  ******************************************************************************
  * @file    oled.h
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
	* 功能描述   : OLED 4接口演示例程(32系列)
	*
	*
	*
  ******************************************************************************
  */
	
#ifndef _BSP_GY30_H
#define _BSP_GY30_H	

#include "includes.h"

/**************************I2C参数定义，I2C1或I2C2********************************/
//#define             GY30_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //硬件
//#define             GY30_I2C_CLK                             RCC_APB1Periph_I2C1      //硬件
#define             GY30_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             GY30_I2C_CLK_CLK                         RCC_APB2Periph_GPIOC 
#define             GY30_I2C_SDA_CLK                         RCC_APB2Periph_GPIOC    
#define             GY30_I2C_SCL_PORT                        GPIOC   
#define             GY30_I2C_SCL_PIN                         GPIO_Pin_9
#define             GY30_I2C_SDA_PORT                        GPIOC 
#define             GY30_I2C_SDA_PIN                         GPIO_Pin_8


//IO方向设置
//   CRL:0-7   CRH:8-15   第几个就移动4*x   且  0XFFFFFFF0 中 第x个至为0;
#define GY30_SDA_IN()  {GPIOC->CRH&=0XFFFFFFF0;GPIOC->CRH|=8<<(4*0);}
#define GY30_SDA_OUT() {GPIOC->CRH&=0XFFFFFFF0;GPIOC->CRH|=3<<(4*0);}


#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

//IO操作函数	 
#define GY30_IIC_SCL    PCout(9) //SCL
#define GY30_IIC_SDA    PCout(8) //SDA	 
#define GY30_READ_SDA   PCin(8)  //输入SDA 


#define  BH1750_ADDR BH1750_ADDRESS_AD0_LOW     //低还是高地址，用于——IIC对接

#define BH1750_ADDRESS_AD0_LOW     0x46 // address pin low (GND), default for InvenSense evaluation board
#define BH1750_ADDRESS_AD0_HIGH    0xb8 // address pin high (VCC)

/* 状态机表 */
typedef enum
{
   LightMode_NO,
	 LightMode_GS,    //跟随模式
	 LightMode_RC,    //日常模式
}  Light_Mode;

typedef struct class_light CLASS_Light;

struct class_light
{
	int   BH_Data;           //合成数据
	float BH_Voltage;        //正常数据
};


void bsp_BH1750_Init(void);
void Updata_BH1750(CLASS_Light *light);

#endif  
























