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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "DisplayTask.h"

ui_mode Show_ui = MAIN_ui;

volatile TickType_t SendUITickCount; //���ڶ�ʱ�ϴ�����

static void Para_Init(void);

void vTaskDisplay( void * pvParameters )
{
	Para_Init();
	
	while(1)
	{

		
		switch(Show_ui)
		{
			case MAIN_ui:
						Main_uictrl();
						Main_ZUI();
						break;
			case CAR_ui:
						Car_uictrl();
						Car_ZUI();
						break;
			case ENVI_ui:
						Envi_uictrl();
						Envi_ZUI();
						break;
			default:break;
		}
		
		if((xTaskGetTickCount()-200) > SendUITickCount)
		{
			if(carUIPara.Sync == true)
			{
				/* ����һ���¼� */
				xEventGroupSetBits(Event_uart3SendData,EVENT_uart3CARUIREQ);	
			}
					
			SendUITickCount = xTaskGetTickCount();
		}
		if(SendUITickCount > xTaskGetTickCount())
		{
			SendUITickCount = xTaskGetTickCount();
		}
		
		OLED_Refresh_Gram();
		vTaskDelay( 50 );

	}
	
}

/*������ʾ����*/
void setShow_ui(ui_mode ui)
{
	Show_ui = ui;
	OLED_Clear();
}

/*��ʾ��ʼ��*/
static void Para_Init(void)
{
	Main_uiconfigParamInit();
	Car_uiconfigParamInit();
	Envi_uiconfigParamInit();
}

//������ʾ����
void Show_Para_Con(CLASS_UIconfigParam* ui_configparam)
{
	int i,c;
	
	c = ui_configparam->Para_Index;
	
	//����0
	for(i=Num_Para_Max;i>=0;i--)
	{
		ui_configparam->Para_Index_Show[i] = 0;
		
	}
	
	
	if(c > 7)
	{
		//�����ʾ7�в���
		for(i=7;i>0;i--)
		{
			ui_configparam->Para_Index_Show[c] = 1;
			c--;
		}
	}
	else
	{
		//�����ʵ7�в���
		for(i=7;i>0;i--)
		{
			ui_configparam->Para_Index_Show[i] = 1;
		}
	}
	
}

void Change_UIMode(void)
{
	/* �л���ʾģʽ */
	switch(Show_ui)
	{
		case MAIN_ui:
					Show_ui = CAR_ui;			
					break;
		case CAR_ui:
					Show_ui = ENVI_ui;
					break;
		case ENVI_ui:
					Show_ui = MAIN_ui;
					break;
		default:break;
	}
	OLED_Fill(0,0,128,64,0);
}


/* ͨѶ */
void canSendCarUIReqCmd(void)
{
	sendCmd(DOWN_REMOTOR,KIND_UIREQ,UIREQ_CAR,20);
}





