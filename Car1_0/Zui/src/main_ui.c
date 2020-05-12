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

void Main_uiconfigParamInit(void)
{
	Main_uiconfigParam.Page_Index_Limit    = 3;
	
	Main_uiconfigParam.Para_Index_Limit[0] = 7;
	Main_uiconfigParam.Para_Index_Limit[1] = 9;
	Main_uiconfigParam.Para_Index_Limit[2] = 8;
	Main_uiconfigParam.Para_Index_Limit[3] = 7;
	
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
	
	Main_uiconfigParam.Sync                = false;
}

void Main_ZUI(void)
{
	u8 h;    //��ʾ��ϵ��
	u8 Ph;   //������ϵ��
	
	/* �ź� */
	if(uart1Connect.status == enBreak)
	{
		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(2,56,UI_ASIGNAL8X8,8,8);
	}
	if(canConnect.status == enBreak)
	{
		OLED_DrawBMP(12,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	}
	
	/* ҳ�� */
	OLED_ShowChar(109,56,'c',1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	
	//�� 0 ҳ
	if(Main_uiconfigParam.Page_Index == 0)
	{  
		//�߽�
		OLED_ShowNum(0,(7-6)*8,Hwbz_LD.status,1,0,2);
		OLED_ShowNum(0,(7-1)*8,Hwbz_LU.status,1,0,2);
		OLED_ShowNum(120,(7-1)*8,Hwbz_RU.status,1,0,2);
		OLED_ShowNum(120,(7-6)*8,Hwbz_RD.status,1,0,2);
		OLED_ShowNum(0,(7-5)*8,MotorA.encoderVal,4,0,1);
		OLED_ShowNum(0,(7-3)*8,MotorB.encoderVal,4,0,1);
		OLED_ShowNum(104,(7-3)*8,MotorC.encoderVal,4,0,1);
		OLED_ShowNum(104,(7-5)*8,MotorD.encoderVal,4,0,1);
		
		//1��2��
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
		
		//4��
		OLED_ShowNum(40,(7-h)*8,Distance.xmm,5,0,2);
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
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorA.pwmout,6,0,1);
			h++;
	  }
		
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorA.encoderVal,6,0,1);
			h++;
	  }
		
		//3��
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorB.pwmout,6,0,1);
			h++;
	  }
		
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorB.encoderVal,6,0,1);
			h++;
	  }
		
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorC.pwmout,6,0,1);
			h++;
	  }
		
		//6��
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorC.encoderVal,6,0,1);
			h++;
	  }
		
		//7��
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorD.pwmout,6,0,1);
			h++;
	  }
		
		//8��
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorD.encoderVal,6,0,1);
			h++;
	  }
		
		//9��
	  Ph = 9;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
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
	
	//�� 2 ҳ
	if(Main_uiconfigParam.Page_Index == 2)
	{  
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,3,1);
		
		h = 1;
		//1��
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarM :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarM :",1);
			}		
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
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
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarMP:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"CarMP:",1);
			}		
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
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
		//3��
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
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
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
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
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
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
		//6��
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtP  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtP  :",1);
			}		
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
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
		//7��
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtI  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtI  :",1);
			}		
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
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
		//8��
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtD  :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MtD  :",1);
			}		
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == true)
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
	
	//�� 3 ҳ
	if(Main_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index],3,3,1);
		
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
					OLED_ShowString(0,(7-h)*8,(u8 *)"Fmqc :",1); //LedA����˸����
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
    if(Main_uiconfigParam.Para_IfControl==false && ((Main_uiconfigParam.Page_Index == 1) || (Main_uiconfigParam.Page_Index == 2) || (Main_uiconfigParam.Page_Index == 3))) 
			 Main_uiconfigParam.Para_IfControl=true;    //�ɿ�ҳ
    else                                                                  
			 Main_uiconfigParam.Para_IfControl=false;

		if(Main_uiconfigParam.Page_Index==0)    
    {
			/* �л�UImode */
			Change_UIMode();
		}
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
			
			
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2����
      {
				//������
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Car.mode)
							{
								case enPWM:
											Car.mode = enPID;
											break;
								case enPID:
											Car.mode = enPWMSelf;
											break;
								case enPWMSelf:
											Car.mode = enPIDSelf;
											break;
								case enPIDSelf:
											Car.mode = enPWMGS;
											break;
								case enPWMGS:
											Car.mode = enPIDGS;
											break;
								case enPIDGS:
											Car.mode = enPWM;
											break;
								default:
											Car.mode = enPWM;
											break;
							}
							break;;
					case 2:
							Car.MaxPwm += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Car.MaxPwm > 30000) Car.MaxPwm = 30000;
							break;
					case 4:
							Distance.offset += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Distance.offset > 30000) Distance.offset = 30000;
							break;
					case 5:
							Distance.shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Distance.shieldVal > 30000) Distance.shieldVal = 30000;
							break;
					case 6:
							MotorAllPID.p += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.p > 999) MotorAllPID.p = 999;
							break;
					case 7:
							MotorAllPID.i += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.i > 999) MotorAllPID.i = 999;
							break;
					case 8:
							MotorAllPID.d += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.d > 999) MotorAllPID.d = 999;
							break;
					default:break;
				}
			}
			
			if(Main_uiconfigParam.Page_Index==3)     //�޸ĵ�3����
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
							sendRmotorData(enIDCar,KIND_LED,(u8*)&LedA,sizeof(LedA),10);
							break;
					case 2:
							LedA.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedA.cycle > 10000) LedA.cycle = 10000;
							sendRmotorData(enIDCar,KIND_LED,(u8*)&LedA,sizeof(LedA),10);
							break;
					case 3:
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
							sendRmotorData(enIDCar,KIND_LED,(u8*)&Fmq,sizeof(Fmq),10);
							break;
					case 4:
							Fmq.cycle += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle > 10000) Fmq.cycle = 10000;
							sendRmotorData(enIDCar,KIND_LED,(u8*)&Fmq,sizeof(Fmq),10);
							break;
					default:break;
				}
			}
			
			
		}

		if(Main_uiconfigParam.Page_Index==0)     //�޸ĵ�0����
		{
			switch(Car.mode)
			{
				case enPWM:
							Car.mode = enPID;
							break;
				case enPID:
							Car.mode = enPWMSelf;
							break;
				case enPWMSelf:
							Car.mode = enPIDSelf;
							break;
				case enPIDSelf:
							Car.mode = enPWMGS;
							break;
				case enPWMGS:
							Car.mode = enPIDGS;
							break;
				case enPIDGS:
							Car.mode = enPWM;
							break;
				default:
							Car.mode = enPWM;
							break;
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
		
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				
			}
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
			
			
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2����
      {
				//������
				switch(Main_uiconfigParam.Para_Index)
				{
					case 1:
							switch(Car.mode)
							{
								case enPIDGS:
											Car.mode = enPWMGS;
											break;
								case enPWMGS:
											Car.mode = enPIDSelf;
											break;
								case enPIDSelf:
											Car.mode = enPWMSelf;
											break;
								case enPWMSelf:
											Car.mode = enPID;
											break;
								case enPID:
											Car.mode = enPWM;
											break;
								case enPWM:
											Car.mode = enPIDGS;
											break;
								default:
											Car.mode = enPWM;
											break;
							}
							break;;
					case 2:
							Car.MaxPwm -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Car.MaxPwm <= 0) Car.MaxPwm = 0;
							break;
					case 4:
							Distance.offset -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Distance.offset < -5000) Distance.offset = -5000;
							break;
					case 5:
							Distance.shieldVal += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Distance.shieldVal <= 0) Distance.shieldVal = 0;
							break;
					case 6:
							MotorAllPID.p += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.p < -99) MotorAllPID.p = -99;
							break;
					case 7:
							MotorAllPID.i += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.i < -99) MotorAllPID.i = -99;
							break;
					case 8:
							MotorAllPID.d += Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(MotorAllPID.d < -99) MotorAllPID.d = -99;
							break;
					default:break;
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
							sendRmotorData(enIDCar,KIND_LED,(u8*)&LedA,sizeof(LedA),10);
							break;
					case 2:
							LedA.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(LedA.cycle <  -1) LedA.cycle =  -1;
							sendRmotorData(enIDCar,KIND_LED,(u8*)&LedA,sizeof(LedA),10);
							break;
					case 3:
							switch(Fmq.flag_mode)
							{
								case enON:
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
							sendRmotorData(enIDCar,KIND_LED,(u8*)&Fmq,sizeof(Fmq),10);
							break;
					case 4:
							Fmq.cycle -= Main_uiconfigParam.Step_Size[Main_uiconfigParam.Step_Index];
							if(Fmq.cycle <  -1) Fmq.cycle =  -1;
							sendRmotorData(enIDCar,KIND_LED,(u8*)&Fmq,sizeof(Fmq),10);
							break;
					default:break;
				}
			}
				
			
		}

		if(Main_uiconfigParam.Page_Index==0)     //�޸ĵ�0����
      {
				switch(Car.mode)
				{
					case enPIDGS:
								Car.mode = enPWMGS;
								break;
					case enPWMGS:
								Car.mode = enPIDSelf;
								break;
					case enPIDSelf:
								Car.mode = enPWMSelf;
								break;
					case enPWMSelf:
								Car.mode = enPID;
								break;
					case enPID:
								Car.mode = enPWM;
								break;
					case enPWM:
								Car.mode = enPIDGS;
								break;
					default:
								Car.mode = enPWM;
								break;
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
