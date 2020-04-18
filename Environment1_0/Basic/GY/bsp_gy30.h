/**
  ******************************************************************************
  * @file    oled.h
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
	* ��������   : OLED 4�ӿ���ʾ����(32ϵ��)
	*
	*
	*
  ******************************************************************************
  */
	
#ifndef _BSP_GY30_H
#define _BSP_GY30_H	

#include "includes.h"

/**************************I2C�������壬I2C1��I2C2********************************/
//#define             GY30_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //Ӳ��
//#define             GY30_I2C_CLK                             RCC_APB1Periph_I2C1      //Ӳ��
#define             GY30_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             GY30_I2C_CLK_CLK                         RCC_APB2Periph_GPIOC 
#define             GY30_I2C_SDA_CLK                         RCC_APB2Periph_GPIOC    
#define             GY30_I2C_SCL_PORT                        GPIOC   
#define             GY30_I2C_SCL_PIN                         GPIO_Pin_9
#define             GY30_I2C_SDA_PORT                        GPIOC 
#define             GY30_I2C_SDA_PIN                         GPIO_Pin_8


//IO��������
//   CRL:0-7   CRH:8-15   �ڼ������ƶ�4*x   ��  0XFFFFFFF0 �� ��x����Ϊ0;
#define GY30_SDA_IN()  {GPIOC->CRH&=0XFFFFFFF0;GPIOC->CRH|=8<<(4*0);}
#define GY30_SDA_OUT() {GPIOC->CRH&=0XFFFFFFF0;GPIOC->CRH|=3<<(4*0);}


#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

//IO��������	 
#define GY30_IIC_SCL    PCout(9) //SCL
#define GY30_IIC_SDA    PCout(8) //SDA	 
#define GY30_READ_SDA   PCin(8)  //����SDA 


#define  BH1750_ADDR BH1750_ADDRESS_AD0_LOW     //�ͻ��Ǹߵ�ַ�����ڡ���IIC�Խ�

#define BH1750_ADDRESS_AD0_LOW     0x46 // address pin low (GND), default for InvenSense evaluation board
#define BH1750_ADDRESS_AD0_HIGH    0xb8 // address pin high (VCC)

/* ״̬���� */
typedef enum
{
   LightMode_NO,
	 LightMode_GS,    //����ģʽ
	 LightMode_RC,    //�ճ�ģʽ
}  Light_Mode;

typedef struct class_light CLASS_Light;

struct class_light
{
	int   BH_Data;           //�ϳ�����
	float BH_Voltage;        //��������
};


void bsp_BH1750_Init(void);
void Updata_BH1750(CLASS_Light *light);

#endif  
























