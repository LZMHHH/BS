/**
  ******************************************************************************
  * @file    bsp_oled.c
  * @author  fire
  * @version V1.1
  * @date    2020-xx-xx
  * @brief   I/OÏßÖĞ¶ÏÓ¦ÓÃbsp
  ******************************************************************************
  * @attention
  *
  * ÊµÑéÆ½Ì¨:Ë«´´ÊµÑéÊÒ-LZM
  * 
  * Wechat£ºqabc132321
  *
	* ¹¦ÄÜÃèÊö   : OLED 4½Ó¿ÚÑİÊ¾Àı³Ì(32ÏµÁĞ)
	*
	* GND    µçÔ´µØ
	* VCC    ½Ó 5V»ò3.3vµçÔ´
	* D0     ½Ó SCL
	* D1     ½Ó SDA
	* RES    ½Ó RES
	* DC     ½Ó DC
	* CS     ½Ó CS (Ã»ÓĞÕâ¸ö¿ÉÒÔ²»½Ó)
	*
	*
  ******************************************************************************
  */


#include "bsp_oled.h"
#include "stdlib.h"
#include "bsp_oledfont.h"  	 


//½Ó¿Ú
#define Initdelay_ms DwtDelay_mS



uint8 Oled_Colour = 0;      //0  Õı   1  ·´


//OLEDµÄÏÔ´æ
//´æ·Å¸ñÊ½ÈçÏÂ.
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
/* SPIĞ´ÈëÒ»¸ö×Ö½Ú */
void SPI_WByte(u8 TxData)
{
	/* Í¨¹ıÍâÉèSPIx·¢ËÍÒ»¸öÊı¾İ */
	SPI_I2S_SendData(OLED_SPI, TxData);

	/* ¼ì²éÖ¸¶¨µÄSPI±êÖ¾Î»ÉèÖÃÓë·ñ:·¢ËÍ»º´æ¿Õ±êÖ¾Î»*/
	while (SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_TXE) == RESET);
}
//ÏòSSD1306Ğ´ÈëÒ»¸ö×Ö½Ú¡££¨SPIÄ£Ê½£©
//dat:ÒªĞ´ÈëµÄÊı¾İ/ÃüÁî
//cmd:Êı¾İ/ÃüÁî±êÖ¾ 0,±íÊ¾ÃüÁî;1,±íÊ¾Êı¾İ;	
void OLED_WR_Byte(u8 dat,u8 cmd)
{		  
	if(cmd)
	  OLED_DC_Set();  //Ğ´ÃüÁî
	else 
	  OLED_DC_Clr();
	//OLED_CS_Clr();
	SPI_WByte(dat);	
	//OLED_CS_Set=();		  
	OLED_DC_Set(); 	  
}
#else
//ÏòSSD1106Ğ´ÈëÒ»¸ö×Ö½Ú¡£
//dat:ÒªĞ´ÈëµÄÊı¾İ/ÃüÁî
//cmd:Êı¾İ/ÃüÁî±êÖ¾ 0,±íÊ¾ÃüÁî;1,±íÊ¾Êı¾İ;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
//	OLED_CS_Clr();
	
//	if(cmd==1 && Oled_Colour==1) dat = ~dat;    //Êı¾İÑÕÉ«·´×ª(Ã»±ØÒªÊ±¿ÉÒÔÉ¾³ı)
	
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
//»­µã 
//x:0~127
//y:0~63
//t:1 Ìî³ä 0,Çå¿Õ				   
void oled_drawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//³¬³ö·¶Î§ÁË.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)oledGram[x][pos]|=temp;
	else oledGram[x][pos]&=~temp;	    
}
//¶Áµã 
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

 
//¿ªÆôOLEDÏÔÊ¾    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//¹Ø±ÕOLEDÏÔÊ¾     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

//ÇåÆÁº¯Êı,ÇåÍêÆÁ,Õû¸öÆÁÄ»ÊÇºÚÉ«µÄ!ºÍÃ»µãÁÁÒ»Ñù!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			oledGram[n][i]=0X00;  
	OLED_Refresh_Gram();//¸üĞÂÏÔÊ
}
void OLED_FillAll(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			oledGram[n][i]=0Xff;  
	OLED_Refresh_Gram();//¸üĞÂÏÔÊ
}

//x1,y1,x2,y2 Ìî³äÇøÓòµÄ¶Ô½Ç×ø±ê
//È·±£x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,Çå¿Õ;1,Ìî³ä	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
		for(y=y1;y<=y2;y++)
			oled_drawPoint(x,y,dot);											    
//	oled_refreshGram();//¸üĞÂÏÔÊ¾
}

void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
#if OLED_SIZE == 0
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞ¸ßµØÖ·  
#else
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x02,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁĞ¸ßµØÖ·  
#endif
		for(n=0;n<128;n++)OLED_WR_Byte(oledGram[n][i],OLED_DATA); 
	}   
}


//ÔÚÖ¸¶¨Î»ÖÃÏÔÊ¾Ò»¸ö×Ö·û,°üÀ¨²¿·Ö×Ö·û
//x:0~127  
//y:0~63     1-7
//mode:0,·´°×ÏÔÊ¾;1,Õı³£ÏÔÊ¾				 
//size:Ñ¡Ôñ×ÖÌå 16/12    
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
				if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //·­×ªÑÕÉ«
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
				if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //·­×ªÑÕÉ«
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
		if(Oled_Colour==1 && c>=0)  Oled_Colour = 1;    //·­×ªÑÕÉ«
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


//m^nº¯Êı
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

//ÏÔÊ¾2¸öÊı×Ö
//x,y :Æğµã×ø±ê	 
//len :Êı×ÖµÄÎ»Êı
//size:×ÖÌå´óĞ¡
//mode:Ä£Ê½	0,Ìî³äÄ£Ê½;1,µş¼ÓÄ£Ê½
//num:ÊıÖµ(0~4294967295);	 		  
//ÏÔÊ¾2¸öÊı×Ö
//x,y :Æğµã×ø±ê	 
//len :ÕûÊıÊı×ÖµÄÎ»Êı
//size:×ÖÌå´óĞ¡1/2
//lenf:0£¬ÕûÊı£¬ÆäËüÎªĞ¡Êı
//num:ÊıÖµ(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf,uint8_t size)
{         
  
  float num1=num;//±£»¤Ğ¡Êı²¿·Ö
	uint32 temp,num_i;
  long int num_f;
	uint8_t t,enshow=0;	
 
        
        
	// ¸ºµÄ»¹Ô­³ÉÕı
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

	//Èç¹ûÓĞĞ¡Êı
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

//ÏÔÊ¾2¸öÊı×Ö
//x,y :Æğµã×ø±ê	 
//len :Êı×ÖµÄÎ»Êı
//size:×ÖÌå´óĞ¡
//mode:Ä£Ê½	0,Ìî³äÄ£Ê½;1,µş¼ÓÄ£Ê½
//num:ÊıÖµ(0~4294967295);	 		  
//ÏÔÊ¾2¸öÊı×Ö
//x,y :Æğµã×ø±ê	 
//len :ÕûÊıÊı×ÖµÄÎ»Êı
//size:×ÖÌå´óĞ¡1/2
//lenf:0£¬ÕûÊı£¬ÆäËüÎªĞ¡Êı
//num:ÊıÖµ(0~4294967295);	 		  
void OLED_ShowNum32(uint8_t x,uint8_t y,int num,uint8_t len)
{         
  
	uint32 temp;
	uint8_t t,enshow=0;	
 
        
        
	// ¸ºµÄ»¹Ô­³ÉÕı
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
//ÏÔÊ¾Ò»¸ö×Ö·ûºÅ´®
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
		  if(size == 2)
			   x+=8;                   //¼ä¾à
			else
				x+=6;
		if(x>122){x=0;y+=2;}
			j++;
	}
}
//ÏÔÊ¾ºº×Ö
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

//ÏÔÊ¾Í¼Æ¬
//x,y:Æğµã×ø±ê  
//p_w:Í¼Æ¬¿í£¨µ¥Î»ÏñËØ£©
//p_h:Í¼Æ¬¸ß£¨µ¥Î»ÏñËØ£©
//*p:Í¼Æ¬ÆğÊ¼µØÖ· 
void OLED_DrawBMP(u8 x,u8 y,const u8 *p,u8 p_w,u8 p_h)
{	
	u8 temp,i,col,row;
	u8 y0=y;
	u8 width=p_w;
	if(x+p_w>128)width=128-p_w;//Êµ¼ÊÏÔÊ¾¿í¶È
	u8 high=p_h;
	if(y+p_h>64)high=64-p_h;//Êµ¼ÊÏÔÊ¾¸ß¶È
	u8 exp_col_bytes=(p_h/8+((p_h%8)?1:0));//ÏÔÊ¾Ò»ÁĞµÄ×Ö½ÚÊı
	u8 act_col_bytes=(high/8+((high%8)?1:0));//Êµ¼ÊÏÔÊ¾Ò»ÁĞµÄ×Ö½ÚÊı
	
	for(row=0;row<width;row++)//ÁĞ++
	{
		for(col=0;col<act_col_bytes;col++)//ÏÔÊ¾Ò»ÁĞ
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



//³õÊ¼»¯	    
void bsp_OLED_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCLK_InitStructure,
	                  GPIO_DC_InitStructure,
	                  GPIO_RST_InitStructure,
	                  GPIO_SDIN_InitStructure,
	                  GPIO_CS_InitStructure;
 	//GPIO_InitTypeDef  GPIO_CS_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(DC_GPIO_CLK, ENABLE);	 //Ê¹ÄÜC¶Ë¿ÚÊ±ÖÓ	
	GPIO_DC_InitStructure.GPIO_Pin = DC_GPIO_PIN;	 
 	GPIO_DC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_DC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //ËÙ¶È50MHz
 	GPIO_Init(DC_GPIO_PORT, &GPIO_DC_InitStructure);	     //³õÊ¼»¯GPIOX
	
	RCC_APB2PeriphClockCmd(RST_GPIO_CLK, ENABLE);	 //Ê¹ÄÜC¶Ë¿ÚÊ±ÖÓ	
	GPIO_RST_InitStructure.GPIO_Pin = RST_GPIO_PIN;	 
 	GPIO_RST_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_RST_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //ËÙ¶È50MHz
 	GPIO_Init(RST_GPIO_PORT, &GPIO_RST_InitStructure);	     //³õÊ¼»¯GPIOX
	
 	
// 	RCC_APB2PeriphClockCmd(CS_GPIO_CLK, ENABLE);	 //Ê¹ÄÜA¶Ë¿ÚÊ±ÖÓ
//	GPIO_CS_InitStructure.GPIO_Pin = CS_GPIO_PIN;	 
// 	GPIO_CS_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
//	GPIO_CS_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
// 	GPIO_Init(CS_GPIO_PORT, &GPIO_CS_InitStructure);	  //³õÊ¼»¯GPIODX
	
	
	
#if OLED_MODE == 1
  SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	RCC_APB2PeriphClockCmd(SCLK_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ	
	GPIO_SCLK_InitStructure.GPIO_Pin = SCLK_GPIO_PIN;	 
 	GPIO_SCLK_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
 	GPIO_Init(SCLK_GPIO_PORT, &GPIO_SCLK_InitStructure);	     //³õÊ¼»¯GPIOX

	RCC_APB2PeriphClockCmd(SDIN_GPIO_CLK, ENABLE);	 //Ê¹ÄÜ¶Ë¿ÚÊ±ÖÓ
	GPIO_SDIN_InitStructure.GPIO_Pin = SDIN_GPIO_PIN;	 
 	GPIO_SDIN_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //¸´ÓÃÍÆÍìÊä³ö
 	GPIO_Init(SDIN_GPIO_PORT, &GPIO_SDIN_InitStructure);	  //³õÊ¼»¯GPIODX
	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	/* ÉèÖÃSPIµ¥Ïò»òÕßË«ÏòµÄÊı¾İÄ£Ê½ */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		/* ÉèÖÃSPI¹¤×÷Ä£Ê½:ÉèÖÃÎªÖ÷SPI */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	/* ÉèÖÃSPIµÄÊı¾İ´óĞ¡:SPI·¢ËÍ½ÓÊÕ8Î»Ö¡½á¹¹ */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;			/* Ñ¡ÔñÁË´®ĞĞÊ±ÖÓµÄÎÈÌ¬:Ê±ÖÓĞü¿ÕµÍ */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;		/* Êı¾İ²¶»ñÓÚµÚ¶ş¸öÊ±ÖÓÑØ */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			/* NSSĞÅºÅÓÉÓ²¼ş£¨NSS¹Ü½Å£©»¹ÊÇÈí¼ş£¨Ê¹ÓÃSSIÎ»£©¹ÜÀí:ÄÚ²¿NSSĞÅºÅÓĞSSIÎ»¿ØÖÆ */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	/* ¶¨Òå²¨ÌØÂÊÔ¤·ÖÆµµÄÖµ:²¨ÌØÂÊÔ¤·ÖÆµÖµÎª4 */
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	/* Ö¸¶¨Êı¾İ´«Êä´ÓMSBÎ»»¹ÊÇLSBÎ»¿ªÊ¼:Êı¾İ´«Êä´ÓMSBÎ»¿ªÊ¼ */
	SPI_InitStructure.SPI_CRCPolynomial = 0;			/* CRCÖµ¼ÆËãµÄ¶àÏîÊ½*/
	SPI_Init(OLED_SPI, &SPI_InitStructure); 				/* ¸ù¾İSPI_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèSPIx¼Ä´æÆ÷ */
 
	SPI_Cmd(OLED_SPI, ENABLE); /* Ê¹ÄÜSPIÍâÉè */

#else


 	RCC_APB2PeriphClockCmd(SCLK_GPIO_CLK, ENABLE);	 //Ê¹ÄÜC¶Ë¿ÚÊ±ÖÓ	
	GPIO_SCLK_InitStructure.GPIO_Pin = SCLK_GPIO_PIN;	 
 	GPIO_SCLK_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_SCLK_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //ËÙ¶È50MHz
 	GPIO_Init(SCLK_GPIO_PORT, &GPIO_SCLK_InitStructure);	     //³õÊ¼»¯GPIOX

	RCC_APB2PeriphClockCmd(SDIN_GPIO_CLK, ENABLE);	 //Ê¹ÄÜC¶Ë¿ÚÊ±ÖÓ
	GPIO_SDIN_InitStructure.GPIO_Pin = SDIN_GPIO_PIN;	 
 	GPIO_SDIN_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_SDIN_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(SDIN_GPIO_PORT, &GPIO_SDIN_InitStructure);	  //³õÊ¼»¯GPIODX
	
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
	
	
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0×óÓÒ·´ÖÃ 0xa1Õı³£
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0ÉÏÏÂ·´ÖÃ 0xc8Õı³£
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




/* ¶ş´Î¿ª·¢ */
void Oled_Show_NumCor(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t lenf,uint8_t size,u8 color)
{
	Oled_Colour = color;
	OLED_ShowNum(x,y,num,len,lenf,size);
	Oled_Colour = 0;
}
void OLED_ShowStringCor(u8 x,u8 y,u8 *chr,u8 size,u8 color)
{
	Oled_Colour = color;
	OLED_ShowString(x,y,chr,size);
	Oled_Colour = 0;
}



















