/**
  ******************************************************************************
  * @file    envi_ui.h
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

#include "envi_ui.h"


CLASS_UIconfigParam Envi_uiconfigParam;

void Envi_uiconfigParamInit(void)
{
	Envi_uiconfigParam.Page_Index_Limit    = 5;
	
	Envi_uiconfigParam.Para_Index_Limit[0] = 7;
	Envi_uiconfigParam.Para_Index_Limit[1] = 9;
	Envi_uiconfigParam.Para_Index_Limit[2] = 8;
	Envi_uiconfigParam.Para_Index_Limit[3] = 8;
	Envi_uiconfigParam.Para_Index_Limit[4] = 8;
	
	Envi_uiconfigParam.Step_Index_Limit    = 6;
	
	Envi_uiconfigParam.Step_Size[0]        =   0.001;
	Envi_uiconfigParam.Step_Size[1]        =   0.01;
	Envi_uiconfigParam.Step_Size[2]        =   0.1;
	Envi_uiconfigParam.Step_Size[3]        =   1.0;
	Envi_uiconfigParam.Step_Size[4]        =  10.0;
	Envi_uiconfigParam.Step_Size[5]        = 100.0;
	
	Show_Para_Con(&Envi_uiconfigParam);
	
	Envi_uiconfigParam.Step_Index          = 1;
	Envi_uiconfigParam.Page_Index          = 2;
	Envi_uiconfigParam.Page_Index_Last     = 0;
	Envi_uiconfigParam.Para_Index          = 0;
	Envi_uiconfigParam.Para_IfControl      = false;
	
}



void Envi_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	
	
	
	/* 信号 */
	if(uart3Connect.status == enBreak)
	{
		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(2,56,UI_ASIGNAL8X8,8,8);
	}

	
	
	/* 同步 */
	if(envUIPara.Sync)
	{
		OLED_ShowString(20,56,(u8 *)"T",1);
	}
	else
	{
		OLED_ShowString(20,56,(u8 *)"X",1);
	}
	
	
	/* 页面 */
	OLED_ShowChar(109,56,'e',1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Envi_uiconfigParam.Page_Index,1,0,1);
	
	
//	//第 0 页
//	if(Envi_uiconfigParam.Page_Index == 0)
//	{  
//		
//		h = 0;
//		//第0行
//		/* 显示时间 */
//		if(ClockA.Hour < 10)
//		{
//			OLED_ShowNum(40,(7-h)*8,0,1,0,1);
//			OLED_ShowNum(46,(7-h)*8,ClockA.Hour,1,0,1);
//		}
//		else		
//		{
//			OLED_ShowNum(40,(7-h)*8,ClockA.Hour,2,0,1);
//		}
//		OLED_ShowString(52,(7-h)*8,":",1);
//		if(ClockA.Minute < 10)
//		{
//			OLED_ShowNum(58,(7-h)*8,0,1,0,1);
//			OLED_ShowNum(64,(7-h)*8,ClockA.Minute,1,0,1);
//		}
//		else		
//		{
//			OLED_ShowNum(58,(7-h)*8,ClockA.Minute,2,0,1);
//		}
//		OLED_ShowString(70,(7-h)*8,":",1);
//		if(ClockA.Second < 10)
//		{
//			OLED_ShowNum(76,(7-h)*8,0,1,0,1);
//			OLED_ShowNum(82,(7-h)*8,ClockA.Second,1,0,1);
//		}
//		else		
//		{
//			OLED_ShowNum(76,(7-h)*8,ClockA.Second,2,0,1);
//		}
//	
//	}
//	
	//第 1 页
	if(Envi_uiconfigParam.Page_Index == 1)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Temp :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Temp :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"`C",1);		
			OLED_ShowNum(86,(7-h)*8,Huimiture.temperature,5,1,1);
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Huim :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Huim :",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"%RH",1);
			OLED_ShowNum(86,(7-h)*8,Huimiture.huimidity,5,1,1);
			h++;
	  }
	
		//3行
	  Ph = 3;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Light:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"Light:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"lx",1);
			OLED_ShowNum(86,(7-h)*8,Light.BH_Voltage,5,1,1);
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_P:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_P:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"hPa",1);
			OLED_ShowNum(86,(7-h)*8,Bme.pressure,5,1,1);
			h++;
	  }
		
		//7行
	  Ph = 7;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_A:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_A:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"m",1);
			OLED_ShowNum(86,(7-h)*8,Bme.asl,5,1,1);
			h++;
	  }
		
		//8行
	  Ph = 8;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_T:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_T:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"`C",1);
			OLED_ShowNum(86,(7-h)*8,Bme.temperature,5,1,1);
			h++;
	  }
		
		//9行
	  Ph = 9;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_H:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"BME_H:",1);
			}
			OLED_ShowString(54,(7-h)*8,(u8 *)"%RH",1);
			OLED_ShowNum(86,(7-h)*8,Bme.humidity,5,1,1);
			h++;
	  }
	}
	
	//第 3 页
	if(Envi_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Envi_uiconfigParam.Step_Size[Envi_uiconfigParam.Step_Index],3,3,1);
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDAs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDAs:",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(envLEDA.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(envLEDA.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDAc:",1); //envLEDA的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDAc:",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,envLEDA.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,envLEDA.cycle,5,0,1);
			}
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDBs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDBs:",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(envLEDB.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(envLEDB.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDBc:",1); //envLEDB的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eLEDBc:",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,envLEDB.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,envLEDB.cycle,5,0,1);
			}
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eFMQs :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eFMQs :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(envFMQ.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(envFMQ.mode)
					{
						case enON:
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						case enCom:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Com",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"eFMQc :",1); //envLEDB的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"eFMQc :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,envFMQ.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,envFMQ.cycle,5,0,1);
			}
			h++;
	  }
		
	}
	
	//第 4 页
	if(Envi_uiconfigParam.Page_Index == 4)
	{  
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_Y :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_Y :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_M :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_M :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_W :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_W :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_D :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_D :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_H :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_H :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_m :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_m :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_S :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_S :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	  if(Envi_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_n :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"T_n :",1);
			}	
			if(Envi_uiconfigParam.Para_Index == Ph && Envi_uiconfigParam.Para_IfControl == true)
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
	
}


///************************************ 对应的按键函数 **********************************/


//预备参数,防止无线控制更新参数   内部（一般用于切换页面时重新准备显示数据）
static void Para_Prepare(void)
{
//  if(Envi_uiconfigParam.Page_Index_Last != Envi_uiconfigParam.Page_Index)
//  {
//    Envi_uiconfigParam.Page_Index_Last = Envi_uiconfigParam.Page_Index;
//    OLED_Clear();
//  }
//  
//  if(Envi_uiconfigParam.Page_Index==4)
//  {
//    SetClock.Year  =ClockA.Year;
//		SetClock.Month =ClockA.Month;
//		SetClock.Week  =ClockA.Week;
//		SetClock.Day   =ClockA.Day;
//		SetClock.Hour  =ClockA.Hour;
//		SetClock.Minute=ClockA.Minute;
//		SetClock.Second=ClockA.Second;	
//  }

}

void Envi_uictrl(void)
{
	//中键被单击
	if(Key_PM.Key_RetVal == enKey_Click)
	{
    if(Envi_uiconfigParam.Para_IfControl==false && ((Envi_uiconfigParam.Page_Index == 1)   
																							   || (Envi_uiconfigParam.Page_Index == 2)  
																								 || (Envi_uiconfigParam.Page_Index == 3)  
																								 || (Envi_uiconfigParam.Page_Index == 4))) 
			 Envi_uiconfigParam.Para_IfControl=true;    //可控页
    else                                                                  
			 Envi_uiconfigParam.Para_IfControl=false;

		
		Key_PM.Key_RetVal = enKey_No;   //标志复位
	}
	//中键被长按中
	if(Key_PM.Key_RetVal == enKey_LongPress)
	{
		
	}	
	
	//左键被单击
	if(Key_PL.Key_RetVal == enKey_Click)
	{
		if(Envi_uiconfigParam.Para_IfControl)  
    {
      if(Envi_uiconfigParam.Step_Index >= Envi_uiconfigParam.Step_Index_Limit)
           Envi_uiconfigParam.Step_Index = 0
			;
      else Envi_uiconfigParam.Step_Index++;
    }
    else
    {
      if(Envi_uiconfigParam.Page_Index<=0) 
        Envi_uiconfigParam.Page_Index=Envi_uiconfigParam.Page_Index_Limit; 
      else 
        Envi_uiconfigParam.Page_Index--;		
			Envi_uiconfigParam.Para_Index=1;         //参数索引复位
			Show_Para_Con(&Envi_uiconfigParam);
			Para_Prepare();
      OLED_Fill(0,0,128,64,0);		
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
		if(Envi_uiconfigParam.Para_IfControl)  
    {
      if(Envi_uiconfigParam.Step_Index <= 0)
           Envi_uiconfigParam.Step_Index = Envi_uiconfigParam.Step_Index_Limit;
      else Envi_uiconfigParam.Step_Index--;
    }
    else
    {
      if(Envi_uiconfigParam.Page_Index>=Envi_uiconfigParam.Page_Index_Limit) 
        Envi_uiconfigParam.Page_Index=0; 
      else 
        Envi_uiconfigParam.Page_Index++;		
			Envi_uiconfigParam.Para_Index=1;         //参数复位
			Show_Para_Con(&Envi_uiconfigParam);
			Para_Prepare();			
      OLED_Fill(0,0,128,64,0);
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
		if(Envi_uiconfigParam.Para_IfControl == false) 
    {
      if(Envi_uiconfigParam.Para_Index<=1) Envi_uiconfigParam.Para_Index = Envi_uiconfigParam.Para_Index_Limit[Envi_uiconfigParam.Page_Index];
      else              Envi_uiconfigParam.Para_Index--;		
			Show_Para_Con(&Envi_uiconfigParam);
    }
    else
    { 
			
			
			
		}

		Key_PU.Key_RetVal = enKey_No;   //标志复位
	}
	
	//上键被长按中
	if(Key_PU.Key_RetVal == enKey_LongPress)
	{

		if(Envi_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
		
			if(Envi_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				
			}
		}
		
	}
	
	//下键被单击
	if(Key_PD.Key_RetVal == enKey_Click)
	{
		if(Envi_uiconfigParam.Para_IfControl == false) 
    {
			if(Envi_uiconfigParam.Para_Index>=Envi_uiconfigParam.Para_Index_Limit[Envi_uiconfigParam.Page_Index]) Envi_uiconfigParam.Para_Index = 1;
      else              Envi_uiconfigParam.Para_Index++;
			Show_Para_Con(&Envi_uiconfigParam);
    }
    else
    { 
			
			
		}

		Key_PD.Key_RetVal = enKey_No;   //标志复位
	}
	//下键被长按中
	if(Key_PD.Key_RetVal == enKey_LongPress)
	{
		if(Envi_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
			;
		}
	}	
}









