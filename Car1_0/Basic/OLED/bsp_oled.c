/**
  ******************************************************************************
  * @file    oled.c
  * @author  fire
  * @version V1.1
  * @date    2020-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
	* 功能描述   : OLED 4接口演示例程(32系列)
	*
	* GND    电源地
	* VCC    接 5V或3.3v电源
	* D0     接 SCL
	* D1     接 SDA
	* RES    接 RES
	* DC     接 DC
	* CS     接 CS (没有这个可以不接)
	*
	*
  ******************************************************************************
  */


#include "bsp_oled.h"
#include "stdlib.h"
#include "bsp_oledfont.h"  	 


//接口
#define Initdelay_ms DwtDelay_mS



uint8 Oled_Colour = 0;      //0  正   1  反


//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
volatile static u8 oledGram[X_WIDTH][Y_WIDTH/8];

#if OLED_MODE==1
/* SPI写入一个字节 */
void SPI_WByte(u8 TxData)
{
	/* 通过外设SPIx发送一个数据 */
	SPI_I2S_SendData(OLED_SPI, TxData);

	/* 检查指定的SPI标志位设置与否:发送缓存空标志位*/
	while (SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_TXE) == RESET);
}
//向SSD1306写入一个字节。（SPI模式）
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;	
void OLED_WR_Byte(u8 dat,u8 cmd)
{		  
	if(cmd)
	  OLED_DC_Set();  //写命令
	else 
	  OLED_DC_Clr();
	//OLED_CS_Clr();
	SPI_WByte(dat);	
	//OLED_CS_Set=();		  
	OLED_DC_Set(); 	  
}
#else
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
//	OLED_CS_Clr();
	
//	if(cmd==1 && Oled_Colour==1) dat = ~dat;    //数据颜色反转(没必要时可以删除)
	
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
//	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
#endif

#if OLED_SIZE == 0
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}  
#else
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte((((x+2)&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte(((x+2)&0x0f),OLED_CMD);  
}
#endif  
//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void oled_drawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)oledGram[x][pos]|=temp;
	else oledGram[x][pos]&=~temp;	    
}
//读点 
//x:0~127
//y:0~63
u8 oled_readPoint(u8 x,u8 y)
{
	u8 pos,bx,temp=0x00;
	//x = 127-x;
	y = 63-y;
	pos=y/8;
	bx=y%8;
	temp=1<<bx;
  if(temp&oledGram[x][pos]) return 1;
	return 0;
}

 
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			oledGram[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显?
}
void OLED_FillAll(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			oledGram[n][i]=0Xff;  
	OLED_Refresh_Gram();//更新显?
}

//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
		for(y=y1;y<=y2;y++)
			oled_drawPoint(x,y,dot);											    
//	oled_refreshGram();//更新显示
}

void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
#if OLED_SIZE == 0
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址  
#else
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址  
#endif
		for(n=0;n<128;n++)OLED_WR_Byte(oledGram[n][i],OLED_DATA); 
	}   
}


//在指定位置显示一个字符,包括部分字符
//x:0~127  
//y:0~63     1-7
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12    
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size)
{      	
	unsigned char c = 0,i = 0,j = 0;
	unsigned char temp;
	unsigned char temp1;
	unsigned char x0 = x;
	unsigned char y0 = y;
	switch(size)
	{
		case 1:
		{
			if(chr != '\0')
			{
				c = chr - 32;
				if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //翻转颜色
				else                  Oled_Colour = 0;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				for(i=0;i<6;i++)
				{
					temp = F6x8[c][i];
					for(j=0;j<8;j++)
					{
						if(temp&0x80)oled_drawPoint(x,y,!Oled_Colour);
						else         oled_drawPoint(x,y,Oled_Colour);
						temp<<=1;
						y++;
						if((y-y0)==8)
						{
							y=y0;
							x++;
							break;
						}
					}
				}
			}
		}break;
		case 2:
		{
			if(chr != '\0')
			{
				c = chr - 32;
				if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //翻转颜色
				else                        Oled_Colour = 0;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				for(i=0;i<8;i+=1)
				{
					temp  = F8X16[c*16+i];
					temp1 = F8X16[c*16+i+8];
					for(j=0;j<8;j++)
					{
						if(temp&0x80)oled_drawPoint(x,y,!Oled_Colour);
						else         oled_drawPoint(x,y,Oled_Colour);
						if(temp1&0x80)oled_drawPoint(x,y-8,!Oled_Colour);
						else         oled_drawPoint(x,y-8,Oled_Colour);
						temp<<=1;
						temp1<<=1;
						y++;
						if((y-y0)==8)
						{
							y=y0;
							x++;
							break;
						}
					}
				}
			}
		}break;
	}
}

void OLED_ShowChar32(u8 x,u8 y,u8 chr)
{      	
	unsigned char c = 0,i = 0;

	c = chr;
		if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //翻转颜色
		else                        Oled_Colour = 0;
		if(x > 120)
		{
			x = 0;
			y++;
		}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i],OLED_DATA);
		OLED_Set_Pos(x+8,y);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+8],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+16],OLED_DATA);
		OLED_Set_Pos(x+8,y+1);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+24],OLED_DATA);
		OLED_Set_Pos(x,y+2);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+32],OLED_DATA);
		OLED_Set_Pos(x+8,y+2);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+40],OLED_DATA);
		OLED_Set_Pos(x,y+3);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+48],OLED_DATA);
		OLED_Set_Pos(x+8,y+3);
		for(i=0;i<8;i++)
			OLED_WR_Byte(F16X32[c*64+i+56],OLED_DATA);

}


//m^n函数
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
//显示2个数字
//x,y :起点坐标	 
//len :整数数字的位数
//size:字体大小1/2
//lenf:0，整数，其它为小数
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf,uint8_t size)
{         
  
  float num1=num;//保护小数部分
	uint32 temp,num_i;
  long int num_f;
	uint8_t t,enshow=0;	
 
        
        
	// 负的还原成正
	if(num < 0)
	{
		OLED_ShowChar(x,y,'-',size);
		if(size == 1)  x= x+(size*6);
		else           x= x+(size*4);
		len=len-1;
		num=-num;
                num1=-num1;
	}
	        
	num_i = (int)num;
        
	for(t=0;t<len;t++)
	{
		temp=(num_i/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			  if(size == 1)
				       OLED_ShowChar(x+(size*6)*t,y,' ',size);
				else OLED_ShowChar(x+(size*4)*t,y,' ',size);
			
				continue;
			}else enshow=1; 
		 	 
		}
		if(size == 1)
				      OLED_ShowChar(x+(size*6)*t,y,temp+'0',size); 
				else OLED_ShowChar(x+(size*4)*t,y,temp+'0',size); 	 	
	}

	//如果有小数
	if(lenf != 0)
	{                   
          
          if(size == 1)
                  OLED_ShowChar(x+len*(size*6),y,'.',size);
          else    OLED_ShowChar(x+len*(size*4),y,'.',size);

#if 1
          num1 = num1 + 0.00001;
          num_f = (int)((num1-num_i)*mypow(10,lenf));
		
		 for(t=0;t<lenf;t++)
                {
                    temp=(num_f/mypow(10,lenf-t-1))%10;
                    if(t<(lenf))
                    {
                      if(temp!=0)
                      {
                              if(size == 1)
                                      OLED_ShowChar(x+(size*6)*(t+len+1),y,temp+'0',size);
                              else   OLED_ShowChar(x+(size*4)*(t+len+1),y,temp+'0',size);
                      }
                      else
                      {
                            if(size == 1)
                                  OLED_ShowChar(x+(size*6)*(t+len+1),y,'0',size); 
                            else  OLED_ShowChar(x+(size*4)*(t+len+1),y,'0',size); 	 
                      }
                    }
                        
                }
#endif
	}

} 

//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
//显示2个数字
//x,y :起点坐标	 
//len :整数数字的位数
//size:字体大小1/2
//lenf:0，整数，其它为小数
//num:数值(0~4294967295);	 		  
void OLED_ShowNum32(uint8_t x,uint8_t y,int num,uint8_t len)
{         
  
	uint32 temp;
	uint8_t t,enshow=0;	
 
        
        
	// 负的还原成正
	if(num < 0)
	{
		OLED_ShowChar32(x,y,11);
		x= x+16;
		len=len-1;
		num=-num;
	}
        
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			  OLED_ShowChar32(x+16*t,y,13);
			
				continue;
			}else enshow=1; 
		 	 
		}
		OLED_ShowChar32(x+16*t,y,temp); 	 	
	}
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
		  if(size == 2)
			   x+=8;                   //间距
			else
				x+=6;
		if(x>122){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	unsigned char t = 0;
	unsigned char j = 0;
	unsigned char temp;
	unsigned char temp1;
//	unsigned char x0 = x;
	unsigned char y0 = y;
	
	for(t=0;t<16;t++)
	{
		temp = Hzk[2*no+1][t];
		temp1  = Hzk[2*no][t];
		for(j=0;j<8;j++)
		{
			if(temp&0x80)oled_drawPoint(x,y,!Oled_Colour);
			else         oled_drawPoint(x,y,Oled_Colour);
			if(temp1&0x80)oled_drawPoint(x,y+8,!Oled_Colour);
			else         oled_drawPoint(x,y+8,Oled_Colour);
			temp<<=1;
			temp1<<=1;
			y++;
			if((y-y0)==8)
			{
				y=y0;
				x++;
				break;
			}
		}
	 }					
}

//显示图片
//x,y:起点坐标  
//p_w:图片宽（单位像素）
//p_h:图片高（单位像素）
//*p:图片起始地址 
void OLED_DrawBMP(u8 x,u8 y,const u8 *p,u8 p_w,u8 p_h)
{	
	u8 temp,i,col,row;
	u8 y0=y;
	u8 width=p_w;
	if(x+p_w>128)width=128-p_w;//实际显示宽度
	u8 high=p_h;
	if(y+p_h>64)high=64-p_h;//实际显示高度
	u8 exp_col_bytes=(p_h/8+((p_h%8)?1:0));//显示一列的字节数
	u8 act_col_bytes=(high/8+((high%8)?1:0));//实际显示一列的字节数
	
	for(row=0;row<width;row++)//列++
	{
		for(col=0;col<act_col_bytes;col++)//显示一列
		{   
			temp = p[col+row*exp_col_bytes];
			for(i=0;i<8;i++)
			{
				if(temp&0x80)oled_drawPoint(x,y,!Oled_Colour);
				else oled_drawPoint(x,y,Oled_Colour);
				temp<<=1;
				y++;
				if((y-y0)==high)
				{
					y=y0;
					x++;
					break;
				}		
			} 
		}
	}	
}



//初始化	    
void bsp_OLED_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCLK_InitStructure,
	                  GPIO_DC_InitStructure,
	                  GPIO_RST_InitStructure,
	                  GPIO_SDIN_InitStructure,
	                  GPIO_CS_InitStructure;
 	//GPIO_InitTypeDef  GPIO_CS_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(DC_GPIO_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_DC_InitStructure.GPIO_Pin = DC_GPIO_PIN;	 
 	GPIO_DC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_DC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(DC_GPIO_PORT, &GPIO_DC_InitStructure);	     //初始化GPIOX
	
	RCC_APB2PeriphClockCmd(RST_GPIO_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_RST_InitStructure.GPIO_Pin = RST_GPIO_PIN;	 
 	GPIO_RST_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_RST_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(RST_GPIO_PORT, &GPIO_RST_InitStructure);	     //初始化GPIOX
	
 	
// 	RCC_APB2PeriphClockCmd(CS_GPIO_CLK, ENABLE);	 //使能A端口时钟
//	GPIO_CS_InitStructure.GPIO_Pin = CS_GPIO_PIN;	 
// 	GPIO_CS_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_CS_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
// 	GPIO_Init(CS_GPIO_PORT, &GPIO_CS_InitStructure);	  //初始化GPIODX
	
	
	
#if OLED_MODE == 1
  SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	RCC_APB2PeriphClockCmd(SCLK_GPIO_CLK, ENABLE);	 //使能端口时钟	
	GPIO_SCLK_InitStructure.GPIO_Pin = SCLK_GPIO_PIN;	 
 	GPIO_SCLK_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
 	GPIO_Init(SCLK_GPIO_PORT, &GPIO_SCLK_InitStructure);	     //初始化GPIOX

	RCC_APB2PeriphClockCmd(SDIN_GPIO_CLK, ENABLE);	 //使能端口时钟
	GPIO_SDIN_InitStructure.GPIO_Pin = SDIN_GPIO_PIN;	 
 	GPIO_SDIN_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出
 	GPIO_Init(SDIN_GPIO_PORT, &GPIO_SDIN_InitStructure);	  //初始化GPIODX
	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	/* 设置SPI单向或者双向的数据模式 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		/* 设置SPI工作模式:设置为主SPI */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	/* 设置SPI的数据大小:SPI发送接收8位帧结构 */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;			/* 选择了串行时钟的稳态:时钟悬空低 */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		/* 数据捕获于第二个时钟沿 */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			/* NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制 */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	/* 定义波特率预分频的值:波特率预分频值为4 */
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	/* 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始 */
	SPI_InitStructure.SPI_CRCPolynomial = 0;			/* CRC值计算的多项式*/
	SPI_Init(OLED_SPI, &SPI_InitStructure); 				/* 根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器 */
 
	SPI_Cmd(OLED_SPI, ENABLE); /* 使能SPI外设 */

#else


 	RCC_APB2PeriphClockCmd(SCLK_GPIO_CLK, ENABLE);	 //使能C端口时钟	
	GPIO_SCLK_InitStructure.GPIO_Pin = SCLK_GPIO_PIN;	 
 	GPIO_SCLK_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SCLK_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //速度50MHz
 	GPIO_Init(SCLK_GPIO_PORT, &GPIO_SCLK_InitStructure);	     //初始化GPIOX

	RCC_APB2PeriphClockCmd(SDIN_GPIO_CLK, ENABLE);	 //使能C端口时钟
	GPIO_SDIN_InitStructure.GPIO_Pin = SDIN_GPIO_PIN;	 
 	GPIO_SDIN_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_SDIN_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(SDIN_GPIO_PORT, &GPIO_SDIN_InitStructure);	  //初始化GPIODX
	
#endif

	GPIO_SetBits(SCLK_GPIO_PORT,SCLK_GPIO_PIN);		
	GPIO_SetBits(SDIN_GPIO_PORT,SDIN_GPIO_PIN);
	GPIO_SetBits(DC_GPIO_PORT,DC_GPIO_PIN);	
	GPIO_SetBits(RST_GPIO_PORT,RST_GPIO_PIN);	
// 	GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN);	



	
	OLED_RST_Clr();
	Initdelay_ms(100);
	OLED_RST_Set(); 
			

#if OLED_SIZE == 0
  OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xEF,OLED_CMD); // Set SEG Output Current Brightness
#else
  OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
#endif
	
	
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  



























