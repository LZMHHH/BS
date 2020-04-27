/**
  ******************************************************************************
  * @file    DisplayTask.c
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
#include "DisplayTask.h"

static ui_mode Show_ui = MAIN_ui;


void vTaskDisplay( void * pvParameters )
{
	
	
	while(1)
	{

		
		switch(Show_ui)
		{
			case MAIN_ui:
						Main_uictrl();
						Main_ZUI();
						break;
			default:break;
		}
		
		OLED_Refresh_Gram();
		vTaskDelay( 50 );

	}
	
}

/*设置显示界面*/
void setShow_ui(ui_mode ui)
{
	Show_ui = ui;
	OLED_Clear();
}


//参数显示控制
void Show_Para_Con(CLASS_UIconfigParam* ui_configparam)
{
	int i,c;
	
	c = ui_configparam->Para_Index;
	
	//先清0
	for(i=Num_Para_Max;i>=0;i--)
	{
		ui_configparam->Para_Index_Show[i] = 0;
		
	}
	
	
	if(c > 7)
	{
		//最多显示7行参数
		for(i=7;i>0;i--)
		{
			ui_configparam->Para_Index_Show[c] = 1;
			c--;
		}
	}
	else
	{
		//最多现实7行参数
		for(i=7;i>0;i--)
		{
			ui_configparam->Para_Index_Show[i] = 1;
		}
	}
	
}


