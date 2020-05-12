/**
  ******************************************************************************
  * @file    car_ui.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */

#include "car_ui.h"


CLASS_UIconfigParam Car_uiconfigParam;


void Car_uiconfigParamInit(void)
{
	Car_uiconfigParam.Page_Index_Limit    = 3;
	
	Car_uiconfigParam.Para_Index_Limit[0] = 7;
	Car_uiconfigParam.Para_Index_Limit[1] = 9;
	Car_uiconfigParam.Para_Index_Limit[2] = 8;
	Car_uiconfigParam.Para_Index_Limit[3] = 7;
	
	Car_uiconfigParam.Step_Index_Limit    = 4;
	
	Car_uiconfigParam.Step_Size[0]        =   0.01;
	Car_uiconfigParam.Step_Size[1]        =   0.1;
	Car_uiconfigParam.Step_Size[2]        =   1.0;
	Car_uiconfigParam.Step_Size[3]        =   10.0;
	Car_uiconfigParam.Step_Size[4]        =  100.0;
	
	Show_Para_Con(&Car_uiconfigParam);
	
	Car_uiconfigParam.Step_Index          = 2;
	Car_uiconfigParam.Page_Index          = 0;
	Car_uiconfigParam.Page_Index_Last     = 0;
	Car_uiconfigParam.Para_Index          = 0;
	Car_uiconfigParam.Para_IfControl      = false;
	
	Car_uiconfigParam.Sync                = false;
	
	
}


void Car_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	

	/* 信号 */
	OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	
	/* 同步 */
	if(carUIPara.Sync)
	{
		OLED_ShowString(22,56,(u8 *)"T",1);
	}
	else
	{
		OLED_ShowString(22,56,(u8 *)"X",1);
	}
	
	
	/* 页面 */
	OLED_ShowChar(109,56,'c',1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Car_uiconfigParam.Page_Index,1,0,1);

	//第 0 页
	if(Car_uiconfigParam.Page_Index == 0)
	{  
		//边角
		OLED_ShowNum(0,(7-6)*8,Hwbz_LD.status,1,0,2);
		OLED_ShowNum(0,(7-1)*8,Hwbz_LU.status,1,0,2);
		OLED_ShowNum(120,(7-1)*8,Hwbz_RU.status,1,0,2);
		OLED_ShowNum(120,(7-6)*8,Hwbz_RD.status,1,0,2);
		OLED_ShowNum(0,(7-5)*8,Encoder.motorA,4,0,1);
		OLED_ShowNum(0,(7-3)*8,Encoder.motorB,4,0,1);
		OLED_ShowNum(104,(7-3)*8,Encoder.motorC,4,0,1);
		OLED_ShowNum(104,(7-5)*8,Encoder.motorD,4,0,1);
		
		//1、2行
		switch(Car.mode)
		{
			case enPWM:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pwm ",2);
						break;
			case enPID:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pid ",2);
						break;
			case enPWMSelf:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pwmS",2);
						break;
			case enPIDSelf:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pidS",2);
						break;
			case enPWMGS:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pwmG",2);
						break;
			case enPIDGS:
						OLED_ShowString(48,(7-1)*8,(u8 *)"pidG",2);
						break;
			default:break;
		}
		
		//4行
		OLED_ShowNum(40,(7-h)*8,Distance.xmm,5,0,2);
	}
	
	//第 1 页
	if(Car_uiconfigParam.Page_Index == 1)
	{  
		h = 1;
		//1行
	  Ph = 1;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutA,6,0,1);
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorA,6,0,1);
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutB,6,0,1);
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorB,6,0,1);
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutC,6,0,1);
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorC,6,0,1);
			h++;
	  }
		
		//7行
	  Ph = 7;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutD,6,0,1);
			h++;
	  }
		
		//8行
	  Ph = 8;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorD,6,0,1);
			h++;
	  }
		//9行
	  Ph = 9;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzABCD:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzABCD:",1);
			}		
			OLED_ShowString(122,(7-h)*8,(u8 *)" ",1);
			OLED_ShowNum(92,(7-h)*8,Hwbz_LD.status,1,0,1);
			OLED_ShowNum(100,(7-h)*8,Hwbz_LU.status,1,0,1);
			OLED_ShowNum(108,(7-h)*8,Hwbz_RU.status,1,0,1);
			OLED_ShowNum(116,(7-h)*8,Hwbz_RD.status,1,0,1);
			h++;
	  }
	}
	
	//第 2 页
	if(Car_uiconfigParam.Page_Index == 2)
	{  
		h = 1;
		//1行
	  Ph = 1;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarM :",1);
			}		
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Car.mode)
					{
						case enPWM:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwm ",1);
									break;
						case enPID:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pid ",1);
									break;
						case enPWMSelf:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwmS",1);
									break;
						case enPIDSelf:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pidS",1);
									break;
						case enPWMGS:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwmG",1);
									break;
						case enPIDGS:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pidG",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Car.mode)
					{
						case enPWM:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwm ",1);
									break;
						case enPID:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pid ",1);
									break;
						case enPWMSelf:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwmS",1);
									break;
						case enPIDSelf:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pidS",1);
									break;
						case enPWMGS:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pwmG",1);
									break;
						case enPIDGS:
									OLED_ShowString(104,(7-h)*8,(u8 *)"pidG",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//2行
	  Ph = 2;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarMP:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarMP:",1);
			}		
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,Car.MaxPwm,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,Car.MaxPwm,5,0,1);
			}
			h++;
	  }
		//3行
	  Ph = 3;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzxmm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzxmm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Distance.xmm,6,0,1);
			h++;
	  }
		//4行
	  Ph = 4;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzOfs :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzOfs :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Distance.offset,6,0,1);
			h++;
	  }
		//5行
	  Ph = 5;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzShi :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"bzShi :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Distance.shieldVal,6,0,1);
			h++;
	  }
		//6行
	  Ph = 6;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtP  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtP  :",1);
			}		
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.p,3,1,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.p,3,1,1);
			}
			h++;
	  }
		//7行
	  Ph = 7;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtI  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtI  :",1);
			}		
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.i,3,1,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.i,3,1,1);
			}
			h++;
	  }
		//8行
	  Ph = 8;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtD  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtD  :",1);
			}		
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.d,3,1,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,MotorAllPID.d,3,1,1);
			}
			h++;
	  }
	}
	
	//第 3 页
	if(Car_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index],3,3,1);
		
		h = 1;
		//1行
	  Ph = 1;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAs:",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(carLEDA.mode)
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
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(carLEDA.mode)
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
						default:break;
					}
			}
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAc:",1); //LedA的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAc:",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,carLEDA.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,carLEDA.cycle,5,0,1);
			}
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqs :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqs :",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(carFMQ.mode)
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
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(carFMQ.mode)
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
						default:break;
					}
			}
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqc :",1); //LedA的闪烁周期
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqc :",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,carFMQ.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,carFMQ.cycle,5,0,1);
			}
			h++;
	  }
	}
	
}


/************************************ 对应的按键函数 **********************************/


//预备参数,防止无线控制更新参数   内部（一般用于切换页面时重新准备显示数据）
static void Para_Prepare(void)
{
  if(Car_uiconfigParam.Page_Index_Last != Car_uiconfigParam.Page_Index)
  {
    Car_uiconfigParam.Page_Index_Last = Car_uiconfigParam.Page_Index;
    OLED_Clear();
  }
  
  if(Car_uiconfigParam.Page_Index==4)
  {
		
  }

}

void Car_uictrl(void)
{
	//中键被单击
	if(Key_PM.Key_RetVal == enKey_Click)
	{
    if(Car_uiconfigParam.Para_IfControl==false && ((Car_uiconfigParam.Page_Index == 1)   
																							   || (Car_uiconfigParam.Page_Index == 2)  
																								 || (Car_uiconfigParam.Page_Index == 3)  
																								 || (Car_uiconfigParam.Page_Index == 4))) 
			 Car_uiconfigParam.Para_IfControl=true;    //可控页
    else                                                                  
			 Car_uiconfigParam.Para_IfControl=false;

		
		/* 同步 */
		if(Car_uiconfigParam.Page_Index==0)    
    {
			/* 切换UImode */
			Change_UIMode();	
		}
		else
		{
			if(carUIPara.Sync == true)
			{
				canSendKeyClickData(CAN_KEYM,30);
			}
		}
		
		
		
		Key_PM.Key_RetVal = enKey_No;   //标志复位
	}
	//中键被长按中
	if(Key_PM.Key_RetVal == enKey_LongPress)
	{
		
	}	
	//中键被长按
	if(Key_PM.Key_RetVal == enKey_No && Key_PM.Flag_LongPress == true)
	{
		/* 同步参数 */
		if(Show_ui == CAR_ui)
		{
				if(carUIPara.Sync == true) carUIPara.Sync = false;
				else                       
				{
					carUIPara.Sync = true;
					/* 触发一个事件 */
					xEventGroupSetBits(Event_canSendData,EVENT_canCARUIREQ);	
				}
		}
		
		
		Key_PM.Flag_LongPress = false; //标志复位
	}	
	
	//左键被单击
	if(Key_PL.Key_RetVal == enKey_Click)
	{
		if(Car_uiconfigParam.Para_IfControl)  
    {
      if(Car_uiconfigParam.Step_Index >= Car_uiconfigParam.Step_Index_Limit)
           Car_uiconfigParam.Step_Index = 0
			;
      else Car_uiconfigParam.Step_Index++;
    }
    else
    {
      if(Car_uiconfigParam.Page_Index<=0) 
        Car_uiconfigParam.Page_Index=Car_uiconfigParam.Page_Index_Limit; 
      else 
        Car_uiconfigParam.Page_Index--;		
			Car_uiconfigParam.Para_Index=1;         //参数索引复位
			Show_Para_Con(&Car_uiconfigParam);
			Para_Prepare();
      OLED_Clear();
			
			
    }
		if(carUIPara.Sync == true)
		{
			canSendKeyClickData(CAN_KEYL,30);
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
		if(Car_uiconfigParam.Para_IfControl)  
    {
      if(Car_uiconfigParam.Step_Index <= 0)
           Car_uiconfigParam.Step_Index = Car_uiconfigParam.Step_Index_Limit;
      else Car_uiconfigParam.Step_Index--;
    }
    else
    {
      if(Car_uiconfigParam.Page_Index>=Car_uiconfigParam.Page_Index_Limit) 
        Car_uiconfigParam.Page_Index=0; 
      else 
        Car_uiconfigParam.Page_Index++;		
			Car_uiconfigParam.Para_Index=1;         //参数复位
			Show_Para_Con(&Car_uiconfigParam);
			Para_Prepare();			
      OLED_Clear();
    }
		
		if(carUIPara.Sync == true)
		{
			canSendKeyClickData(CAN_KEYR,30);
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
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
      if(Car_uiconfigParam.Para_Index<=1) Car_uiconfigParam.Para_Index = Car_uiconfigParam.Para_Index_Limit[Car_uiconfigParam.Page_Index];
      else              Car_uiconfigParam.Para_Index--;		
			Show_Para_Con(&Car_uiconfigParam);
    }
    else
    { 
			
			
			
		}
		
		if(carUIPara.Sync == true)
		{
			canSendKeyClickData(CAN_KEYU,30);
		}

		Key_PU.Key_RetVal = enKey_No;   //标志复位
	}
	
	//上键被长按中
	if(Key_PU.Key_RetVal == enKey_LongPress)
	{

		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
		
			if(Car_uiconfigParam.Page_Index==2)     //修改第2页参数
      {
				
			}
		}
		
	}
	
	//下键被单击
	if(Key_PD.Key_RetVal == enKey_Click)
	{
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			if(Car_uiconfigParam.Para_Index>=Car_uiconfigParam.Para_Index_Limit[Car_uiconfigParam.Page_Index]) Car_uiconfigParam.Para_Index = 1;
      else              Car_uiconfigParam.Para_Index++;
			Show_Para_Con(&Car_uiconfigParam);
    }
    else
    { 
			
			
		}
		
		if(carUIPara.Sync == true)
		{
			canSendKeyClickData(CAN_KEYD,30);
		}

		Key_PD.Key_RetVal = enKey_No;   //标志复位
	}
	//下键被长按中
	if(Key_PD.Key_RetVal == enKey_LongPress)
	{
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
			;
		}
	}	
}

