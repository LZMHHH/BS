#include "bsp_ws2812.h"


//ģ��spi
// д����λ
void RGB_LED_Write0(void)
{
    RGB_DI_Set();
    __nop();__nop();__nop();__nop();__nop();__nop();
    RGB_DI_Clr();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();
}
void RGB_LED_Write1(void)
{
    RGB_DI_Set();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();
    RGB_DI_Clr();
    __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
    __nop();__nop();
}
void Send_8bits(uint8_t dat) 
{
  uint8_t i=0;

  for (i=0;i<8;i++)
  {
    if((dat & 0x80)==0x80)
    {
		   RGB_LED_Write1();
    }
    else
    {
		   RGB_LED_Write0();
    }
    dat=dat<<1;
  }
	
}
//G--R--B
//MSB first	
void Send_2811_24bits(uint8_t RData,uint8_t GData,uint8_t BData)
{   
  Send_8bits(GData);  
  Send_8bits(RData); 
  Send_8bits(BData);
} 

void PixelUpdate(void)//should >24us
{
  uint8_t rst[24]={0};
  for(int i = 0 ;i < 24 ; i++)
  {
	 RGB_LED_Write0();
  }
}



uint8_t rBuffer[PIXEL_MAX]={0};
uint8_t gBuffer[PIXEL_MAX]={0};
uint8_t bBuffer[PIXEL_MAX]={0};
//����all led��ɫ
void SetAllLed(uint8_t r, uint8_t g, uint8_t b)
{ 
  uint8_t i=0;
  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=0;
    gBuffer[i]=0;
    bBuffer[i]=0;
  }
  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=r;
    gBuffer[i]=g;
    bBuffer[i]=b;
  }

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_2811_24bits(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
	PixelUpdate();
}
//����one led ��ɫ ���಻��
void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{	 
  uint8_t i=0;

  for(i=0;i<PIXEL_MAX;i++)
  {
    rBuffer[i]=0;
    gBuffer[i]=0;
    bBuffer[i]=0;
  }
  rBuffer[n]=r;
  gBuffer[n]=g;
  bBuffer[n]=b;
  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_2811_24bits(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
  PixelUpdate();
}
//set one led ��ɫ�����಻��
void SetOneLed(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{	 
  uint8_t i=0;

  rBuffer[n]=r;
  gBuffer[n]=g;
  bBuffer[n]=b;
  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_2811_24bits(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
  PixelUpdate();
}
void setPixelColor(uint16_t n, uint32_t c)
{	 
  uint8_t i=0;
	  
  rBuffer[n]=(uint8_t)(c>>16);
  gBuffer[n]=(uint8_t)(c>>8);
  bBuffer[n]=(uint8_t)c;

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_2811_24bits(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
   PixelUpdate();
}

void bsp_WS2812B_Init(void)//should >50us
{
	GPIO_InitTypeDef  GPIO_SCLK_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RGB_DI_GPIO_CLK, ENABLE);	 //ʹ�ܶ˿�ʱ��	
	GPIO_SCLK_InitStructure.GPIO_Pin = RGB_DI_GPIO_PIN;	 
 	GPIO_SCLK_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCLK_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(RGB_DI_GPIO_PORT, &GPIO_SCLK_InitStructure);	     //��ʼ��GPIOX

  uint8_t ResCode[50]={0};
  for(int i = 0 ;i < 50 ;i ++)
  {
	   RGB_LED_Write0();
  }
  //SetAllOneLed(255, 255, 255);
   DwtDelay_mS (50);
  SetAllLed(0, 0, 0);
   DwtDelay_mS (50);
}

//Ӧ�� ********************************************************
uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
uint32_t Wheel(uint8_t WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
//2��o?
void rainbow(uint8_t wait)
{
	OS_ERR      err;
  uint16_t i, j;
  
  for(j=0; j<256; j++) 
  {
    for(i=0; i<PIXEL_MAX; i++)
    {
      setPixelColor(i, Wheel((i+j) & 255));
    }
    PixelUpdate();
    OSTimeDly ( wait, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
	OS_ERR      err;
  uint16_t i, j;
  
  for(j=0; j<256*5; j++) 
  { // 5 cycles of all colors on wheel
    for(i=0; i< PIXEL_MAX; i++) 
    {
      setPixelColor(i, Wheel(((i * 256 / PIXEL_MAX) + j) & 255));
    }
    PixelUpdate();
      OSTimeDly ( wait, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
  }
}
//Theatre-style crawling lights.o??����?
void theaterChase(uint32_t c, uint8_t wait) 
{
	OS_ERR      err;
  for (int j=0; j<10; j++) 
  {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) 
    {
      for (uint16_t i=0; i < PIXEL_MAX; i=i+1)//turn every one pixel on
      {
        setPixelColor(i+q, c);    
      }
      PixelUpdate();
       OSTimeDly ( wait, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
      
      for (uint16_t i=0; i < PIXEL_MAX; i=i+1) //turn every one pixel off
      {
        setPixelColor(i+q, 0);        
      }
      PixelUpdate();
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
	OS_ERR      err;
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++)
    {
      for (uint16_t i=0; i < PIXEL_MAX; i=i+1) //turn every one pixel on
      {
        setPixelColor(i+q, Wheel( (i+j) % 255));    
      }
      PixelUpdate();
      
       OSTimeDly ( wait, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
      
      for (uint16_t i=0; i < PIXEL_MAX; i=i+1)//turn every one pixel off
      {
        setPixelColor(i+q, 0);        
      }
      PixelUpdate();
    }
  }
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
	OS_ERR      err;
  uint16_t i=0;
  for( i=0; i<PIXEL_MAX; i++) 
  {
    setPixelColor(i, c);
    PixelUpdate();
     OSTimeDly ( wait, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
  }
}

//light�ȼ� 0-8
void SetRGBLight(char light, uint8_t r, uint8_t g, uint8_t b)
{
	u8 i;

	for(i=0; i< PIXEL_MAX; i++)
	{
		if(i < light)
		{
			rBuffer[i]=r;
			gBuffer[i]=g;
			bBuffer[i]=b;
		}
		else
		{
			rBuffer[i]=0;
			gBuffer[i]=0;
			bBuffer[i]=0;
		}
	}
	for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_2811_24bits(rBuffer[i],gBuffer[i],bBuffer[i]);
  }
  PixelUpdate();

}





