
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
#include "Picture.h"
#include "QDTFT_demo.h"



unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

//******************************************************************
//��������  Redraw_Mainmenu
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ���Ʋ��Բ˵�
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(16,2,BLUE,GRAY0,"ȫ�����Ӽ���");
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Һ�����Գ���");

	DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,40,GREEN,GRAY0,"��ɫ������");

	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"������ʾ����");

	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,100,RED,GRAY0,"ͼƬ��ʾ����");


	//Gui_DrawFont_GBK16(16,120,BLUE,GRAY0,"Welcome");
	//Gui_DrawFont_GBK16(16,140,RED,GRAY0, "Welcome");
}

//******************************************************************
//��������  Num_Test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    �������������
//�����������
//����ֵ��  ��
//�޸ļ�¼����
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
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	
}

//******************************************************************
//��������  Font_Test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ��Ӣ����ʾ����
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void Font_Test(void)
{
	 OS_ERR      err;
	
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"������ʾ����");

	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,30,RED,GRAY0,"ȫ�����Ӽ���");
	Gui_DrawFont_GBK16(16,50,BLUE,GRAY0,"רעҺ������");
	Gui_DrawFont_GBK16(16,70,RED,GRAY0, "ȫ�̼���֧��");
	Gui_DrawFont_GBK16(0,100,BLUE,GRAY0,"Tel:15989313508");
	//Gui_DrawFont_GBK16(0,130,RED,GRAY0, "www.qdtech.net");	
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
}

//******************************************************************
//��������  Color_Test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ��ˢ������
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void Color_Test(void)
{
	 OS_ERR      err;
	
	u8 i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"��ɫ������");
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬

	while(i--)
	{
		Lcd_Clear(WHITE); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
		Lcd_Clear(BLACK); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
		Lcd_Clear(RED);	  OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	  Lcd_Clear(GREEN); OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	  Lcd_Clear(BLUE);  OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	}		
}

//******************************************************************
//��������  showimage
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    16λBMP��ʾͼƬ����
//          Image2LCDȡģѡ������
//          ˮƽɨ��
//          16λ
//          40X40
//          ������ͼ��ͷ����
//          ��������
//          �Զ�����
//          ��λ��ǰ
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void showimage(const unsigned char *p) //��ʾ40*40 QQͼƬ
{
	 OS_ERR      err;
	
  	int i,j,k; 
	unsigned char picH,picL; 
	Lcd_Clear(WHITE);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"ͼƬ��ʾ����");
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬

	Lcd_Clear(WHITE);
	for(j=0;j<3;j++)
	{
	   for(k=0;k<3;k++)	
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				Lcd_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}

//******************************************************************
//��������  QDTFT_Test_Demo
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    �ۺϲ��Ժ���
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void QDTFT_Test_Demo(void)
{	
	OS_ERR      err;
	
	Redraw_Mainmenu();//�������˵�(�����������ڷֱ��ʳ�������ֵ�����޷���ʾ)
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	Color_Test();//�򵥴�ɫ������
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	Num_Test();//������������

	Font_Test();//��Ӣ����ʾ����		
	showimage(gImage_qq);//ͼƬ��ʾʾ��
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	Lcd_Histogram_UI();
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	Lcd_Stopwatch_UI();
	Lcd_modify_num();	
	OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
}

u16 color_Tab[5]={RED,GREEN,BLUE,YELLOW,BLACK};
u8* str[5]={"RED","GREEN","BLUE","YELLOW","BLACK"};

//******************************************************************
//��������  Lcd_Fill
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ȫ����������
//�����������
//����ֵ��  ��
//�޸ļ�¼����
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
//��������  Lcd_Histogram_UI
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ��ʾ��״ͼ
//�����������
//����ֵ��  ��
//�޸ļ�¼����
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
//��������  Lcd_Stopwatch_UI
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    ��ʾʱ�����
//�����������
//����ֵ��  ��
//�޸ļ�¼����
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
//��������  Lcd_modify_num
//���ߣ�    xiao��@ȫ������
//���ڣ�    2018-07-28
//���ܣ�    �޸�ʱ�����
//�����������
//����ֵ��  ��
//�޸ļ�¼����
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
		OSTimeDly ( 1000, OS_OPT_TIME_DLY, & err );   //��ʱ,���������״̬
	}
}
