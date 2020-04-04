
#ifndef _WS2812_H
#define _WS2812_H

#include "includes.h"

//灯数
#define PIXEL_MAX 8


//*****************   IO口   **************************************************

//  RGB_DI
#define RGB_DI_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define RGB_DI_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define RGB_DI_GPIO_PIN		    GPIO_Pin_8			        /* 连接到SCL时钟线的GPIO */



//-----------------OLED端口定义----------------  					   
#define RGB_DI_Clr() GPIO_ResetBits(RGB_DI_GPIO_PORT,RGB_DI_GPIO_PIN)//CLK
#define RGB_DI_Set() GPIO_SetBits(RGB_DI_GPIO_PORT,RGB_DI_GPIO_PIN)


//私有驱动
void Send_8bits(uint8_t dat);
void Send_2811_24bits(uint8_t GData,uint8_t RData,uint8_t BData);
void PixelUpdate(void);


//公有驱动
void bsp_WS2812B_Init(void);    
void SetAllLed(uint8_t r, uint8_t g, uint8_t b);   //设置所有灯的颜色
void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b); //设置单灯灯色
void SetOneLed(uint16_t n, uint8_t r, uint8_t g, uint8_t b);     //set one led 颜色，其余不变
void setPixelColor(uint16_t n, uint32_t c);
void SetRGBLight(char light, uint8_t r, uint8_t g, uint8_t b);

//应用
uint32_t Wheel(uint8_t WheelPos);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);              //爬行
void theaterChase(uint32_t c, uint8_t wait);  //追击
void theaterChaseRainbow(uint8_t wait) ;      //追击彩虹
void colorWipe(uint32_t c, uint8_t wait);

#endif // ADAFRUIT_NEOPIXEL_H
