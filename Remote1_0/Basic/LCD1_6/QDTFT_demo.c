
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
#include "Picture.h"
#include "QDTFT_demo.h"



unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

//******************************************************************
//函数名：  Redraw_Mainmenu
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    绘制测试菜单
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(16,2,BLUE,GRAY0,"全动电子技术");
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"液晶测试程序");

	DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,40,GREEN,GRAY0,"颜色填充测试");

	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"文字显示测试");

	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,100,RED,GRAY0,"图片显示测试");


	//Gui_DrawFont_GBK16(16,120,BLUE,GRAY0,"Welcome");
	//Gui_DrawFont_GBK16(16,140,RED,GRAY0, "Welcome");
}

//******************************************************************
//函数名：  Num_Test
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    测试数码管字体
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Num_Test(void)
{
	 OS_ERR      err;
	
	u8 i=0;
	/*Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);*/
	Lcd_Clear(GRAY0);

	for(i=0;i<9;i++)
	{
	Gui_DrawFont_Num32((i%3)*40,32*(i/3)+30,RED,GRAY0,Num[i+1]);
	//delay_ms(100);
	}
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	
}

//******************************************************************
//函数名：  Font_Test
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    中英文显示测试
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Font_Test(void)
{
	 OS_ERR      err;
	
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"文字显示测试");

	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,30,RED,GRAY0,"全动电子技术");
	Gui_DrawFont_GBK16(16,50,BLUE,GRAY0,"专注液晶批发");
	Gui_DrawFont_GBK16(16,70,RED,GRAY0, "全程技术支持");
	Gui_DrawFont_GBK16(0,100,BLUE,GRAY0,"Tel:15989313508");
	//Gui_DrawFont_GBK16(0,130,RED,GRAY0, "www.qdtech.net");	
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
}

//******************************************************************
//函数名：  Color_Test
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    简单刷屏测试
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Color_Test(void)
{
	 OS_ERR      err;
	
	u8 i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"颜色填充测试");
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态

	while(i--)
	{
		Lcd_Clear(WHITE); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
		Lcd_Clear(BLACK); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
		Lcd_Clear(RED);	  OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	  Lcd_Clear(GREEN); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	  Lcd_Clear(BLUE);  OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	}		
}

//******************************************************************
//函数名：  showimage
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    16位BMP显示图片（）
//          Image2LCD取模选项设置
//          水平扫描
//          16位
//          40X40
//          不包含图像头数据
//          自左至右
//          自顶至底
//          低位在前
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void showimage(const unsigned char *p) //显示40*40 QQ图片
{
	 OS_ERR      err;
	
  	int i,j,k; 
	unsigned char picH,picL; 
	Lcd_Clear(WHITE);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"图片显示测试");
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态

	Lcd_Clear(WHITE);
	for(j=0;j<3;j++)
	{
	   for(k=0;k<3;k++)	
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				Lcd_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}

//******************************************************************
//函数名：  QDTFT_Test_Demo
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    综合测试函数
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void QDTFT_Test_Demo(void)
{	
	OS_ERR      err;
	
	Redraw_Mainmenu();//绘制主菜单(部分内容由于分辨率超出物理值可能无法显示)
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	Color_Test();//简单纯色填充测试
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	Num_Test();//数码管字体测试

	Font_Test();//中英文显示测试		
	showimage(gImage_qq);//图片显示示例
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	Lcd_Histogram_UI();
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	Lcd_Stopwatch_UI();
	Lcd_modify_num();	
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
}

u16 color_Tab[5]={RED,GREEN,BLUE,YELLOW,BLACK};
u8* str[5]={"RED","GREEN","BLUE","YELLOW","BLACK"};

//******************************************************************
//函数名：  Lcd_Fill
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    全屏清屏函数
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Lcd_Fill(void)               
{	
   unsigned int i,m;
	u16 j;
	for(j=0;j<5;j++)
	{
		Lcd_SetRegion(0,0,220-1,176-1);
		Gui_DrawFont_GBK16(0,j*30,RED,WHITE,str[j]);	
   Lcd_SetRegion(50,j*30,220-1,j*30+20);
	

   for(i=0;i<220;i++)
    for(m=0;m<20;m++)
    {	
	  	Lcd_WriteData_16Bit(color_Tab[j]);
    }   
	}
}

//******************************************************************
//函数名：  Lcd_Histogram_UI
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    显示柱状图
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Lcd_Histogram_UI(void)
{
	Lcd_Clear(BLACK);
	Gui_DrawLine(30, 25,30, 110,WHITE);  
	Gui_DrawLine(30, 110,125, 110,WHITE);  
	LCD_DrawFillRectangle(40, 35, 55, 109,RED);
	LCD_DrawFillRectangle(70, 50, 85, 109,BLUE);
	LCD_DrawFillRectangle(100, 65, 115, 109,GREEN);
	LCD_DrawRectangle(40, 35, 55, 109,GRAY1);
	LCD_DrawRectangle(70, 50, 85, 109,GRAY1);
	LCD_DrawRectangle(100, 65, 115, 109,GRAY1);
	Gui_DrawFont_GBK16(21, 0, YELLOW, BLACK, "air quality");
	Gui_DrawFont_GBK8(0, 25, YELLOW, BLACK, "PM2.5");
	Gui_DrawFont_GBK8(0, 33, YELLOW, BLACK, "ug/m3");
	Gui_DrawFont_GBK8(40, 111, YELLOW, BLACK, "MAX");
	Gui_DrawFont_GBK8(72, 111, YELLOW, BLACK, "AV");
	Gui_DrawFont_GBK8(100, 111, YELLOW, BLACK, "MIN");
}

//******************************************************************
//函数名：  Lcd_Stopwatch_UI
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    显示时间界面
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Lcd_Stopwatch_UI(void)
{
	u16 i;
	Lcd_Clear(SBLUE);
	Gui_DrawFont_Num32(0,20,RED,SBLUE,2);
	Gui_DrawFont_Num32(26,20,RED,SBLUE,8);
	Gui_DrawFont_Num32(52,20,RED,SBLUE,11);
	Gui_DrawFont_Num32(74,20,RED,SBLUE,3);
	Gui_DrawFont_Num32(100,20,RED,SBLUE,6);
	for(i=0;i<18;i++)
	{
		Fill_Circle(23,90,18-i,GREEN+i*2);
	}
	for(i=0;i<18;i++)
	{
		Fill_Circle(63,90,18-i,YELLOW);
	}
	for(i=0;i<18;i++)
	{
		Fill_Circle(103,90,18-i,RED+i*3);
	}
	Fill_Triangel(18,80,35,90,18,100,GRAY2);
	LCD_DrawFillRectangle(57, 80, 60, 100,GRAY2); 
	LCD_DrawFillRectangle(66, 80, 69, 100,GRAY2); 
	LCD_DrawFillRectangle(93, 80, 113, 100,GRAY2); 
	Gui_Circle(23,90,18,GRAY2);
	Gui_Circle(63,90,18,GRAY2);
	Gui_Circle(103,90,18,GRAY2);
}

//******************************************************************
//函数名：  Lcd_modify_num
//作者：    xiao冯@全动电子
//日期：    2018-07-28
//功能：    修改时间参数
//输入参数：无
//返回值：  无
//修改记录：无
//****************************************************************** 
void Lcd_modify_num(void)
{
	OS_ERR      err;
	
	u16 i;
	srand(123456);
	for(i=0;i<30;i++)
	{
		Gui_DrawFont_Num32(0,20,RED,SBLUE, rand()%10);
		Gui_DrawFont_Num32(26,20,RED,SBLUE,rand()%10);
		Gui_DrawFont_Num32(74,20,RED,SBLUE,rand()%10);
		Gui_DrawFont_Num32(100,20,RED,SBLUE,rand()%10);
		OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //定时,并进入就绪状态
	}
}
