/**
  ******************************************************************************
  * @file    bsp_bme280.h
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
	
#ifndef _BSP_BME280_H
#define _BSP_BME280_H	

#include "includes.h"

/**************************I2C参数定义，I2C1或I2C2********************************/
//#define             BME280_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd   //硬件
//#define             BME280_I2C_CLK                             RCC_APB1Periph_I2C1      //硬件
#define             BME280_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             BME280_I2C_CLK_CLK                         RCC_APB2Periph_GPIOB 
#define             BME280_I2C_SDA_CLK                         RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO    
#define             BME280_I2C_SCL_PORT                        GPIOB   
#define             BME280_I2C_SCL_PIN                         GPIO_Pin_5
#define             BME280_I2C_SDA_PORT                        GPIOB 
#define             BME280_I2C_SDA_PIN                         GPIO_Pin_4


//IO方向设置
//   CRL:0-7   CRH:8-15   第几个就移动4*x   且  0XFFFFFFF0 中 第x个至为0;
#define BME280_SDA_IN()  {BME280_I2C_SDA_PORT->CRL&=0XFFF0FFFF;BME280_I2C_SDA_PORT->CRL|=8<<(4*4);}
#define BME280_SDA_OUT() {BME280_I2C_SDA_PORT->CRL&=0XFFF0FFFF;BME280_I2C_SDA_PORT->CRL|=3<<(4*4);}


#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

//IO操作函数	 
#define BME280_IIC_SCL    PBout(5) //SCL
#define BME280_IIC_SDA    PBout(4) //SDA	 
#define BME280_READ_SDA   PBin(4)  //输入SDA 



#define BME280_ADDRESS 0xEC  
#define BME280_SlaveAddr 0x76    //BME280的器件地址
#define BME280_RESET_VALUE 0xB6  

#define BME280_DIG_T1_LSB_REG       0x88  
#define BME280_DIG_T1_MSB_REG       0x89  
#define BME280_DIG_T2_LSB_REG       0x8A  
#define BME280_DIG_T2_MSB_REG       0x8B  
#define BME280_DIG_T3_LSB_REG       0x8C  
#define BME280_DIG_T3_MSB_REG       0x8D  
#define BME280_DIG_P1_LSB_REG       0x8E  
#define BME280_DIG_P1_MSB_REG       0x8F  
#define BME280_DIG_P2_LSB_REG       0x90  
#define BME280_DIG_P2_MSB_REG       0x91  
#define BME280_DIG_P3_LSB_REG       0x92  
#define BME280_DIG_P3_MSB_REG       0x93  
#define BME280_DIG_P4_LSB_REG       0x94  
#define BME280_DIG_P4_MSB_REG       0x95  
#define BME280_DIG_P5_LSB_REG       0x96  
#define BME280_DIG_P5_MSB_REG       0x97  
#define BME280_DIG_P6_LSB_REG       0x98  
#define BME280_DIG_P6_MSB_REG       0x99  
#define BME280_DIG_P7_LSB_REG       0x9A  
#define BME280_DIG_P7_MSB_REG       0x9B  
#define BME280_DIG_P8_LSB_REG       0x9C  
#define BME280_DIG_P8_MSB_REG       0x9D  
#define BME280_DIG_P9_LSB_REG       0x9E  
#define BME280_DIG_P9_MSB_REG       0x9F  
  
#define BME280_CHIPID_REG           0xD0  /*Chip ID Register */  
#define BME280_RESET_REG            0xE0  /*Softreset Register */  
#define BME280_CTRLHUM_REG          0xF2  /* Ctrl Humidity Register */
#define BME280_STATUS_REG           0xF3  /*Status Register */  
#define BME280_CTRLMEAS_REG         0xF4  /*Ctrl Measure Register */  
#define BME280_CONFIG_REG           0xF5  /*Configuration Register */  
#define BME280_PRESSURE_MSB_REG     0xF7  /*Pressure MSB Register */  
#define BME280_PRESSURE_LSB_REG     0xF8  /*Pressure LSB Register */  
#define BME280_PRESSURE_XLSB_REG    0xF9  /*Pressure XLSB Register */  
#define BME280_TEMPERATURE_MSB_REG  0xFA  /*Temperature MSB Reg */  
#define BME280_TEMPERATURE_LSB_REG  0xFB  /*Temperature LSB Reg */  
#define BME280_TEMPERATURE_XLSB_REG	0xFC  /*Temperature XLSB Reg */  
  
/* 在foreced mode下，1s的采样周期，温度和气压使用最低的精度采集并且使用最小的滤波器系数, 
 * 数据的采集时间大概在6ms，平均功率为3.27uA。 
 * */  
  
/* 在foreced mode下，1s的采样周期, 温度和气压使用最高的精度采集并且使用最大的滤波器系数， 
 * 数据的采集时间大概在70ms，平均功率为30uA。 
 * */  
  
  
#define BME280_SLEEP_MODE				  (0x00)
#define BME280_FORCED_MODE				(0x01)
#define BME280_NORMAL_MODE				(0x03)
  

#define BME280_OVERSAMP_SKIPPED		(0x00)
#define BME280_OVERSAMP_1X				(0x01)
#define BME280_OVERSAMP_2X				(0x02)
#define BME280_OVERSAMP_4X				(0x03)
#define BME280_OVERSAMP_8X				(0x04)
#define BME280_OVERSAMP_16X				(0x05)  

/************************************************/
/**@name	          工作模式定义                 */
/************************************************/
typedef enum
{
	BME280_ULTRA_LOW_POWER_MODE = 0x00,
	BME280_LOW_POWER_MODE = 0x01,
	BME280_STANDARD_RESOLUTION_MODE = 0x02,
	BME280_HIGH_RESOLUTION_MODE = 0x03,
	BME280_ULTRA_HIGH_RESOLUTION_MODE = 0x04
}WORKING_MODE;

typedef enum {  
    BME280_FILTER_OFF = 0x0,    /*filter off*/  
    BME280_FILTER_MODE_1,       /*0.223*ODR*/  
    BME280_FILTER_MODE_2,       /*0.092*ODR*/  
    BME280_FILTER_MODE_3,       /*0.042*ODR*/  
    BME280_FILTER_MODE_4        /*0.021*ODR*/  
} BME280_FILTER_COEFFICIENT;  
  
typedef enum {  
    BME280_T_SB_0_5MS = 0x00,      /*0.5ms */  
    BME280_T_SB_62_5MS= 0x01,      /*62.5ms*/  
    BME280_T_SB_125MS = 0x02,      /*125ms */  
    BME280_T_SB_250MS = 0x03,      /*250ms */  
    BME280_T_SB_500MS = 0x04,      /*500ms */  
    BME280_T_SB_1000MS= 0x05,      /*1000ms*/  
    BME280_T_SB_2000MS= 0x06,      /*2000ms*/  
    BME280_T_SB_4000MS= 0x07,      /*4000ms*/  
} BME280_T_SB;  

#define BME280_DATA_FRAME_SIZE			(8)

typedef struct 
{
    u16 dig_T1;                                                                /* calibration T1 data */
    s16 dig_T2;                                                                /* calibration T2 data */
    s16 dig_T3;                                                                /* calibration T3 data */
    u16 dig_P1;                                                                /* calibration P1 data */
    s16 dig_P2;                                                                /* calibration P2 data */
    s16 dig_P3;                                                                /* calibration P3 data */
    s16 dig_P4;                                                                /* calibration P4 data */
    s16 dig_P5;                                                                /* calibration P5 data */
    s16 dig_P6;                                                                /* calibration P6 data */
    s16 dig_P7;                                                                /* calibration P7 data */
    s16 dig_P8;                                                                /* calibration P8 data */
    s16 dig_P9;                                                                /* calibration P9 data */
	u8  dig_H1;                                                                /* calibration H1 data */
	s16 dig_H2;                                                                /* calibration H2 data */
	u8  dig_H3;                                  							   /* calibration H3 data */
	s16 dig_H4;                                                                /* calibration H4 data */
	s16 dig_H5;                                                                /* calibration H5 data */
	u8  dig_H6;                                                                /* calibration H6 data */
    s32 t_fine;                                                                /* calibration t_fine data */
} bme280Calib;




typedef struct class_bme CLASS_Bme;

struct class_bme
{
	float   temperature;
	float   pressure; 
	float   humidity;
	float   asl;
	
};


void  BME280_Init(void);
void  BME280_Getdata(CLASS_Bme *bme);

#endif  
























