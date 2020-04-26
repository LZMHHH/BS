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
	Main_uiconfigParam.Para_Index_Limit[1] = 7;
	Main_uiconfigParam.Para_Index_Limit[2] = 8;
	Main_uiconfigParam.Para_Index_Limit[3] = 7;
	Main_uiconfigParam.Para_Index_Limit[4] = 7;
	Main_uiconfigParam.Para_Index_Limit[5] = 7;
	
	Main_uiconfigParam.Step_Index_Limit    = 6;
	
	Main_uiconfigParam.Step_Size[0]        =   0.001;
	Main_uiconfigParam.Step_Size[1]        =   0.01;
	Main_uiconfigParam.Step_Size[2]        =   0.1;
	Main_uiconfigParam.Step_Size[3]        =   1.0;
	Main_uiconfigParam.Step_Size[4]        =  10.0;
	Main_uiconfigParam.Step_Size[5]        = 100.0;
	
	Show_Para_Con(&Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 1;
	Main_uiconfigParam.Page_Index          = 2;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
}

void Main_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	
	/* 页面 */
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	/* 信号 */
	OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	
	//第 0 页
	if(Main_uiconfigParam.Page_Index == 0)
	{  
	
	}
	
	//第 2 页
	if(Main_uiconfigParam.Page_Index == 2)
	{  
		h = 1;
		//1行
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MApwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MApwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorA.pwmout,6,0,1);
			h++;
	  }
		
		//2行
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MAenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MAenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorA.encoderVal,6,0,1);
			h++;
	  }
		
		//3行
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MBpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MBpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorB.pwmout,6,0,1);
			h++;
	  }
		
		//4行
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MBenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MBenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorB.encoderVal,6,0,1);
			h++;
	  }
		
		//5行
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MCpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MCpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorC.pwmout,6,0,1);
			h++;
	  }
		
		//6行
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MCenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MCenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorC.encoderVal,6,0,1);
			h++;
	  }
		
		//7行
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MDpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MDpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorD.pwmout,6,0,1);
			h++;
	  }
		
		//8行
	  Ph = 8;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Main_uiconfigParam.Para_Index == Ph && Main_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,"MDenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,"MDenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,MotorD.encoderVal,6,0,1);
			h++;
	  }
		
	
		
	}
	
	
	//第 3 页
	if(Main_uiconfigParam.Page_Index == 3)
	{  
		OLED_ShowNum(0,0,mpu_data.Acceleration_X,4,2,1);
		OLED_ShowNum(0,8,mpu_data.Acceleration_Y,4,2,1);
		OLED_ShowNum(0,16,mpu_data.Acceleration_Z,4,2,1);		
		OLED_ShowNum(60,16,mpu_data.Gyro_BalanceZ,4,2,1);
	}
	
	
}




//预备参数,防止无线控制更新参数   内部
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
           Main_uiconfigParam.Step_Index = 0;
      else Main_uiconfigParam.Step_Index++;
    }
    else
    {
      Main_uiconfigParam.Para_Index=1;         //参数复位
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();
      if(Main_uiconfigParam.Page_Index<=0) 
        Main_uiconfigParam.Page_Index=Main_uiconfigParam.Page_Index_Limit; 
      else 
        Main_uiconfigParam.Page_Index--;
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
      Main_uiconfigParam.Para_Index=1;         //参数复位
			Show_Para_Con(&Main_uiconfigParam);
			Para_Prepare();
      if(Main_uiconfigParam.Page_Index>=Main_uiconfigParam.Page_Index_Limit) 
        Main_uiconfigParam.Page_Index=0; 
      else 
        Main_uiconfigParam.Page_Index++;
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
