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
						if(Show_ui != MAIN_ui) OLED_Fill(0,0,128,64,0);
						else                   Main_ZUI();
						break;
			case CAR_ui:
						Car_uictrl();
						if(Show_ui != CAR_ui) OLED_Fill(0,0,128,64,0);
						else                  Car_ZUI();
						break;
			default:break;
		}
		
		if((xTaskGetTickCount()-200) > SendUITickCount)
		{
			if(carUIPara.Sync == true)
			{
				/* ����һ���¼� */
				xEventGroupSetBits(Event_canSendData,EVENT_canCARUIREQ);	
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
}

//������ʾ����
void Show_Para_Con(CLASS_UIconfigParam *ui_configparam)
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
					if(carUIPara.Sync == true)                      
					{
						carUIPara.Sync = true;
						/* ����һ���¼� */
						xEventGroupSetBits(Event_canSendData,EVENT_canCARUIREQ);	
					}
					break;
		case CAR_ui:
					Show_ui = MAIN_ui;				
					break;
		default:break;
	}
}

/* ͨѶ */

void canSendCarUIData(void)
{
	static u8 flag = 0;
	
	CanTxMsg p;
	
	carUIPara.Step_Index = Car_uiconfigParam.Step_Index;
	carUIPara.Page_Index = Car_uiconfigParam.Page_Index;
	carUIPara.Page_Index_Last = Car_uiconfigParam.Page_Index_Last;
	carUIPara.Para_Index = Car_uiconfigParam.Para_Index;
	carUIPara.Para_IfControl = Car_uiconfigParam.Para_IfControl;

	switch(flag)
	{
		case 0:
					flag++;
					p.StdId = CAN_UIID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARUI;
					p.Data[3] = CAN_UIStepIndex;
					p.Data[4] = carUIPara.Step_Index;
					xQueueSend(xQueue_canTx, &p, 10);
					
					p.Data[3] = CAN_UIPageIndex;
					p.Data[4] = carUIPara.Page_Index;
					xQueueSend(xQueue_canTx, &p, 10);
					break;
		case 1:
					flag = 0;
					/* ����sht3x���¶����� */
					p.StdId = CAN_UIID;
					p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
					p.RTR = CAN_RTR_DATA;
					p.IDE = CAN_ID_STD;	
					/* ��CAN���緢��8���ֽ����� */
					p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
					p.Data[0] = enIDEnvironment;   
					p.Data[1] = enDATA;
					p.Data[2] = CAN_CARUI;
					p.Data[3] = CAN_UIPageIndexLast;
					p.Data[4] = carUIPara.Page_Index_Last;
					xQueueSend(xQueue_canTx, &p, 10);				
		
					p.Data[3] = CAN_UIPareIndex;
					p.Data[4] = carUIPara.Para_Index;
					xQueueSend(xQueue_canTx, &p, 10);
		
					p.Data[3] = CAN_UIParaIfControl;
					p.Data[4] = carUIPara.Para_IfControl;
					xQueueSend(xQueue_canTx, &p, 10);
					break;
					default:
								flag = 0;	
								break;
	}
	
}						

void canSendCarUIReqCmd(void)
{
	CanTxMsg p;

	p.StdId = CAN_UIID;
	p.ExtId = 0x01;  /* �ú���ʹ��STD֡ID������ExtID�ò��� */
	p.RTR = CAN_RTR_DATA;
	p.IDE = CAN_ID_STD;	
	/* ��CAN���緢��8���ֽ����� */
	p.DLC = 8;          /* ÿ������֧��0-8���ֽڣ���������Ϊ����8���ֽ� */
	p.Data[0] = enIDEnvironment;   
	p.Data[1] = enCMD;
	p.Data[2] = CAN_CARUI;
	p.Data[3] = CAN_UIReq;
	xQueueSend(xQueue_canTx, &p, 10);
					
	
}				

