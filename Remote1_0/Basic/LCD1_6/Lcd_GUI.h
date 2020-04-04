//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/7/28
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
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
#ifndef _BSP_LCD_GUI_H_
#define _BSP_LCD_GUI_H_

#include "includes.h"

//bsp
u16 LCD_BGR2RGB(u16 c);
void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc);   //画圆
void Fill_Crcle(u16 X,u16 Y,u16 R,u16 fc);  //填充圆
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);  //画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);  //画矩形(非填充)
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color); //画矩形(填充)
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 color); //画三角形(非填充)
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 color); //画三角形(填充)
void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc);                        //在屏幕显示灰色矩形
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);                        //在屏幕显示灰色矩形
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);             //在屏幕显示一凸起的按钮框
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);               //在屏幕显示一凹下的按钮框
void Gui_DrawFont_GBK8(u16 x, u16 y, u16 fc, u16 bc, u8 *s);     //显示6*8字符或者英文  中 6*8
void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);    //显示8*16字符或者英文  中 16*136
void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);    //显示12*24字符或者英文  中 24*24
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ; //显示16*32数字        中 32*32
void LCD_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf, u16 fc, u16 bc,uint8_t scale);


#endif

