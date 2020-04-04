
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
#include "bsp_Lcd_Driver.h"

/****************************************************************************
* 名    称：void LCD_GPIO_Init(void)
* 功    能：STM32_模拟SPI所用到的GPIO初始化
* 入口参数：无
* 出口参数：无
* 说    明：初始化模拟SPI所用的GPIO
****************************************************************************/
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;  
	
	RCC_APB2PeriphClockCmd( LCD_LED_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_LED_GPIO_PORT, &GPIO_InitStructure);     
	
	RCC_APB2PeriphClockCmd( LCD_SCL_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_SCL_GPIO_PORT, &GPIO_InitStructure);     
	
	RCC_APB2PeriphClockCmd( LCD_SDA_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_SDA_GPIO_PORT, &GPIO_InitStructure);     
	
	RCC_APB2PeriphClockCmd( LCD_RS_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_RS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure);     
	
	RCC_APB2PeriphClockCmd( LCD_RST_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_RST_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_RST_GPIO_PORT, &GPIO_InitStructure);     
	
	RCC_APB2PeriphClockCmd( LCD_CS_GPIO_CLK ,ENABLE);	
	GPIO_InitStructure.GPIO_Pin   = LCD_CS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);  

   
}

/****************************************************************************
* 名    称：void  SPIv_WriteData(u8 Data)
* 功    能：STM32_模拟SPI写一个字节数据底层函数
* 入口参数：Data
* 出口参数：无
* 说    明：STM32_模拟SPI读写一个字节数据底层函数
****************************************************************************/
void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
			LCD_SDA_SET; //输出数据
		else 
			LCD_SDA_CLR;	   
    LCD_SCL_CLR;       
    LCD_SCL_SET;
    Data<<=1; 
	}
}

/****************************************************************************
* 名    称：Lcd_WriteIndex(u8 Index)
* 功    能：向液晶屏写一个8位指令
* 入口参数：Index   寄存器地址
* 出口参数：无
* 说    明：调用前需先选中控制器，内部函数
****************************************************************************/
void Lcd_WriteIndex(u8 Index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   SPIv_WriteData(Index);
   LCD_CS_SET;
}

/****************************************************************************
* 名    称：Lcd_WriteData(u8 Data)
* 功    能：向液晶屏写一个8位数据
* 入口参数：dat     寄存器数据
* 出口参数：无
* 说    明：向控制器指定地址写入数据，内部函数
****************************************************************************/
void Lcd_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPIv_WriteData(Data);
   LCD_CS_SET;
}

/****************************************************************************
* 名    称：void LCD_WriteReg(u8 Index,u16 Data)
* 功    能：写寄存器数据
* 入口参数：Index,Data
* 出口参数：无
* 说    明：本函数为组合函数，向Index地址的寄存器写入Data值
****************************************************************************/
void LCD_WriteReg(u8 Index,u16 Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData_16Bit(Data);
}

/****************************************************************************
* 名    称：void Lcd_WriteData_16Bit(u16 Data)
* 功    能：向液晶屏写一个16位数据
* 入口参数：Data
* 出口参数：无
* 说    明：向控制器指定地址写入一个16位数据
****************************************************************************/
void Lcd_WriteData_16Bit(u16 Data)
{	
	 LCD_CS_CLR;
   LCD_RS_SET;
   SPIv_WriteData(Data>>8);
	 SPIv_WriteData(Data);
   LCD_CS_SET;
	//delay_us(100);
}
void Write_WDR(u8 Index,u16 Data)
{
Lcd_WriteIndex(Index);
Lcd_WriteData_16Bit(Data);
}
/****************************************************************************
* 名    称：void Lcd_Reset(void)
* 功    能：液晶硬复位函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	DwtDelay_mS(100);
	LCD_RST_SET;
	DwtDelay_mS(50);
	
}
/****************************************************************************
* 名    称：void Lcd_Init(void)
* 功    能：液晶初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化_ILI9225_176X220
****************************************************************************/
void bsp_Lcd_Init(void)
{	
	LCD_GPIO_Init();//使用模拟SPI
	Lcd_Reset(); //Reset before LCD Init.
	LCD_LED_SET;
	Write_WDR(0x10,0x2F8E); /* power control 1 */
	Write_WDR(0x11,0x000C); /* power control 2 */
  Write_WDR(0x07,0x0021); /* display control */
  Write_WDR(0x28,0x0006); /* vcom OTP */
  Write_WDR(0x28,0x0005);
  Write_WDR(0x27,0x057F); /* further bias current setting */
  Write_WDR(0x29,0x89A1); /* vcom OTP */
  Write_WDR(0x00,0x0001); /* OSC en */
  DwtDelay_mS(100);
  Write_WDR(0x29,0x80B0); /* vcom OTP */
  DwtDelay_mS(30);
  Write_WDR(0x29,0xFFFE); /* vcom OTP */
  Write_WDR(0x07,0x0023); /* display control */
  DwtDelay_mS(30);
  Write_WDR(0x07,0x0033); /* display control */
#if USE_HORIZONTAL
  Write_WDR(0x01,0x2283); /* driver output control, REV, TB=0, RL=1, RGB */
  Write_WDR(0x03,0x6838); /* entry mode, 65K, ram, ID3 */
#else
  Write_WDR(0x01,0x2183); /* driver output control, REV, TB, RGB */
  Write_WDR(0x03,0x6830); /* entry mode, 65K, ram, ID0 */
#endif
  Write_WDR(0x2F,0xFFFF); /* 2A ~ 2F, test */
  Write_WDR(0x2C,0x8000);
  Write_WDR(0x27,0x0570);
  Write_WDR(0x02,0x0300); /* driving wave form control */
  Write_WDR(0x0B,0x580C); /* frame cycle control */
  Write_WDR(0x12,0x0609); /* power control 3 */
  Write_WDR(0x13,0x3100); /* power control 4 */
	Lcd_Clear(BLACK);
}



/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(u16 Xpos, u16 Ypos)
{	
#if USE_HORIZONTAL//如果定义了横屏	
	Lcd_WriteIndex(0x21);
	Lcd_WriteData(Xpos);
	Lcd_WriteData(Ypos+2);	
#else//竖屏	
		Lcd_WriteIndex(0x21);
	Lcd_WriteData(Ypos+2);
	Lcd_WriteData(Xpos+2);	
#endif
	Lcd_WriteIndex(0x22);	

} 
/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
//设置显示窗口
void Lcd_SetRegion(u8 xStar, u8 yStar,u8 xEnd,u8 yEnd)
{
	
#if USE_HORIZONTAL//如果定义了横屏	
	Lcd_WriteIndex(0x45);
	Lcd_WriteData(xEnd);
	Lcd_WriteData(xStar);	
	
	Lcd_WriteIndex(0x44);
	Lcd_WriteData(yEnd+2);
	Lcd_WriteData(yStar+2);	

#else//竖屏	
		Lcd_WriteIndex(0x44);
	Lcd_WriteData(xEnd+2);
	Lcd_WriteData(xStar+2);	
	
	Lcd_WriteIndex(0x45);
	Lcd_WriteData(yEnd+2);
	Lcd_WriteData(yStar+2);	

#endif

	Lcd_SetXY(xStar,yStar);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：xy坐标和颜色数据
返回值：无
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);

}    

/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(u16 Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	Lcd_WriteData_16Bit(Color);
    }   
}



