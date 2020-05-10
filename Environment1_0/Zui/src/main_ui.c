/**
  ******************************************************************************
  * @file    main_ui.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ui显示文件：主模式
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */

#include "main_ui.h"


CLASS_UIconfigParam Main_uiconfigParam;

void Main_uiconfigParamInit(void)
{
	Main_uiconfigParam.Page_Index_Limit    = 5;
	
	Main_uiconfigParam.Para_Index_Limit[0] = 7;
	Main_uiconfigParam.Para_Index_Limit[1] = 12;
	Main_uiconfigParam.Para_Index_Limit[2] = 16;
	Main_uiconfigParam.Para_Index_Limit[3] = 6;
	Main_uiconfigParam.Para_Index_Limit[4] = 8;
	Main_uiconfigParam.Para_Index_Limit[5] = 5;
	
	Main_uiconfigParam.Step_Index_Limit    = 4;
	
	Main_uiconfigParam.Step_Size[0]        =   0.01;
	Main_uiconfigParam.Step_Size[1]        =   0.1;
	Main_uiconfigParam.Step_Size[2]        =   1.0;
	Main_uiconfigParam.Step_Size[3]        =   10.0;
	Main_uiconfigParam.Step_Size[4]        =  100.0;
	
	Show_Para_Con(&Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 2;
	Main_uiconfigParam.Page_Index          = 0;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
}



void Main_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	
	
	
	/* 信号 */
	if(canConnect.status == enBreak)
	{
		OLED_DrawBMP(12,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	}
	
	/* 页面 */
	OLED_ShowChar(97,56,'e',1);
	OLED_ShowNum(103,56,Main_uiconfigParam.Para_Index,2,0,1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	
	//第 0 页
	if(Main_uiconfigParam.Page_Index == 0)
	{  
		
		h = 0;
		//第0行
		OLED_ShowString(103,56,(u8 *)"  ",1);
		
		// 1 、 2 行
		h = 1;
		OLED_ShowNum(0,45,ClockA.Year,4,0,1);
		OLED_ShowNum(0,35,ClockA.Week,4,0,1);
		OLED_ShowNum(110,45,ClockA.Month,2,0,1);
		OLED_ShowNum(110,35,ClockA.Day,2,0,1);
		if(ClockA.Hour < 10)
		{
			OLED_ShowNum(32,(7-h)*8,0,1,0,2);
			OLED_ShowNum(40,(7-h)*8,ClockA.Hour,1,0,2);
		}
		else		
		{
			OLED_ShowNum(32,(7-h)*8,ClockA.Hour,2,0,2);
		}
		OLED_ShowString(48,(7-h)*8,(u8 *)":",2);
		if(ClockA.Minute < 10)
		{
			OLED_ShowNum(56,(7-h)*8,0,1,0,2);
			OLED_ShowNum(64,(7-h)*8,ClockA.Minute,1,0,2);
		}
		else		
		{
			OLED_ShowNum(56,(7-h)*8,ClockA.Minute,2,0,2);
		}
		OLED_ShowString(72,(7-h)*8,(u8 *)":",2);
		if(ClockA.Second < 10)
		{
			OLED_ShowNum(80,(7-h)*8,0,1,0,2);
			OLED_ShowNum(88,(7-h)*8,ClockA.Second,1,0,2);
		}
		else		
		{
			OLED_ShowNum(80,(7-h)*8,ClockA.Second,2,0,2);
		}
		// 4 、 5 行
		h = 5;
		 OLED_ShowCHinese(0,(7-h)*8,9);          //叶子
		 switch(Pms.AQI)
		 {
			 case 1:
				      OLED_ShowCHinese(26,(7-h)*8,0);      //优
			        OLED_ShowCHinese(42,(7-h)*8,15);      // 
			        OLED_ShowCHinese(58,(7-h)*8,15);      // 
			        OLED_ShowCHinese(74,(7-h)*8,15);      // 
			        break;
			 case 2:
				      OLED_ShowCHinese(26,(7-h)*8,1);      //良
			        OLED_ShowCHinese(42,(7-h)*8,15);      // 
			        OLED_ShowCHinese(58,(7-h)*8,15);      // 
			        OLED_ShowCHinese(74,(7-h)*8,15);      // 
			        break;
			 case 3:
				      OLED_ShowCHinese(26,(7-h)*8,2);      //轻
			        OLED_ShowCHinese(42,(7-h)*8,6);      //度
			        OLED_ShowCHinese(58,(7-h)*8,7);      //污
			        OLED_ShowCHinese(74,(7-h)*8,8);      //染
			        break;
			 case 4:
				      OLED_ShowCHinese(26,(7-h)*8,3);      //中
			        OLED_ShowCHinese(42,(7-h)*8,6);      //度
			        OLED_ShowCHinese(58,(7-h)*8,7);      //污
			        OLED_ShowCHinese(74,(7-h)*8,8);      //染
			        break;
			 case 5:
				      OLED_ShowCHinese(26,(7-h)*8,4);      //重
			        OLED_ShowCHinese(42,(7-h)*8,6);      //度
			        OLED_ShowCHinese(58,(7-h)*8,7);      //污
			        OLED_ShowCHinese(74,(7-h)*8,8);      //染
			        break;
			 case 6:
				      OLED_ShowCHinese(26,(7-h)*8,5);      //严
			        OLED_ShowCHinese(42,(7-h)*8,4);      //重
			        OLED_ShowCHinese(58,(7-h)*8,7);      //污
			        OLED_ShowCHinese(74,(7-h)*8,8);      //染
			        break;
			 case 7:
				      OLED_ShowCHinese(26,(7-h)*8,14);      //优
			        OLED_ShowCHinese(42,(7-h)*8,15);      // 
			        OLED_ShowCHinese(58,(7-h)*8,15);      // 
			        OLED_ShowCHinese(74,(7-h)*8,15);      // 
			        break;
		 }
		 OLED_ShowNum(86,(7-4)*8,Bme.pressure,5,1,1);
		 OLED_ShowNum(86,(7-5)*8,Bme.asl,5,1,1);
		 // 6、7 行
		 h=6;
		 OLED_ShowNum(0,(7-h)*8,Huimiture.temperature,2,1,2); 	
     OLED_ShowString(40,(7-7)*8,(u8 *)"`C",1);
		
		 OLED_ShowNum(70,(7-h)*8,Huimiture.huimidity,2,1,2);
     OLED_ShowString(108,(7-7)*8,(u8 *)"%RH",1);		
	
	}
	
	//第 1 页
	if(Main_uiconfigParam.Page_Index == 1)
	{  

		h = 0;
		//第0行
		/* 显示时间 */
		if(ClockA.Hour < 10)
		{
			OLED_ShowNum(40,(7-h)*8,0,1,0,1);
			OLED_ShowNum(46,(7-h)*8,ClockA.Hour,1,0,1);
		}
		else		
		{
			OLED_ShowNum(40,(7-h)*8,ClockA.Hour,2,0,1);
		}
		OLED_ShowString(52,(7-h)*8,(u8 *)":",1);
		if(ClockA.Minute < 10)
		{
			OLED_ShowNum(58,(7-h)*8,0,1,0,1);
			OLED_ShowNum(64,(7-h)*8,ClockA.Minute,1,0,1);
		}
		else		
		{
			OLED_ShowNum(58,(7-h)*8,ClockA.Minute,2,0,1);
		}
		OLED_ShowString(70,(7-h)*8,(u8 *)":",1);
		if(ClockA.Second < 10)
		{
			OLED_ShowNum(76,(7-h)*8,0,1,0,1);
			OLED_ShowNum(82,(7-h)*8,ClockA.Second,1,0,1);
		}
		else		
		{
			OLED_ShowNum(76,(7-h)*8,ClockA.Second,2,0,1);
		}
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Temp :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Temp :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"`C   ",1);		
			OLED_ShowNum(86,(7-h)*8,Huimiture.temperature,5,1,1);
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Huim :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Huim :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"%RH  ",1);
			OLED_ShowNum(86,(7-h)*8,Huimiture.huimidity,5,1,1);
			h++;
	  }
	
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Light:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Light:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"lx   ",1);
			OLED_ShowNum(86,(7-h)*8,Light.BH_Voltage,5,1,1);
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"PM2.5:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"PM2.5:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"ug/m3",1);
			OLED_ShowNum(86,(7-h)*8,Pms.PM2_5_Vol,5,1,1);
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"PM10 :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"PM10 :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"ug/m3",1);
			OLED_ShowNum(86,(7-h)*8,Pms.PM10_Vol,5,1,1);
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_P:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_P:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"hPa  ",1);
			OLED_ShowNum(86,(7-h)*8,Bme.pressure,5,1,1);
			h++;
	  }
		
		//7行
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_A:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_A:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"m    ",1);
			OLED_ShowNum(86,(7-h)*8,Bme.asl,5,1,1);
			h++;
	  }
		
		//8行
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_T:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_T:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"`C   ",1);
			OLED_ShowNum(86,(7-h)*8,Bme.temperature,5,1,1);
			h++;
	  }
		
		//9行
	  Ph = 9;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_H:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_H:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"%RH  ",1);
			OLED_ShowNum(86,(7-h)*8,Bme.humidity,5,1,1);
			h++;
	  }
		
		//10行
	  Ph = 10;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Smog :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Smog :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"     ",1);
			OLED_ShowNum(86,(7-h)*8,Smog.PriVal,5,1,1);
			h++;
	  }
		
		//11行
	  Ph = 11;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Hydr :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Hydr :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"     ",1);
			OLED_ShowNum(86,(7-h)*8,Hydrogen.PriVal,5,1,1);
			h++;
	  }
		
		//12行
	  Ph = 12;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"CO   :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"CO   :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"     ",1);
			OLED_ShowNum(86,(7-h)*8,CO.PriVal,5,1,1);
			h++;
	  }
	}
	
	//第 2 页
	if(Main_uiconfigParam.Page_Index == 2)
	{  
		
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,2,1);
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempOf:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempOf:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.temp_offset,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.temp_offset,3,1,1);
			}
			h++;
	  }
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimOf:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimOf:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.huim_offset,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.huim_offset,3,1,1);
			}
			h++;
	  }
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAM:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAM:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.tempAdd_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.tempAdd_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }	
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAP:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAP:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.AddPwm,5,0,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.AddPwm,5,0,1);
			}
			h++;
	  }
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAS:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAS:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.tempAdd_shieldVal,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.tempAdd_shieldVal,3,1,1);
			}
			h++;
	  }
		//6行
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRM:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRM:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.tempRed_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.tempRed_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//7行
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRP:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRP:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.RedPwm,5,0,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.RedPwm,5,0,1);
			}
			h++;
	  }
		//8行
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRS:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRS:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.tempRed_shieldVal,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.tempRed_shieldVal,3,1,1);
			}
			h++;
	  }
		//9行
	  Ph = 9;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimM :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.huim_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.huim_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//10行
	  Ph = 10;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimS :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Huimiture.huim_shieldVal,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Huimiture.huim_shieldVal,3,1,1);
			}
			h++;
	  }
		//11行
	  Ph = 11;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightM :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Light.mode)
					{
						case enLightMode_OFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enLightMode_GS:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   GS",1);
									break;
						case enLightMode_RC:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   RC",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Light.mode)
					{
						case enLightMode_OFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enLightMode_GS:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   GS",1);
									break;
						case enLightMode_RC:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   RC",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//12行
	  Ph = 12;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightS :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Light.shieldVal,5,0,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Light.shieldVal,5,0,1);
			}
			h++;
	  }
		//13行
	  Ph = 13;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightA :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightA :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Light.a,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Light.a,3,1,1);
			}
			h++;
	  }
		//14行
	  Ph = 14;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"PmsM   :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"PmsM   :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Pms.mode)
					{
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Pms.mode)
					{
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//15行
	  Ph = 15;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Pm2_5S :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Pm2_5S :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Pms.shieldPM2_5Val,5,0,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Pms.shieldPM2_5Val,5,0,1);
			}
			h++;
	  }
		//16行
	  Ph = 16;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Pm10S  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Pm10S  :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Pms.shieldPM10Val,3,1,1);
					Oled_Colour = 0;					
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Pms.shieldPM10Val,3,1,1);
			}
			h++;
	  }
	}
	
	//第 3 页
	if(Main_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,2,1);
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedAs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedAs:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(LedA.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(LedA.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedAc:",1); //LedA的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedAc:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,LedA.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,LedA.cycle,5,0,1);
			}
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedBs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedBs:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(LedB.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(LedB.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedBc:",1); //LedB的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedBc:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,LedB.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,LedB.cycle,5,0,1);
			}
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqs :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqs :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Fmq.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Fmq.flag_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Cyc",1);
									break;
						case enCom:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqc :",1); //LedB的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqc :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Fmq.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Fmq.cycle,5,0,1);
			}
			h++;
	  }
		
	}
	
	//第 4 页
	if(Main_uiconfigParam.Page_Index == 4)
	{  
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_Y :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_Y :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Year,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Year,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Year,4,0,1);
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_M :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_M :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Month,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Month,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Month,4,0,1);
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_W :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_W :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Week,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Week,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Week,4,0,1);
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_D :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_D :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Day,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Day,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Day,4,0,1);
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_H :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_H :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Hour,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Hour,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Hour,4,0,1);
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_m :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_m :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Minute,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Minute,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Minute,4,0,1);
			h++;
	  }
		
		//7行
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_S :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_S :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Second,4,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(104,(7-h)*8,SetClock.Second,4,0,1);
			}
			OLED_ShowNum(52,(7-h)*8,ClockA.Second,4,0,1);
			h++;
	  }
		
		//8行
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_n :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_n :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,SetClock.num_save,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,SetClock.num_save,5,0,1);
			}
			OLED_ShowString(52,(7-h)*8,(u8 *)"    ",1);
			h++;
	  }
	}
	
	//第 5 页
	if(Main_uiconfigParam.Page_Index == 5)
	{  
		
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,2,1);
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAM:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempAM:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.tempAdd_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.tempAdd_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }	
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRM:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"STempRM:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.tempRed_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.tempRed_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SHuimM :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Huimiture.huim_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Huimiture.huim_mode)
					{
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LightM :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Light.mode)
					{
						case enLightMode_OFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enLightMode_GS:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   GS",1);
									break;
						case enLightMode_RC:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   RC",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Light.mode)
					{
						case enLightMode_OFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enLightMode_GS:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   GS",1);
									break;
						case enLightMode_RC:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   RC",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"PmsM   :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"PmsM   :",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Pms.mode)
					{
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Pms.mode)
					{
						case enOFF:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  OFF",1);
									break;
						case enON:
									OLED_ShowString(98,(7-h)*8,(u8 *)"   ON",1);
									break;
						case enFre:
									OLED_ShowString(98,(7-h)*8,(u8 *)"  Con",1);
									break;
						default:break;
					}
			}
			h++;
	  }
	}
}


/************************************ 对应的按键函数 **********************************/


//预备参数,防止无线控制更新参数   内部（一般用于切换页面时重新准备显示数据）
static void Para_Prepare(void)
{
  if(Main_uiconfigParam.Page_Index_Last != Main_uiconfigParam.Page_Index)
  {
    Main_uiconfigParam.Page_Index_Last = Main_uiconfigParam.Page_Index;
    OLED_Clear();
  }
  
  if(Main_uiconfigParam.Page_Index==4)
  {
    SetClock.Year  =ClockA.Year;
		SetClock.Month =ClockA.Month;
		SetClock.Week  =ClockA.Week;
		SetClock.Day   =ClockA.Day;
		SetClock.Hour  =ClockA.Hour;
		SetClock.Minute=ClockA.Minute;
		SetClock.Second=ClockA.Second;	
  }

}

void Main_uictrl(void)
{
	//中键被单击
	if(Key_PM.Key_RetVal == enKey_Click)
	{
    if(Main_uiconfigParam.Para_IfControl==false && ((Main_uiconfigParam.Page_Index == 1)   
																							   || (Main_uiconfigParam.Page_Index == 2)  
																								 || (Main_uiconfigParam.Page_Index == 3)
																								 || (Main_uiconfigParam.Page_Index == 4)
																								 || (Main_uiconfigParam.Page_Index == 5))) 
			 Main_uiconfigParam.Para_IfControl=true;    //可控页
    else                                                                  
			 Main_uiconfigParam.Para_IfControl=false;

		if(Main_uiconfigParam.Page_Index==0)    
    {
			/* 切换UImode */
			Change_UIMode();
		}
		
		Key_PM.Key_RetVal = enKey_No;   //标志复位
	}
	//中键被长按中
	if(Key_PM.Key_RetVal == enKey_LongPress)
	{
		
	}	
	
	//左键被单击
	if(Key_PL.Key_RetVal == enKey_Click)
	{
		if(Main_uiconfigParam.Para_IfControl)  
    {
      if(Main_uiconfigParam.Step_Index >= Main_uiconfigParam.Step_Index_Limit)
           Main_uiconfigParam.Step_Index = 0
			;
      else Main_uiconfigParam.Step_Index++;
    }
    else
    {
      if(Main_uiconfigParam.Page_Index<=0) 
        Main_uiconfigParam.Page_Index=Main_uiconfigParam.Page_Index_Limit; 
      else 
        Main_uiconfigParam.Page_Index--;		
			Main_uiconfigParam.Para_Index=1;         //参数索引复位
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();
      OLED_Clear();
    }

		Key_PL.Key_RetVal = enKey_No;   //标志复位
	}
	//左键被长按中
	if(Key_PL.Key_RetVal == enKey_LongPress)
	{
		
	}
	
	//右键被单击
	if(Key_PR.Key_RetVal == enKey_Click)
	{
		if(Main_uiconfigParam.Para_IfControl)  
    {
      if(Main_uiconfigParam.Step_Index <= 0)
           Main_uiconfigParam.Step_Index = Main_uiconfigParam.Step_Index_Limit;
      else Main_uiconfigParam.Step_Index--;
    }
    else
    {
      if(Main_uiconfigParam.Page_Index>=Main_uiconfigParam.Page_Index_Limit) 
        Main_uiconfigParam.Page_Index=0; 
      else 
        Main_uiconfigParam.Page_Index++;		
			Main_uiconfigParam.Para_Index=1;         //参数复位
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();			
      OLED_Clear();
    }
		
		Key_PR.Key_RetVal = enKey_No;   //标志复位
	}
	//右键被长按中
	if(Key_PR.Key_RetVal == enKey_LongPress)
	{
		
	}	
	
	//上键被单击
	if(Key_PU.Key_RetVal == enKey_Click)
	{
		if(Main_uiconfigParam.Para_IfControl == false) 
    {
      if(Main_uiconfigParam.Para_Index<=1) Main_uiconfigParam.Para_Index = Main_uiconfigParam.Para_Index_Limit[Main_uiconfigParam.Page_Index];
      else              Main_uiconfigParam.Para_Index--;		
			Show_Para_Con(&Main_uiconfigParam);
    }
    else
    { 
			
		if(Main_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							Huimiture.temp_offset += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.temp_offset > 1000) Huimiture.temp_offset = 1000;
							break;
					case 2:
							Huimiture.huim_offset += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.huim_offset > 1000) Huimiture.huim_offset = 1000;
							break;
					case 3:
							switch(Huimiture.tempAdd_mode)
							{
								case enON:
											Huimiture.tempAdd_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempAdd_mode = enFre;
											break;
								case enFre:
											Huimiture.tempAdd_mode = enON;
											Huimiture.tempRed_mode = enOFF;
											break;
								default:
											Huimiture.tempAdd_mode = enOFF;
											break;
							}
							break;
					case 4:
							Huimiture.AddPwm += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.AddPwm > 7200) Huimiture.AddPwm = 7200;
							break;
					case 5:
							Huimiture.tempAdd_shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.tempAdd_shieldVal > Huimiture.tempRed_shieldVal) Huimiture.tempAdd_shieldVal = Huimiture.tempRed_shieldVal;
							break;
					case 6:
							switch(Huimiture.tempRed_mode)
							{
								case enON:
											Huimiture.tempRed_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempRed_mode = enFre;
											break;
								case enFre:
											Huimiture.tempRed_mode = enON;
											Huimiture.tempAdd_mode = enOFF;
											break;
								default:
											Huimiture.tempRed_mode = enOFF;
											break;
							}
							break;
				 case 7:
							Huimiture.RedPwm += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.RedPwm > 7200) Huimiture.RedPwm = 7200;
				 case 8:
							Huimiture.tempRed_shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.tempRed_shieldVal > 1000) Huimiture.tempRed_shieldVal = 1000;
							break;
				 case 9:
							switch(Huimiture.huim_mode)
							{
								case enON:
											Huimiture.huim_mode = enOFF;
											break;
								case enOFF:
											Huimiture.huim_mode = enFre;
											break;
								case enFre:
											Huimiture.huim_mode = enON;
											break;
								default:
											Huimiture.huim_mode = enON;
											break;
							}
							break;
				 case 10:
							Huimiture.huim_shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.huim_shieldVal > 1000) Huimiture.huim_shieldVal = 1000;
							break;
				 case 11:
							switch(Light.mode)
							{
								case enLightMode_OFF:
											Light.mode = enLightMode_GS;
											break;
								case enLightMode_GS:
											Light.mode = enLightMode_RC;
											break;
								case enLightMode_RC:
											Light.mode = enLightMode_OFF;
											break;
								default:
											Light.mode = enLightMode_OFF;
											break;
							}
							break;
				 case 12:
							Light.shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Light.shieldVal > 9999) Light.shieldVal = 9999;
							break;
				 case 13:
							Light.a += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Light.a > 999) Light.a = 999;
							break;
				 case 14:
							switch(Pms.mode)
							{
								case enOFF:
											Pms.mode = enON;
											break;
								case enON:
											Pms.mode = enFre;
											break;
								case enFre:
											Pms.mode = enOFF;
											break;
								default:
											Pms.mode = enOFF;
											break;
							}
							break;
				 case 15:
							Pms.shieldPM2_5Val += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Pms.shieldPM2_5Val >= 65535) Pms.shieldPM2_5Val = 65535;
							break;
				 case 16:
							Pms.shieldPM10Val += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Pms.shieldPM10Val >= 65535) Pms.shieldPM10Val = 65535;
							break;
					default:break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==3)     //修改第3参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(LedA.flag_mode)
							{
								case enON:
											LedA.flag_mode = enOFF;
											break;
								case enOFF:
											LedA.flag_mode = enFre;
											break;
								case enFre:
											LedA.flag_mode = enCom;
											break;
								case enCom:
											LedA.flag_mode = enON;
											break;
								default:
											LedA.flag_mode = enON;
											break;
							}
							break;
					case 2:
							LedA.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedA.cycle > 10000) LedA.cycle = 10000;
							break;
					case 3:
							switch(LedB.flag_mode)
							{
								case enON:
											LedB.flag_mode = enOFF;
											break;
								case enOFF:
											LedB.flag_mode = enFre;
											break;
								case enFre:
											LedB.flag_mode = enCom;
											break;
								case enCom:
											LedB.flag_mode = enON;
											break;
								default:
											LedB.flag_mode = enON;
											break;
							}
							break;
					case 4:
							LedB.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedB.cycle > 10000) LedB.cycle = 10000;
							break;
					case 5:
							switch(Fmq.flag_mode)
							{
								case enON:
											Fmq.flag_mode = enOFF;
											break;
								case enOFF:
											Fmq.flag_mode = enFre;
											break;
								case enFre:
											Fmq.flag_mode = enCom;
											break;
								case enCom:
											Fmq.flag_mode = enON;
											break;
								default:
											Fmq.flag_mode = enON;
											break;
							}
							break;
					case 6:
							Fmq.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle > 10000) Fmq.cycle = 10000;
							break;
					default:break;
				}
			}
			
			
			
			if(Main_uiconfigParam.Page_Index==4)     //修改第4页参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
								 SetTime_Add(&SetClock,enYear,1);
								 break;
					case 2:
								 SetTime_Add(&SetClock,enMonth,1);
								 break;
					case 3:
								 SetTime_Add(&SetClock,enWeek,1);
								 break;
					case 4:
								 SetTime_Add(&SetClock,enDay,1);
								 break;
					case 5:
								 SetTime_Add(&SetClock,enHour,1);
								 break;
					case 6:
								 SetTime_Add(&SetClock,enMinute,1);
								 break;
					case 7:
								 SetTime_Add(&SetClock,enSecond,1);
								 break;
					case 8:
								SetClock.num_save++;
								DS3231_SetTime(&SetClock);
								break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==5)     //修改第5参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Huimiture.tempAdd_mode)
							{
								case enON:
											Huimiture.tempAdd_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempAdd_mode = enFre;
											break;
								case enFre:
											Huimiture.tempAdd_mode = enON;
											Huimiture.tempRed_mode = enOFF;
											break;
								default:
											Huimiture.tempAdd_mode = enOFF;
											break;
							}
							break;
					case 2:
							switch(Huimiture.tempRed_mode)
							{
								case enON:
											Huimiture.tempRed_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempRed_mode = enFre;
											break;
								case enFre:
											Huimiture.tempRed_mode = enON;
											Huimiture.tempAdd_mode = enOFF;
											break;
								default:
											Huimiture.tempRed_mode = enOFF;
											break;
							}
							break;
				 case 3:
							switch(Huimiture.huim_mode)
							{
								case enON:
											Huimiture.huim_mode = enOFF;
											break;
								case enOFF:
											Huimiture.huim_mode = enFre;
											break;
								case enFre:
											Huimiture.huim_mode = enON;
											break;
								default:
											Huimiture.huim_mode = enON;
											break;
							}
							break;
				 case 4:
							switch(Light.mode)
							{
								case enLightMode_OFF:
											Light.mode = enLightMode_GS;
											break;
								case enLightMode_GS:
											Light.mode = enLightMode_RC;
											break;
								case enLightMode_RC:
											Light.mode = enLightMode_OFF;
											break;
								default:
											Light.mode = enLightMode_OFF;
											break;
							}
							break;
				 case 5:
							switch(Pms.mode)
							{
								case enOFF:
											Pms.mode = enON;
											break;
								case enON:
											Pms.mode = enFre;
											break;
								case enFre:
											Pms.mode = enOFF;
											break;
								default:
											Pms.mode = enOFF;
											break;
							}
							break;
					default:break;
				}
			}
			
			
		}

		Key_PU.Key_RetVal = enKey_No;   //标志复位
	}
	
	//上键被长按中
	if(Key_PU.Key_RetVal == enKey_LongPress)
	{

		if(Main_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
		
			if(Main_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				
			}
		}
		
	}
	
	//下键被单击
	if(Key_PD.Key_RetVal == enKey_Click)
	{
		if(Main_uiconfigParam.Para_IfControl == false) 
    {
			if(Main_uiconfigParam.Para_Index>=Main_uiconfigParam.Para_Index_Limit[Main_uiconfigParam.Page_Index]) Main_uiconfigParam.Para_Index = 1;
      else              Main_uiconfigParam.Para_Index++;
			Show_Para_Con(&Main_uiconfigParam);
    }
    else
    { 
			if(Main_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							Huimiture.temp_offset -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.temp_offset < -1000) Huimiture.temp_offset = -1000;
							break;
					case 2:
							Huimiture.huim_offset -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.huim_offset < -1000) Huimiture.huim_offset = -1000;
							break;
					case 3:
							switch(Huimiture.tempAdd_mode)
							{
								case enON:
											Huimiture.tempAdd_mode = enFre;
											break;
								case enFre:
											Huimiture.tempAdd_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempAdd_mode = enON;
											Huimiture.tempRed_mode = enOFF;
											break;
								default:
											Huimiture.tempAdd_mode = enON;
											break;
							}
							break;
				  case 4:
							Huimiture.AddPwm -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.AddPwm <= 0) Huimiture.AddPwm = 0;
					case 5:
							Huimiture.tempAdd_shieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.tempAdd_shieldVal < -100) Huimiture.tempAdd_shieldVal = -100;
							break;
					case 6:
							switch(Huimiture.tempRed_mode)
							{
								case enON:
											Huimiture.tempRed_mode = enFre;
											break;
								case enFre:
											Huimiture.tempRed_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempRed_mode = enON;
											Huimiture.tempAdd_mode = enOFF;
											break;
								default:
											Huimiture.tempRed_mode = enON;
											break;
							}
							break;
				 case 7:
							Huimiture.RedPwm -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.RedPwm <= 0) Huimiture.RedPwm = 0;
				 case 8:
							Huimiture.tempRed_shieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.tempRed_shieldVal < Huimiture.tempAdd_shieldVal) Huimiture.tempRed_shieldVal = Huimiture.tempAdd_shieldVal;
							break;
				 case 9:
							switch(Huimiture.huim_mode)
							{
								case enON:
											Huimiture.huim_mode = enFre;
											break;
								case enFre:
											Huimiture.huim_mode = enOFF;
											break;
								case enOFF:
											Huimiture.huim_mode = enON;
											break;
								default:
											Huimiture.huim_mode = enON;
											break;
							}
							break;
				 case 10:
							Huimiture.huim_shieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Huimiture.huim_shieldVal < -1000) Huimiture.huim_shieldVal = -1000;
							break;
				 case 11:
							switch(Light.mode)
							{
								case enLightMode_OFF:
											Light.mode = enLightMode_RC;
											break;
								case enLightMode_RC:
											Light.mode = enLightMode_GS;
											break;
								case enLightMode_GS:
											Light.mode = enLightMode_OFF;
											break;
								default:
											Light.mode = enLightMode_OFF;
											break;
							}
							break;
				 case 12:
							Light.shieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Light.shieldVal < -9999) Light.shieldVal = -9999;
							break;
				 case 13:
							Light.a -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Light.a < -999) Light.a = -999;
							break;
				 case 14:
							switch(Pms.mode)
							{
								case enOFF:
											Pms.mode = enFre;
											break;
								case enFre:
											Pms.mode = enON;
											break;
								case enON:
											Pms.mode = enOFF;
											break;
								default:
											Pms.mode = enOFF;
											break;
							}
							break;
				 case 15:
							Pms.shieldPM2_5Val -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Pms.shieldPM2_5Val < 0) Pms.shieldPM2_5Val = 0;
							break;
				 case 16:
							Pms.shieldPM10Val -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Pms.shieldPM10Val <= 0) Pms.shieldPM10Val = 0;
							break;
					default:break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==3)     //修改第3页参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(LedA.flag_mode)
							{
								case enON:
											LedA.flag_mode = enCom;
											break;
								case enCom:
											LedA.flag_mode = enFre;
											break;
								case enFre:
											LedA.flag_mode = enOFF;
											break;
								case enOFF:
											LedA.flag_mode = enON;
											break;
								default:
											LedA.flag_mode = enON;
											break;
							}
							break;
					case 2:
							LedA.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedA.cycle <  -1) LedA.cycle =  -1;
							break;
					case 3:
							switch(LedB.flag_mode)
							{
								case enON:
											LedB.flag_mode = enCom;
											break;
								case enCom:
											LedB.flag_mode = enFre;
											break;
								case enFre:
											LedB.flag_mode = enOFF;
											break;
								case enOFF:
											LedB.flag_mode = enON;
											break;
								default:
											LedB.flag_mode = enON;
											break;
							}
							break;
					case 4:
							LedB.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedB.cycle <  -1) LedB.cycle =  -1;
							break;
					case 5:
							switch(Fmq.flag_mode)
							{
								case enON:
											Fmq.flag_mode = enCom;
											break;
								case enCom:
											Fmq.flag_mode = enFre;
											break;
								case enFre:
											Fmq.flag_mode = enOFF;
											break;
								case enOFF:
											Fmq.flag_mode = enON;
											break;
								default:
											Fmq.flag_mode = enON;
											break;
							}
							break;
					case 6:
							Fmq.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle < -1) Fmq.cycle = -1;
							break;
					default:break;
				}
			}
				
			if(Main_uiconfigParam.Page_Index==4)     //修改第4页参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
									 SetTime_Add(&SetClock,enYear,0);
									 break;
					case 2:
								 SetTime_Add(&SetClock,enMonth,0);
								 break;
					case 3:
								 SetTime_Add(&SetClock,enWeek,0);
								 break;
					case 4:
								 SetTime_Add(&SetClock,enDay,0);
								 break;
					case 5:
								 SetTime_Add(&SetClock,enHour,0);
								 break;
					case 6:
								 SetTime_Add(&SetClock,enMinute,0);
								 break;
					case 7:
								 SetTime_Add(&SetClock,enSecond,0);
								 break;
					case 8:
								SetClock.num_save++;
								DS3231_SetTime(&SetClock);
								break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==5)     //修改第5参数
      {
				//参数行
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Huimiture.tempAdd_mode)
							{
								case enON:
											Huimiture.tempAdd_mode = enFre;
											break;
								case enFre:
											Huimiture.tempAdd_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempAdd_mode = enON;
											Huimiture.tempRed_mode = enOFF;
											break;
								default:
											Huimiture.tempAdd_mode = enON;
											break;
							}
							break;
					case 2:
							switch(Huimiture.tempRed_mode)
							{
								case enON:
											Huimiture.tempRed_mode = enFre;
											break;
								case enFre:
											Huimiture.tempRed_mode = enOFF;
											break;
								case enOFF:
											Huimiture.tempRed_mode = enON;
											Huimiture.tempAdd_mode = enOFF;
											break;
								default:
											Huimiture.tempRed_mode = enON;
											break;
							}
							break;
				 case 3:
							switch(Huimiture.huim_mode)
							{
								case enON:
											Huimiture.huim_mode = enFre;
											break;
								case enFre:
											Huimiture.huim_mode = enOFF;
											break;
								case enOFF:
											Huimiture.huim_mode = enON;
											break;
								default:
											Huimiture.huim_mode = enON;
											break;
							}
							break;
				 case 4:
							switch(Light.mode)
							{
								case enLightMode_OFF:
											Light.mode = enLightMode_RC;
											break;
								case enLightMode_RC:
											Light.mode = enLightMode_GS;
											break;
								case enLightMode_GS:
											Light.mode = enLightMode_OFF;
											break;
								default:
											Light.mode = enLightMode_OFF;
											break;
							}
							break;
				 case 5:
							switch(Pms.mode)
							{
								case enOFF:
											Pms.mode = enFre;
											break;
								case enFre:
											Pms.mode = enON;
											break;
								case enON:
											Pms.mode = enOFF;
											break;
								default:
											Pms.mode = enOFF;
											break;
							}
							break;
					default:break;
				}
			}
			
		}

		Key_PD.Key_RetVal = enKey_No;   //标志复位
	}
	//下键被长按中
	if(Key_PD.Key_RetVal == enKey_LongPress)
	{
		if(Main_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
			;
		}
	}	
}











