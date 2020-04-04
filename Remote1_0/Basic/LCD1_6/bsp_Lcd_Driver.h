

#ifndef _BSP_LCD_DRIVER_H_
#define _BSP_LCD_DRIVER_H_

#include "includes.h"

//-------------------------��Ļ������������--------------------------------------//
#define LCD_X_SIZE	        130
#define LCD_Y_SIZE	        130

/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL  		0	//�����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.

#if USE_HORIZONTAL//��������˺��� 
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif
//////////////////////////////////////////////////////////////////////////////////
	 

//--------------------��ɫ����---------------------------------//
#define RED  		0xf800    //��ɫ
#define GREEN		0x07e0    //��ɫ
#define BLUE 		0x001f    //��ɫ
#define SBLUE 	0x251F    //����ɫ
#define WHITE		0xffff    //��ɫ
#define BLACK		0x0000    //��ɫ
#define YELLOW  0xFFE0    //��ɫ
#define GRAY0   0xEF7D   	//��ɫ0 1110 1111 0111 1100 
#define GRAY1   0x8410    //��ɫ1 1000 0100 0001 0000
#define GRAY2   0x4208    //��ɫ2 0100 0010 0000 1000



//ģ��SPI�ӿ�����
//*****************   IO��   **************************************************

//  LED ����
#define LCD_LED_GPIO_PORT       GPIOA			              /* GPIO�˿� */
#define LCD_LED_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LCD_LED_GPIO_PIN	      GPIO_Pin_15			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  SCL ʱ����
#define LCD_SCL_GPIO_PORT    	  GPIOA			              /* GPIO�˿� */
#define LCD_SCL_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LCD_SCL_GPIO_PIN		    GPIO_Pin_12			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  SDA ������
#define LCD_SDA_GPIO_PORT      	GPIOA			              /* GPIO�˿� */
#define LCD_SDA_GPIO_CLK 	      RCC_APB2Periph_GPIOA  	/* GPIO�˿�ʱ�� */
#define LCD_SDA_GPIO_PIN		    GPIO_Pin_11		        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  RS��A0 �� DS��
#define LCD_RS_GPIO_PORT        GPIOA			              /* GPIO�˿� */
#define LCD_RS_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LCD_RS_GPIO_PIN		      GPIO_Pin_10			        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  RST
#define LCD_RST_GPIO_PORT      	GPIOA			              /* GPIO�˿� */
#define LCD_RST_GPIO_CLK 	      RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LCD_RST_GPIO_PIN		    GPIO_Pin_9		        /* ���ӵ�SCLʱ���ߵ�GPIO */

//  CS
#define LCD_CS_GPIO_PORT      	GPIOA			              /* GPIO�˿� */
#define LCD_CS_GPIO_CLK 	      RCC_APB2Periph_GPIOA  	/* GPIO�˿�ʱ�� */
#define LCD_CS_GPIO_PIN		      GPIO_Pin_8		        /* ���ӵ�SCLʱ���ߵ�GPIO */



//Һ�����ƿ���1�������궨��
#define	LCD_CS_SET  	LCD_CS_GPIO_PORT->BSRR=LCD_CS_GPIO_PIN   
#define	LCD_RS_SET  	LCD_RS_GPIO_PORT->BSRR=LCD_RS_GPIO_PIN    
#define	LCD_SDA_SET  	LCD_SDA_GPIO_PORT->BSRR=LCD_SDA_GPIO_PIN    
#define	LCD_SCL_SET  	LCD_SCL_GPIO_PORT->BSRR=LCD_SCL_GPIO_PIN    
#define	LCD_RST_SET  	LCD_RST_GPIO_PORT->BSRR=LCD_RST_GPIO_PIN    
#define	LCD_LED_SET  	LCD_LED_GPIO_PORT->BSRR=LCD_LED_GPIO_PIN   

//Һ�����ƿ���0�������궨��
#define	LCD_CS_CLR  	LCD_CS_GPIO_PORT->BRR=LCD_CS_GPIO_PIN    
#define	LCD_RS_CLR  	LCD_RS_GPIO_PORT->BRR=LCD_RS_GPIO_PIN    
#define	LCD_SDA_CLR  	LCD_SDA_GPIO_PORT->BRR=LCD_SDA_GPIO_PIN    
#define	LCD_SCL_CLR  	LCD_SCL_GPIO_PORT->BRR=LCD_SCL_GPIO_PIN    
#define	LCD_RST_CLR  	LCD_RST_GPIO_PORT->BRR=LCD_RST_GPIO_PIN    
#define	LCD_LED_CLR  	LCD_LED_GPIO_PORT->BRR=LCD_LED_GPIO_PIN 


#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //�������
#define LCD_DATAIN     LCD_DATA->IDR;   //��������

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 


//˽������
void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);

void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
void Lcd_SetRegion(u8 x_start,u8 y_start,u8 x_end,u8 y_end);
void Lcd_WriteData_16Bit(u16 Data);

//��������
void Lcd_Reset(void);
void bsp_Lcd_Init(void);
void Lcd_Clear(u16 Color);


#endif
