
/****************************************************************************************************
//=========================================电源接线================================================//
//   液晶屏模块            STM32单片机
//      VCC        接       DC5V/3.3V      //电源
//      GND        接          GND         //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//   液晶屏模块            STM32单片机    
//      SDA        接          PB15        //SPI总线数据信号
//=======================================液晶屏控制线接线==========================================//
//   液晶屏模块 					 STM32单片机 
//      LED        接          PB9         //背光控制信号，如果不需要控制，接5V或3.3V
//      SCK        接          PB13        //SPI总线时钟信号
//    A0(RS/DC)    接          PB10        //数据/命令控制信号
//      RST        接          PB12        //复位控制信号
//      CS         接          PB11        //片选控制信号
//=========================================触摸屏触接线=========================================//
//本模块不带触摸功能，不需要进行触摸屏接线
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#ifndef __QDTFT_DEMO_H
#define __QDTFT_DEMO_H 

#include "includes.h"

void Redraw_Mainmenu(void);
void Num_Test(void);
void Font_Test(void);
void Color_Test(void);
void showimage(const unsigned char *p); 
void QDTFT_Test_Demo(void);
void Lcd_Histogram_UI(void);
void Lcd_Stopwatch_UI(void);
void Lcd_modify_num(void);
#endif
