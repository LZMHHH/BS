/**
  ******************************************************************************
  * @file    main.c
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
	Main_uiconfigParam.Para_Index_Limit[1] = 9;
	Main_uiconfigParam.Para_Index_Limit[2] = 7;
	Main_uiconfigParam.Para_Index_Limit[3] = 7;
	
	Main_uiconfigParam.Step_Index_Limit    = 6;
	
	Main_uiconfigParam.Step_Size[0]        =   0.001;
	Main_uiconfigParam.Step_Size[1]        =   0.01;
	Main_uiconfigParam.Step_Size[2]        =   0.1;
	Main_uiconfigParam.Step_Size[3]        =   1.0;
	Main_uiconfigParam.Step_Size[4]        =  10.0;
	Main_uiconfigParam.Step_Size[5]        = 100.0;
	
	Show_Para_Con(&Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 1;
	Main_uiconfigParam.Page_Index          = 1;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
}



void Main_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	u8 color;//颜色参数
	
	
	
	/* 页面 */
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	/* 信号 */
	OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	
	
	//第 0 页
	if(Main_uiconfigParam.Page_Index == 0)
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
		OLED_ShowString(52,(7-h)*8,":",1);
		if(ClockA.Minute < 10)
		{
			OLED_ShowNum(58,(7-h)*8,0,1,0,1);
			OLED_ShowNum(64,(7-h)*8,ClockA.Minute,1,0,1);
		}
		else		
		{
			OLED_ShowNum(58,(7-h)*8,ClockA.Minute,2,0,1);
		}
		OLED_ShowString(70,(7-h)*8,":",1);
		if(ClockA.Second < 10)
		{
			OLED_ShowNum(76,(7-h)*8,0,1,0,1);
			OLED_ShowNum(82,(7-h)*8,ClockA.Second,1,0,1);
		}
		else		
		{
			OLED_ShowNum(76,(7-h)*8,ClockA.Second,2,0,1);
		}
	
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
		OLED_ShowString(52,(7-h)*8,":",1);
		if(ClockA.Minute < 10)
		{
			OLED_ShowNum(58,(7-h)*8,0,1,0,1);
			OLED_ShowNum(64,(7-h)*8,ClockA.Minute,1,0,1);
		}
		else		
		{
			OLED_ShowNum(58,(7-h)*8,ClockA.Minute,2,0,1);
		}
		OLED_ShowString(70,(7-h)*8,":",1);
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
					OLED_ShowString(0,(7-h)*8,"Temp :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"Temp :",1);
			}
			OLED_ShowString(54,(7-h)*8,"`C",1);		
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
					OLED_ShowString(0,(7-h)*8,"Huim :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"Huim :",1);
			}
			OLED_ShowString(54,(7-h)*8,"%RH",1);
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
					OLED_ShowString(0,(7-h)*8,"Light:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"Light:",1);
			}
			OLED_ShowString(54,(7-h)*8,"lx",1);
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
					OLED_ShowString(0,(7-h)*8,"PM2.5:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"PM2.5:",1);
			}
			OLED_ShowString(54,(7-h)*8,"ug/m3",1);
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
					OLED_ShowString(0,(7-h)*8,"PM10 :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"PM10 :",1);
			}
			OLED_ShowString(54,(7-h)*8,"ug/m3",1);
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
					OLED_ShowString(0,(7-h)*8,"BME_P:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"BME_P:",1);
			}
			OLED_ShowString(54,(7-h)*8,"hPa",1);
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
					OLED_ShowString(0,(7-h)*8,"BME_A:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"BME_A:",1);
			}
			OLED_ShowString(54,(7-h)*8,"m",1);
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
					OLED_ShowString(0,(7-h)*8,"BME_T:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"BME_T:",1);
			}
			OLED_ShowString(54,(7-h)*8,"`C",1);
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
					OLED_ShowString(0,(7-h)*8,"BME_H:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"BME_H:",1);
			}
			OLED_ShowString(54,(7-h)*8,"%RH",1);
			OLED_ShowNum(86,(7-h)*8,Bme.humidity,5,1,1);
			h++;
	  }
		
	}
	
	//第 3 页
	if(Main_uiconfigParam.Page_Index == 3)
	{  
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"T_Y :",1);
					Oled_Colour = 0;
				
					OLED_ShowNum(104,(7-h)*8,SetClock.Year,4,0,1);
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"T_Y :",1);
				
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Year,4,0,1);
					Oled_Colour = 0;
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
					OLED_ShowString(0,(7-h)*8,"T_M :",1);
					Oled_Colour = 0;
				
					OLED_ShowNum(104,(7-h)*8,SetClock.Year,4,0,1);
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"T_M :",1);
				
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(104,(7-h)*8,SetClock.Month,4,0,1);
					Oled_Colour = 0;
			}		
			OLED_ShowNum(58,(7-h)*8,ClockA.Month,4,0,1);
			h++;
	  }
		

//		OLED_ShowNum(30,56,ClockA.Second,3,0,1);
//		OLED_ShowNum(30,48,ClockA.Minute,3,0,1);
//		OLED_ShowNum(30,40,ClockA.Hour,3,0,1);
//		OLED_ShowNum(30,32,ClockA.Day,3,0,1);
//		OLED_ShowNum(30,24,ClockA.Week,3,0,1);
//		OLED_ShowNum(30,16,ClockA.Month,3,0,1);
//		OLED_ShowNum(30,8,ClockA.Year,5,0,1);
//		OLED_ShowNum(80,56,ClockA.Temp,3,1,1);
		
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
  
  if(Main_uiconfigParam.Page_Index==3)
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
    if(Main_uiconfigParam.Para_IfControl==false && ((Main_uiconfigParam.Page_Index == 1) || (Main_uiconfigParam.Page_Index == 2) || (Main_uiconfigParam.Page_Index == 3))) 
			 Main_uiconfigParam.Para_IfControl=true;    //可控页
    else                                                                  
			 Main_uiconfigParam.Para_IfControl=false;

		
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
			if(Main_uiconfigParam.Page_Index==1)     //修改第1页参数
      {
				
			}
			
			if(Main_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				
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
			if(Main_uiconfigParam.Page_Index==1)     //修改第1页参数
      {
				;
			}
			
			if(Main_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				;
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
