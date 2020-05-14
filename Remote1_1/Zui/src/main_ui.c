/**
  ******************************************************************************
  * @file    main.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ui��ʾ�ļ�����ģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */

#include "main_ui.h"


CLASS_UIconfigParam Main_uiconfigParam;
static u16 save_numA = 0;
static u16 save_numB = 0;

void Main_uiconfigParamInit(void)
{
	Main_uiconfigParam.Page_Index_Limit    = 3;
	
	Main_uiconfigParam.Para_Index_Limit[0] = 7;
	Main_uiconfigParam.Para_Index_Limit[1] = 5;
	Main_uiconfigParam.Para_Index_Limit[2] = 11;
	Main_uiconfigParam.Para_Index_Limit[3] = 9;
	
	Main_uiconfigParam.Step_Index_Limit    = 4;
	
	Main_uiconfigParam.Step_Size[0]        =   0.01;
	Main_uiconfigParam.Step_Size[1]        =   0.1;
	Main_uiconfigParam.Step_Size[2]        =   1.0;
	Main_uiconfigParam.Step_Size[3]        =   10.0;
	Main_uiconfigParam.Step_Size[4]        =  100.0;
	
	Show_Para_Con(&Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 2;
	Main_uiconfigParam.Page_Index          = 1;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
}


void Main_ZUI(void)
{
	u8 h;    //��ʾ��ϵ��
	u8 Ph;   //������ϵ��
	
	Show_Para_Con(&Main_uiconfigParam);
	
	/* �ź� */
	if(uart3Connect.status == enBreak)
	{
		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(2,56,UI_ASIGNAL8X8,8,8);
	}
	
	/* ҳ�� */
	OLED_ShowChar(97,56,'r',1);
	OLED_ShowNum(103,56,Main_uiconfigParam.Para_Index,2,0,1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	//�� 0 ҳ
	if(Main_uiconfigParam.Page_Index == 0)
	{  
			
		
	}
	
	//�� 1 ҳ
	if(Main_uiconfigParam.Page_Index == 1)
	{  
		h = 1;
		//1��
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyLX :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyLX :",1);
			}	
			OLED_ShowNum(92,(7-h)*8,Joystick_Left.NorX,6,0,1);
			h++;
	  }
		
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyLY :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyLY :",1);
			}	
			OLED_ShowNum(92,(7-h)*8,Joystick_Left.NorY,6,0,1);
			h++;
	  }
		
		//3��
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyRX :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyRX :",1);
			}	
			OLED_ShowNum(92,(7-h)*8,Joystick_Right.NorX,6,0,1);
			h++;
	  }
		
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyRY :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"JoyRY :",1);
			}	
			OLED_ShowNum(92,(7-h)*8,Joystick_Right.NorY,6,0,1);
			h++;
	  }
		
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"mpuAnX:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"mpuAnX:",1);
			}	
			OLED_ShowNum(86,(7-h)*8,mpu_data.Angle_BalanceX,5,1,1);
			h++;
	  }
	}
	
	//�� 2 ҳ
	if(Main_uiconfigParam.Page_Index == 2)
	{  
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,2,1);
		h = 1;
		//1��
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RJoyM:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RJoyM:",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Joystick_Right.Mode)
					{
						case enCar:
									OLED_ShowString(92,(7-h)*8,(u8 *)"   Car",1);
									break;
						case enEnv:
									OLED_ShowString(92,(7-h)*8,(u8 *)"   Env",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Joystick_Right.Mode)
					{
						case enCar:
									OLED_ShowString(92,(7-h)*8,(u8 *)"   Car",1);
									break;
						case enEnv:
									OLED_ShowString(92,(7-h)*8,(u8 *)"   Env",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RJoyG:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RJoyG:",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(Joystick_Right.Grade)
					{
						case enGA:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     A",1);
									break;
						case enGB:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     B",1);
									break;
						case enGC:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     C",1);
									break;
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(Joystick_Right.Grade)
					{
						case enGA:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     A",1);
									break;
						case enGB:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     B",1);
									break;
						case enGC:
									OLED_ShowString(92,(7-h)*8,(u8 *)"     C",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		//3��
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LXZS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LXZS :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.XZeroSet,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.XZeroSet,6,0,1);
			}
			h++;
	  }
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LYZS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LYZS :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.YZeroSet,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.YZeroSet,6,0,1);
			}
			h++;
	  }
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RXZS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RXZS :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.XZeroSet,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.XZeroSet,6,0,1);
			}
			h++;
	  }
		//6��
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RYZS :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RYZS :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.YZeroSet,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.YZeroSet,6,0,1);
			}
			h++;
	  }
		//7��
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LXSV :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LXSV :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.XShieldVal,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.XShieldVal,6,0,1);
			}
			h++;
	  }
		//8��
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LYSV :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LYSV :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.YShieldVal,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Left.YShieldVal,6,0,1);
			}
			h++;
	  }
		//9��
	  Ph = 9;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RXSV :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RXSV :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.XShieldVal,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.XShieldVal,6,0,1);
			}
			h++;
	  }
		//10��
	  Ph = 10;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"RYSV :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"RYSV :",1);
			}
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.YShieldVal,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,Joystick_Right.YShieldVal,6,0,1);
			}
			h++;
	  }
		//11��
	  Ph = 11;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SaveA:",1); //LedB����˸����
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SaveA:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(92,(7-h)*8,save_numA,6,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(92,(7-h)*8,save_numA,6,0,1);
			}
			h++;
	  }
	}
	
	//�� 3 ҳ
	if(Main_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,2,1);
		
		h = 1;
		//1��
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedAc:",1); //LedA����˸����
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
		
		//3��
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedBc:",1); //LedB����˸����
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
		
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedCs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedCs:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(LedC.flag_mode)
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
						default:break;
					}
					Oled_Colour = 0;				
			}
			else
			{
					switch(LedC.flag_mode)
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
						default:break;
					}
			}
			h++;
	  }
		
		//6��
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedCc:",1); //LedB����˸����
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"LedCc:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,LedC.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,LedC.cycle,5,0,1);
			}
			h++;
	  }
		
		//7��
	  Ph = 7;
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
									break;
						default:break;
					}
			}
			h++;
	  }
		
		//8��
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqc :",1); //LedB����˸����
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
		//9��
	  Ph = 9;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"SaveB:",1); //LedB����˸����
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"SaveB:",1);
			}	
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,save_numB,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,save_numB,5,0,1);
			}
			h++;
	  }
		
	}
	
	
	
}






//Ԥ������,��ֹ���߿��Ƹ��²���   �ڲ�
static void Para_Prepare(void)
{
  if(Main_uiconfigParam.Page_Index_Last != Main_uiconfigParam.Page_Index)
  {
    Main_uiconfigParam.Page_Index_Last = Main_uiconfigParam.Page_Index;
    OLED_Clear();
  }
  
  if(Main_uiconfigParam.Page_Index==2)
  {
     ;
  }

}

void Main_uictrl(void)
{

	
	//�м�������
	if(Key_PM.Key_RetVal == enKey_Click)
	{
    if(Main_uiconfigParam.Para_IfControl==false && ((Main_uiconfigParam.Page_Index == 1) 
																								 || (Main_uiconfigParam.Page_Index == 2) 
																								 || (Main_uiconfigParam.Page_Index == 3))) 
			 Main_uiconfigParam.Para_IfControl=true;    //�ɿ�ҳ
    else                                                                  
			 Main_uiconfigParam.Para_IfControl=false;

		
		Key_PM.Key_RetVal = enKey_No;   //��־��λ
	}
	//�м���������
	if(Key_PM.Key_RetVal == enKey_LongPress)
	{
		
	}	
	
	//���������
	if(Key_PL.Key_RetVal == enKey_Click)
	{
		if(Main_uiconfigParam.Para_IfControl)  
    {
      if(Main_uiconfigParam.Step_Index >= Main_uiconfigParam.Step_Index_Limit)
           Main_uiconfigParam.Step_Index = 0;
      else Main_uiconfigParam.Step_Index++;
    }
    else
    {
      if(Main_uiconfigParam.Page_Index<=0) 
        Main_uiconfigParam.Page_Index=Main_uiconfigParam.Page_Index_Limit; 
      else 
        Main_uiconfigParam.Page_Index--;
			Main_uiconfigParam.Para_Index=1;         //������λ
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();
      OLED_Clear();
    }

		Key_PL.Key_RetVal = enKey_No;   //��־��λ
	}
	//�����������
	if(Key_PL.Key_RetVal == enKey_LongPress)
	{
		
	}
	
	//�Ҽ�������
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
			Main_uiconfigParam.Para_Index=1;         //������λ
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();
      OLED_Clear();
    }
		
		Key_PR.Key_RetVal = enKey_No;   //��־��λ
	}
	//�Ҽ���������
	if(Key_PR.Key_RetVal == enKey_LongPress)
	{
		
	}	
	
	//�ϼ�������
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
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				//������
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Joystick_Right.Mode)
							{
								case enCar:
											Joystick_Right.Mode = enEnv;
											break;
								case enEnv:
											Joystick_Right.Mode = enCar;
											break;
								default:
											Joystick_Right.Mode = enCar;
											break;
							}
							break;
					case 2:
							switch(Joystick_Right.Grade)
							{
								case enGA:
											Joystick_Right.Grade = enGB;
											break;
								case enGB:
											Joystick_Right.Grade = enGC;
											break;
								case enGC:
											Joystick_Right.Grade = enGA;
											break;
								default:
											Joystick_Right.Grade = enGA;
											break;
							}
							break;
					case 3:
							Joystick_Left.XZeroSet += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.XZeroSet > 10000) Joystick_Left.XZeroSet = 10000;
							break;
					case 4:
							Joystick_Left.YZeroSet += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.YZeroSet > 10000) Joystick_Left.YZeroSet = 10000;
							break;
					case 5:
							Joystick_Right.XZeroSet += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.XZeroSet > 10000) Joystick_Right.XZeroSet = 10000;
							break;
					case 6:
							Joystick_Right.YZeroSet += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.YZeroSet > 10000) Joystick_Right.YZeroSet = 10000;
							break;
					case 7:
							Joystick_Left.XShieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.XShieldVal > 10000) Joystick_Left.XShieldVal = 10000;
							break;
					case 8:
							Joystick_Left.YShieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.YShieldVal > 10000) Joystick_Left.YShieldVal = 10000;
							break;
					case 9:
							Joystick_Right.XShieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.XShieldVal > 10000) Joystick_Right.XShieldVal = 10000;
							break;
					case 10:
							Joystick_Right.YShieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.YShieldVal > 10000) Joystick_Right.YShieldVal = 10000;
							break;
					case 11:
							SaveFlashJoyData();
							save_numA++;
							break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==3)     //�޸ĵ�3ҳ����
      {
				//������
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
							switch(LedC.flag_mode)
							{
								case enON:
											LedC.flag_mode = enOFF;
											break;
								case enOFF:
											LedC.flag_mode = enFre;
											break;
								case enFre:
											LedC.flag_mode = enON;
											break;
								default:
											LedC.flag_mode = enON;
											break;
							}
							break;
					case 6:
							LedC.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedC.cycle > 10000) LedC.cycle = 10000;
							break;
					case 7:
							switch(Fmq.flag_mode)
							{
								case enON:
											Fmq.flag_mode = enOFF;
											break;
								case enOFF:
											Fmq.flag_mode = enFre;
											break;
								case enFre:
											Fmq.flag_mode = enON;
											break;
								default:
											Fmq.flag_mode = enON;
											break;
							}
							break;
					case 8:
							Fmq.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle > 10000) Fmq.cycle = 10000;
							break;
					default:break;
				}
			}
			
		}

		Key_PU.Key_RetVal = enKey_No;   //��־��λ
	}
	
	//�ϼ���������
	if(Key_PU.Key_RetVal == enKey_LongPress)
	{

		if(Main_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
		
			
		}
		
	}
	
	//�¼�������
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
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				//������
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Joystick_Right.Mode)
							{
								case enCar:
											Joystick_Right.Mode = enEnv;
											break;
								case enEnv:
											Joystick_Right.Mode = enCar;
											break;
								default:
											Joystick_Right.Mode = enCar;
											break;
							}
							break;
					case 2:
							switch(Joystick_Right.Grade)
							{
								case enGC:
											Joystick_Right.Grade = enGB;
											break;
								case enGB:
											Joystick_Right.Grade = enGA;
											break;
								case enGA:
											Joystick_Right.Grade = enGC;
											break;
								default:
											Joystick_Right.Grade = enGA;
											break;
							}
							break;
					case 3:
							Joystick_Left.XZeroSet -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.XZeroSet < -9999) Joystick_Left.XZeroSet = -9999;
							break;
					case 4:
							Joystick_Left.YZeroSet -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.YZeroSet < -9999) Joystick_Left.YZeroSet = -9999;
							break;
					case 5:
							Joystick_Right.XZeroSet -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.XZeroSet < -9999) Joystick_Right.XZeroSet = -9999;
							break;
					case 6:
							Joystick_Right.YZeroSet -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.YZeroSet < -9999) Joystick_Right.YZeroSet = -9999;
							break;
					case 7:
							Joystick_Left.XShieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.XShieldVal < -9999) Joystick_Left.XShieldVal = -9999;
							break;
					case 8:
							Joystick_Left.YShieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Left.YShieldVal < -9999) Joystick_Left.YShieldVal = -9999;
							break;
					case 9:
							Joystick_Right.XShieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.XShieldVal < -9999) Joystick_Right.XShieldVal = -9999;
							break;
					case 10:
							Joystick_Right.YShieldVal -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Joystick_Right.YShieldVal < -9999) Joystick_Right.YShieldVal = -9999;
							break;
					case 11:
							SaveFlashJoyData();
							save_numA++;
							break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==3)     //�޸ĵ�3ҳ����
      {
				//������
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(LedA.flag_mode)
							{
								case enON:
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
							switch(LedC.flag_mode)
							{
								case enON:
											LedC.flag_mode = enFre;
											break;
								case enFre:
											LedC.flag_mode = enOFF;
											break;
								case enOFF:
											LedC.flag_mode = enON;
											break;
								default:
											LedC.flag_mode = enON;
											break;
							}
							break;
					case 6:
							LedC.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedC.cycle <  -1) LedC.cycle =  -1;
							break;
					case 7:
							switch(Fmq.flag_mode)
							{
								case enON:
											Fmq.flag_mode = enOFF;
											break;
								case enOFF:
											Fmq.flag_mode = enFre;
											break;
								case enFre:
											Fmq.flag_mode = enON;
											break;
								default:
											Fmq.flag_mode = enON;
											break;
							}
							break;
					case 8:
							Fmq.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle < -1) Fmq.cycle = -1;
							break;
					default:break;
				}
			}
				
			
		}

		Key_PD.Key_RetVal = enKey_No;   //��־��λ
	}
	//�¼���������
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






