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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_VL53L0X_H
#define _BSP_VL53L0X_H	 
#include "includes.h"


/**************************I2C�������壬I2C1��I2C2********************************/
//#define             VL53L0X_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //Ӳ��
//#define             VL53L0X_I2C_CLK                             RCC_APB1Periph_I2C1      //Ӳ��
#define             VL53L0X_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             VL53L0X_I2C_CLK_CLK                         RCC_APB2Periph_GPIOB 
#define             VL53L0X_I2C_SDA_CLK                         RCC_APB2Periph_GPIOB    
#define             VL53L0X_I2C_SCL_PORT                        GPIOB   
#define             VL53L0X_I2C_SCL_PIN                         GPIO_Pin_0
#define             VL53L0X_I2C_SDA_PORT                        GPIOB 
#define             VL53L0X_I2C_SDA_PIN                         GPIO_Pin_1


//IO��������
//   CRL:0-7   CRH:8-15   �ڼ������ƶ�4*x   ��  0XFFFFFFF0 �� ��x����Ϊ0;
#define VL53L0X_SDA_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<(4*1);}
#define VL53L0X_SDA_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<(4*1);}

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

//IO��������	 
#define VL53L0X_IIC_SCL    PBout(0) //SCL
#define VL53L0X_IIC_SDA    PBout(1) //SDA	 
#define VL53L0X_READ_SDA   PBin(1)  //����SDA 


#define VL53L0X_DEV_ADDR			0x52		/* 24xx02���豸��ַ */



typedef struct class_distance CLASS_Distance;
	
struct class_distance
{
	int xmm;
	
	int offset;
	
	int shieldVal;
};


uint8_t vl53l0x_CheckOk(void);
uint8_t vl53l0x_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t vl53l0x_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t vl53l0x_WriteByte(uint8_t _pWriteBuf, uint16_t _usAddress);
void bsp_VL53L0X_Init(void);
void DistanceRead(CLASS_Distance* diatance);


#endif 

