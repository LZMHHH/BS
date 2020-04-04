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

/* 显示数据 */
CLASS_Joystick uiJoystick_Left;
CLASS_Joystick uiJoystick_Right;

/* 接收需要显示的数据 */
void RxUidata(void)
{
	/*先读空，再发送*/
	xQueueReceive( vQueue_JoystickLeft,        /* 消息队列的句柄 */
                             (void *)&uiJoystick_Left,      /* 发送的消息内容 */
                             0);                       /* 不等待 */
														 
														 
	/*先读空，再发送*/
	xQueueReceive( vQueue_JoystickRight,       /* 消息队列的句柄 */
                             (void *)&uiJoystick_Right,      /* 发送的消息内容 */
                             0);                       /* 不等待 */
														 
}

void Main_ZUI(void)
{
	u8 h;    //显示行系数
	u8 Ph;   //参数行系数
	
	
	/* 更新显示数据 */
	RxUidata();
	
	OLED_ShowChar(115,3,'P',1);
  OLED_ShowNum(121,3,Main_uiconfigParam.Page_Index,1,0,1);
	
	//第 0 页
	if(Main_uiconfigParam.Page_Index == 0)
	{  

		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);
		
		OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	
		OLED_ShowNum(20,56,uiJoystick_Left.NorY,5,2,1);
		OLED_ShowNum(20,46,uiJoystick_Left.NorX,5,2,1);
		OLED_ShowNum(20,36,uiJoystick_Right.NorY,5,2,1);
		OLED_ShowNum(20,26,uiJoystick_Right.NorX,5,2,1);
		OLED_ShowNum(20,16,getAdcValue(ADC_BAT),5,2,1);
	}
	
	//第 1 页
	if(Main_uiconfigParam.Page_Index == 1)
	{  


	}
	
	
	
}


void Main_uiconfigParamInit(void)
{
	Main_uiconfigParam.Page_Index_Limit    = 3;
	
	Main_uiconfigParam.Para_Index_Limit[0] = 7;
	Main_uiconfigParam.Para_Index_Limit[1] = 7;
	Main_uiconfigParam.Para_Index_Limit[2] = 7;
	Main_uiconfigParam.Para_Index_Limit[3] = 7;
	
	Main_uiconfigParam.Step_Index_Limit    = 6;
	
	Main_uiconfigParam.Step_Size[0]        =   0.001;
	Main_uiconfigParam.Step_Size[1]        =   0.01;
	Main_uiconfigParam.Step_Size[2]        =   0.1;
	Main_uiconfigParam.Step_Size[3]        =   1.0;
	Main_uiconfigParam.Step_Size[4]        =  10.0;
	Main_uiconfigParam.Step_Size[5]        = 100.0;
	
	Show_Para_Con(Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 1;
	Main_uiconfigParam.Page_Index          = 1;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
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
			Show_Para_Con(Main_uiconfigParam);
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
			Show_Para_Con(Main_uiconfigParam);
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
			Show_Para_Con(Main_uiconfigParam);
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
			Show_Para_Con(Main_uiconfigParam);
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
