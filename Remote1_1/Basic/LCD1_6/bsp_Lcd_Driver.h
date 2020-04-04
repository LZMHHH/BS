

#ifndef _BSP_LCD_DRIVER_H_
#define _BSP_LCD_DRIVER_H_

#include "includes.h"

//-------------------------屏幕物理像素设置--------------------------------------//
#define LCD_X_SIZE	        130
#define LCD_Y_SIZE	        130

/////////////////////////////////////用户配置区///////////////////////////////////	 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL  		0	//定义是否使用横屏 		0,不使用.1,使用.

#if USE_HORIZONTAL//如果定义了横屏 
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif
//////////////////////////////////////////////////////////////////////////////////
	 

//--------------------颜色定义---------------------------------//
#define RED  		0xf800    //红色
#define GREEN		0x07e0    //绿色
#define BLUE 		0x001f    //蓝色
#define SBLUE 	0x251F    //淡蓝色
#define WHITE		0xffff    //白色
#define BLACK		0x0000    //黑色
#define YELLOW  0xFFE0    //黄色
#define GRAY0   0xEF7D   	//灰色0 1110 1111 0111 1100 
#define GRAY1   0x8410    //灰色1 1000 0100 0001 0000
#define GRAY2   0x4208    //灰色2 0100 0010 0000 1000



//模拟SPI接口驱动
//*****************   IO口   **************************************************

//  LED 背光
#define LCD_LED_GPIO_PORT       GPIOA			              /* GPIO端口 */
#define LCD_LED_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LCD_LED_GPIO_PIN	      GPIO_Pin_15			        /* 连接到SCL时钟线的GPIO */

//  SCL 时钟线
#define LCD_SCL_GPIO_PORT    	  GPIOA			              /* GPIO端口 */
#define LCD_SCL_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LCD_SCL_GPIO_PIN		    GPIO_Pin_12			        /* 连接到SCL时钟线的GPIO */

//  SDA 数据线
#define LCD_SDA_GPIO_PORT      	GPIOA			              /* GPIO端口 */
#define LCD_SDA_GPIO_CLK 	      RCC_APB2Periph_GPIOA  	/* GPIO端口时钟 */
#define LCD_SDA_GPIO_PIN		    GPIO_Pin_11		        /* 连接到SCL时钟线的GPIO */

//  RS（A0 、 DS）
#define LCD_RS_GPIO_PORT        GPIOA			              /* GPIO端口 */
#define LCD_RS_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LCD_RS_GPIO_PIN		      GPIO_Pin_10			        /* 连接到SCL时钟线的GPIO */

//  RST
#define LCD_RST_GPIO_PORT      	GPIOA			              /* GPIO端口 */
#define LCD_RST_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define LCD_RST_GPIO_PIN		    GPIO_Pin_9		        /* 连接到SCL时钟线的GPIO */

//  CS
#define LCD_CS_GPIO_PORT      	GPIOA			              /* GPIO端口 */
#define LCD_CS_GPIO_CLK 	      RCC_APB2Periph_GPIOA  	/* GPIO端口时钟 */
#define LCD_CS_GPIO_PIN		      GPIO_Pin_8		        /* 连接到SCL时钟线的GPIO */



//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	LCD_CS_GPIO_PORT->BSRR=LCD_CS_GPIO_PIN   
#define	LCD_RS_SET  	LCD_RS_GPIO_PORT->BSRR=LCD_RS_GPIO_PIN    
#define	LCD_SDA_SET  	LCD_SDA_GPIO_PORT->BSRR=LCD_SDA_GPIO_PIN    
#define	LCD_SCL_SET  	LCD_SCL_GPIO_PORT->BSRR=LCD_SCL_GPIO_PIN    
#define	LCD_RST_SET  	LCD_RST_GPIO_PORT->BSRR=LCD_RST_GPIO_PIN    
#define	LCD_LED_SET  	LCD_LED_GPIO_PORT->BSRR=LCD_LED_GPIO_PIN   

//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	LCD_CS_GPIO_PORT->BRR=LCD_CS_GPIO_PIN    
#define	LCD_RS_CLR  	LCD_RS_GPIO_PORT->BRR=LCD_RS_GPIO_PIN    
#define	LCD_SDA_CLR  	LCD_SDA_GPIO_PORT->BRR=LCD_SDA_GPIO_PIN    
#define	LCD_SCL_CLR  	LCD_SCL_GPIO_PORT->BRR=LCD_SCL_GPIO_PIN    
#define	LCD_RST_CLR  	LCD_RST_GPIO_PORT->BRR=LCD_RST_GPIO_PIN    
#define	LCD_LED_CLR  	LCD_LED_GPIO_PORT->BRR=LCD_LED_GPIO_PIN 


#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 


//私有驱动
void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);

void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
void Lcd_SetRegion(u8 x_start,u8 y_start,u8 x_end,u8 y_end);
void Lcd_WriteData_16Bit(u16 Data);

//公有驱动
void Lcd_Reset(void);
void bsp_Lcd_Init(void);
void Lcd_Clear(u16 Color);


#endif
