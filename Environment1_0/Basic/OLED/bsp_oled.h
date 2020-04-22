/**
  ******************************************************************************
  * @file    oled.h
  * @author  fire
  * @version V1.1
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
	* GND    ��Դ��
	* VCC    �� 5V��3.3v��Դ
	* D0     �� SCL
	* D1     �� SDA
	* RES    �� RES
	* DC     �� DC
	* CS     �� CS (û�������������)
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

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_SPI   SPI2  //���ΪӲ��spiʱ��ѡ��SPI
#define OLED_MODE   0     //0�����spi  1��ΪӲ��spi 
#define SIZE        16
#define XLevelL		  0x00
#define XLevelH		  0x10
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xFF 
#define X_WIDTH 	  128
#define Y_WIDTH 	  64	    


//��һ�ֳߴ��oled
#define OLED_SIZE   1     //0:0.96     1:1.3


//*****************   IO��   **************************************************

//  CLK
#define SCLK_GPIO_PORT    	GPIOD			              /* GPIO�˿� */
#define SCLK_GPIO_CLK 	    RCC_APB2Periph_GPIOD		/* GPIO�˿�ʱ�� */
#define SCLK_GPIO_PIN		    GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  DIN / SDA
#define SDIN_GPIO_PORT    	GPIOC			              /* GPIO�˿� */
#define SDIN_GPIO_CLK 	    RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define SDIN_GPIO_PIN		    GPIO_Pin_12			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  RES
#define RST_GPIO_PORT      	GPIOC			              /* GPIO�˿� */
#define RST_GPIO_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define RST_GPIO_PIN		    GPIO_Pin_11		        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  DC
#define DC_GPIO_PORT    	  GPIOC 		              /* GPIO�˿� */
#define DC_GPIO_CLK 	      RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define DC_GPIO_PIN		      GPIO_Pin_10			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  CS
//#define CS_GPIO_PORT      	GPIOB 		              /* GPIO�˿� */
//#define CS_GPIO_CLK 	      RCC_APB2Periph_GPIOB  	/* GPIO�˿�ʱ�� */
//#define CS_GPIO_PIN		      GPIO_Pin_7		        /* ���ӵ�SCLʱ���ߵ�GPIO */

//-----------------����LED�˿ڶ���---------------- 
//#define LED_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_4)    
//#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_4)

//-----------------OLED�˿ڶ���----------------  					   


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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//�㲥
extern u8 Oled_Colour;



//OLED�����ú���
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


























