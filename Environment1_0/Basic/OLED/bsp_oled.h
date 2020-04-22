/**
  ******************************************************************************
  * @file    oled.h
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
	* 功能描述   : OLED 4接口演示例程(32系列)
	*
	* GND    电源地
	* VCC    接 5V或3.3v电源
	* D0     接 SCL
	* D1     接 SDA
	* RES    接 RES
	* DC     接 DC
	* CS     接 CS (没有这个可以拉低)
	*
	*
  ******************************************************************************
  */
	
#ifndef _bsp_OLED_H
#define _bsp_OLED_H	

#include "includes.h"

//#include "bsp_systick.h"
//#include "stdlib.h"	    
//#include "stm32f10x.h"
//#include "stdlib.h"
//#include "oledfont.h"  

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_SPI   SPI2  //如果为硬件spi时，选择SPI
#define OLED_MODE   0     //0：软件spi  1：为硬件spi 
#define SIZE        16
#define XLevelL		  0x00
#define XLevelH		  0x10
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xFF 
#define X_WIDTH 	  128
#define Y_WIDTH 	  64	    


//哪一种尺寸的oled
#define OLED_SIZE   1     //0:0.96     1:1.3


//*****************   IO口   **************************************************

//  CLK
#define SCLK_GPIO_PORT    	GPIOD			              /* GPIO端口 */
#define SCLK_GPIO_CLK 	    RCC_APB2Periph_GPIOD		/* GPIO端口时钟 */
#define SCLK_GPIO_PIN		    GPIO_Pin_2			        /* 连接到SCL时钟线的GPIO */

//  DIN / SDA
#define SDIN_GPIO_PORT    	GPIOC			              /* GPIO端口 */
#define SDIN_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define SDIN_GPIO_PIN		    GPIO_Pin_12			        /* 连接到SCL时钟线的GPIO */

//  RES
#define RST_GPIO_PORT      	GPIOC			              /* GPIO端口 */
#define RST_GPIO_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define RST_GPIO_PIN		    GPIO_Pin_11		        /* 连接到SCL时钟线的GPIO */

//  DC
#define DC_GPIO_PORT    	  GPIOC 		              /* GPIO端口 */
#define DC_GPIO_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define DC_GPIO_PIN		      GPIO_Pin_10			        /* 连接到SCL时钟线的GPIO */

//  CS
//#define CS_GPIO_PORT      	GPIOB 		              /* GPIO端口 */
//#define CS_GPIO_CLK 	      RCC_APB2Periph_GPIOB  	/* GPIO端口时钟 */
//#define CS_GPIO_PIN		      GPIO_Pin_7		        /* 连接到SCL时钟线的GPIO */

//-----------------测试LED端口定义---------------- 
//#define LED_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_4)    
//#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_4)

//-----------------OLED端口定义----------------  					   


#define OLED_SCLK_Clr() GPIO_ResetBits(SCLK_GPIO_PORT,SCLK_GPIO_PIN)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(SCLK_GPIO_PORT,SCLK_GPIO_PIN)

#define OLED_SDIN_Clr() GPIO_ResetBits(SDIN_GPIO_PORT,SDIN_GPIO_PIN)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(SDIN_GPIO_PORT,SDIN_GPIO_PIN)

#define OLED_RST_Clr()  GPIO_ResetBits(RST_GPIO_PORT,RST_GPIO_PIN)//RES
#define OLED_RST_Set()  GPIO_SetBits(RST_GPIO_PORT,RST_GPIO_PIN)

#define OLED_DC_Clr()   GPIO_ResetBits(DC_GPIO_PORT,DC_GPIO_PIN)//DC
#define OLED_DC_Set()   GPIO_SetBits(DC_GPIO_PORT,DC_GPIO_PIN)
 		     
#define OLED_CS_Clr()   GPIO_ResetBits(CS_GPIO_PORT,CS_GPIO_PIN)//CS
#define OLED_CS_Set()   GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//广播
extern u8 Oled_Colour;



//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void bsp_OLED_Init(void);
void OLED_ClearInit(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_FillAll(void);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size);   // size :1/2
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(u8 x,u8 y,const u8 *p,u8 p_w,u8 p_h);
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf,uint8_t size);
void OLED_Refresh_Gram(void);
void OLED_ShowChar32(u8 x,u8 y,u8 chr);
void OLED_ShowNum32(uint8_t x,uint8_t y,int num,uint8_t len);

void Oled_Show_NumCor(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf,uint8_t size,u8 color);
void OLED_ShowStringCor(u8 x,u8 y,u8 *chr,u8 size,u8 color);

#endif  


























