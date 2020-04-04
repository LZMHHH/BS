
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
#include "bsp_Lcd_Driver.h"

/****************************************************************************
* ��    �ƣ�void LCD_GPIO_Init(void)
* ��    �ܣ�STM32_ģ��SPI���õ���GPIO��ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵    ������ʼ��ģ��SPI���õ�GPIO
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
* ��    �ƣ�void  SPIv_WriteData(u8 Data)
* ��    �ܣ�STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
* ��ڲ�����Data
* ���ڲ�������
* ˵    ����STM32_ģ��SPI��дһ���ֽ����ݵײ㺯��
****************************************************************************/
void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
			LCD_SDA_SET; //�������
		else 
			LCD_SDA_CLR;	   
    LCD_SCL_CLR;       
    LCD_SCL_SET;
    Data<<=1; 
	}
}

/****************************************************************************
* ��    �ƣ�Lcd_WriteIndex(u8 Index)
* ��    �ܣ���Һ����дһ��8λָ��
* ��ڲ�����Index   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
****************************************************************************/
void Lcd_WriteIndex(u8 Index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   SPIv_WriteData(Index);
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�Lcd_WriteData(u8 Data)
* ��    �ܣ���Һ����дһ��8λ����
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ��ڲ�����
****************************************************************************/
void Lcd_WriteData(u8 Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPIv_WriteData(Data);
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�void LCD_WriteReg(u8 Index,u16 Data)
* ��    �ܣ�д�Ĵ�������
* ��ڲ�����Index,Data
* ���ڲ�������
* ˵    ����������Ϊ��Ϻ�������Index��ַ�ļĴ���д��Dataֵ
****************************************************************************/
void LCD_WriteReg(u8 Index,u16 Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData_16Bit(Data);
}

/****************************************************************************
* ��    �ƣ�void Lcd_WriteData_16Bit(u16 Data)
* ��    �ܣ���Һ����дһ��16λ����
* ��ڲ�����Data
* ���ڲ�������
* ˵    �����������ָ����ַд��һ��16λ����
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
* ��    �ƣ�void Lcd_Reset(void)
* ��    �ܣ�Һ��Ӳ��λ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	DwtDelay_mS(100);
	LCD_RST_SET;
	DwtDelay_mS(50);
	
}
/****************************************************************************
* ��    �ƣ�void Lcd_Init(void)
* ��    �ܣ�Һ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��_ILI9225_176X220
****************************************************************************/
void bsp_Lcd_Init(void)
{	
	LCD_GPIO_Init();//ʹ��ģ��SPI
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
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(u16 Xpos, u16 Ypos)
{	
#if USE_HORIZONTAL//��������˺���	
	Lcd_WriteIndex(0x21);
	Lcd_WriteData(Xpos);
	Lcd_WriteData(Ypos+2);	
#else//����	
		Lcd_WriteIndex(0x21);
	Lcd_WriteData(Ypos+2);
	Lcd_WriteData(Xpos+2);	
#endif
	Lcd_WriteIndex(0x22);	

} 
/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
//������ʾ����
void Lcd_SetRegion(u8 xStar, u8 yStar,u8 xEnd,u8 yEnd)
{
	
#if USE_HORIZONTAL//��������˺���	
	Lcd_WriteIndex(0x45);
	Lcd_WriteData(xEnd);
	Lcd_WriteData(xStar);	
	
	Lcd_WriteIndex(0x44);
	Lcd_WriteData(yEnd+2);
	Lcd_WriteData(yStar+2);	

#else//����	
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
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�����xy�������ɫ����
����ֵ����
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);

}    

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
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



