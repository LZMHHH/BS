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

ui_mode Show_ui = MAIN_ui;


void vTaskDisplay( void * pvParameters )
{
	
	
	while(1)
	{

		
		switch(Show_ui)
		{
			case MAIN_ui:
						Main_uictrl();
						if(Show_ui != MAIN_ui) OLED_Fill(0,0,128,64,0);
						else                   Main_ZUI();
						break;
			case ENVI_ui:
						Envi_uictrl();
						if(Show_ui != ENVI_ui) OLED_Fill(0,0,128,64,0);
						else                  Envi_ZUI();
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

/*显示初始化*/
void DisplayInit(void)
{
	Main_uiconfigParamInit();
	Envi_uiconfigParamInit();
}

//参数显示控制
void Show_Para_Con(CLASS_UIconfigParam *ui_configparam)
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

void Change_UIMode(void)
{
	/* 切换显示模式 */
	switch(Show_ui)
	{
		case MAIN_ui:
					Show_ui = ENVI_ui;			
					break;
		case ENVI_ui:
					Show_ui = MAIN_ui;
					break;
		default:break;
	}
}

/* 通讯 */

void canSendCarUIData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_UIID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARUI;
					p.Data[3] = CAN_UIStepIndex;
					p.Data[4] = Main_uiconfigParam.Step_Index;
					xQueueSend(xQueue_canTx, &p, 30);
					
					p.Data[3] = CAN_UIPageIndex;
					p.Data[4] = Main_uiconfigParam.Page_Index;
					xQueueSend(xQueue_canTx, &p, 30);
					break;
		case 1:
					flag = 0;
					p.StdId = CAN_UIID;
					p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* 向CAN网络发送8个字节数据 */
					p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
					p.Data[0] = enIDCar;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARUI;
					p.Data[3] = CAN_UIPageIndexLast;
					p.Data[4] = Main_uiconfigParam.Page_Index_Last;
					xQueueSend(xQueue_canTx, &p, 30);				
		
					p.Data[3] = CAN_UIPareIndex;
					p.Data[4] = Main_uiconfigParam.Para_Index;
					xQueueSend(xQueue_canTx, &p, 30);
		
					p.Data[3] = CAN_UIParaIfControl;
					p.Data[4] = Main_uiconfigParam.Para_IfControl;
					xQueueSend(xQueue_canTx, &p, 30);
					break;
					default:
								flag = 0;	
								break;
	}
	
}				

void canSendEnvUIReqCmd(void)
{
	CanTxMsg p;

	p.StdId = CAN_UIID;
	p.ExtId = 0x01;  /* 该函数使用STD帧ID，所以ExtID用不到 */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* 向CAN网络发送8个字节数据 */
	p.DLC = 8;          /* 每包数据支持0-8个字节，这里设置为发送8个字节 */
	p.Data[0] = enIDCar;   
	p.Data[1] = enCMD;
	p.Data[2] = CAN_ENVUI;
	p.Data[3] = CAN_UIReq;
	xQueueSend(xQueue_canTx, &p, 10);
					
	
}	

void SendCarUIData(void)
{
	carUIPara.Step_Index = Main_uiconfigParam.Step_Index;
	carUIPara.Page_Index = Main_uiconfigParam.Page_Index;
	carUIPara.Page_Index_Last = Main_uiconfigParam.Page_Index_Last;
	carUIPara.Para_Index = Main_uiconfigParam.Para_Index;
	carUIPara.Para_IfControl = Main_uiconfigParam.Para_IfControl;
	sendData(UP_DATA,enIDCar,KIND_UI,(u8 *)&carUIPara,sizeof(carUIPara),20);
	
}	

void SendEnvUIData(void)
{
	canSendEnvUIReqCmd();
	envUIPara.Step_Index = Envi_uiconfigParam.Step_Index;
	envUIPara.Page_Index = Envi_uiconfigParam.Page_Index;
	envUIPara.Page_Index_Last = Envi_uiconfigParam.Page_Index_Last;
	envUIPara.Para_Index = Envi_uiconfigParam.Para_Index;
	envUIPara.Para_IfControl = Envi_uiconfigParam.Para_IfControl;
	sendData(UP_DATA,enIDEnvironment,KIND_UI,(u8 *)&envUIPara,sizeof(envUIPara),20);
	
}	
