
/****************************************************************************************************
//=========================================��Դ����================================================//
//   Һ����ģ��            STM32��Ƭ��
//      VCC        ��       DC5V/3.3V      //��Դ
//      GND        ��          GND         //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//   Һ����ģ��            STM32��Ƭ��    
//      SDA        ��          PB15        //SPI���������ź�
//=======================================Һ���������߽���==========================================//
//   Һ����ģ�� 					 STM32��Ƭ�� 
//      LED        ��          PB9         //��������źţ��������Ҫ���ƣ���5V��3.3V
//      SCK        ��          PB13        //SPI����ʱ���ź�
//    A0(RS/DC)    ��          PB10        //����/��������ź�
//      RST        ��          PB12        //��λ�����ź�
//      CS         ��          PB11        //Ƭѡ�����ź�
//=========================================������������=========================================//
//��ģ�鲻���������ܣ�����Ҫ���д���������
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
