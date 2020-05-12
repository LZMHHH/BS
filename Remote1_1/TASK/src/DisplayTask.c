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
volatile TickType_t SendUITickCountA; //���ڶ�ʱ�ϴ�����

static void Para_Init(void);
void uart3SendCARUIREQ(void);
void uart3SendENVUIREQ(void);

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
			if(envUIPara.Sync == true)
			{
				/* ����һ���¼� */
				xEventGroupSetBits(Event_uart3SendData,EVENT_uart3ENVUIREQ);	
			}
					
			SendUITickCount = xTaskGetTickCount();
		}
		if(SendUITickCount > xTaskGetTickCount())
		{
			SendUITickCount = xTaskGetTickCount();
		}
		
		
		if((xTaskGetTickCount()-100) > SendUITickCountA)
		{
			if(Show_ui == CAR_ui)
			{
				uart3SendCARUIREQ();
			}
			if(Show_ui == ENVI_ui)
			{
				uart3SendENVUIREQ();
			}
					
			SendUITickCountA = xTaskGetTickCount();
		}
		if(SendUITickCountA > xTaskGetTickCount())
		{
			SendUITickCountA = xTaskGetTickCount();
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
void uart3SendCarUIReqCmd(void)
{
	sendCmd(DOWN_REMOTOR,KIND_UIREQ,UIREQ_CAR,20);
}

/* ͨѶ */
void uart3SendEnvUIReqCmd(void)
{
	sendCmd(DOWN_REMOTOR,KIND_UIREQ,UIREQ_ENVIRONMENT,20);
}

void uart3SendCARUIREQ(void)
{
	sendCmd(DOWN_REQ,KIND_UIPAGEREQ,UIREQ_CAR,20);
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REQ;
	p.mcuID = enIDRemote;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = KIND_UIPAGEREQ;
	switch(Car_uiconfigParam.Page_Index)
	{
		case 0:
					p.data[2] = KIND_CARUIPAGE0;
					break;
		case 1:
					p.data[2] = KIND_CARUIPAGE1;
					break;
		case 2:
					p.data[2] = KIND_CARUIPAGE2;
					break;
		case 3:
					p.data[2] = KIND_CARUIPAGE3;
					break;
	}
	
	xQueueSend(xQueue_uart3Tx, &p, 20);
}

void uart3SendENVUIREQ(void)
{
	msg_t p;
	p.msg_head = MSG_HEAD;
	p.msgID = DOWN_REQ;
	p.mcuID = enIDRemote;
	p.dataLen = 3;
	p.data[0] = enCMD;
	p.data[1] = KIND_UIPAGEREQ;
	switch(Envi_uiconfigParam.Page_Index)
	{
		case 0:
					p.data[2] = KIND_ENVUIPAGE0;
					break;
		case 1:
					p.data[2] = KIND_ENVUIPAGE1;
					break;
		case 2:
					p.data[2] = KIND_ENVUIPAGE2;
					break;
		case 3:
					p.data[2] = KIND_ENVUIPAGE3;
					break;
		case 4:
					p.data[2] = KIND_ENVUIPAGE4;
					break;
		case 5:
					p.data[2] = KIND_ENVUIPAGE5;
					break;
	}
	
	xQueueSend(xQueue_uart3Tx, &p, 20);
}
