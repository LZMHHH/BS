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

/* ��ʾ���� */
CLASS_Joystick uiJoystick_Left;
CLASS_Joystick uiJoystick_Right;

/* ������Ҫ��ʾ������ */
void RxUidata(void)
{
	/*�ȶ��գ��ٷ���*/
	xQueueReceive( vQueue_JoystickLeft,        /* ��Ϣ���еľ�� */
                             (void *)&uiJoystick_Left,      /* ���͵���Ϣ���� */
                             0);                       /* ���ȴ� */
														 
														 
	/*�ȶ��գ��ٷ���*/
	xQueueReceive( vQueue_JoystickRight,       /* ��Ϣ���еľ�� */
                             (void *)&uiJoystick_Right,      /* ���͵���Ϣ���� */
                             0);                       /* ���ȴ� */
														 
}

void Main_ZUI(void)
{
	u8 h;    //��ʾ��ϵ��
	u8 Ph;   //������ϵ��
	
	
	/* ������ʾ���� */
	RxUidata();
	
	OLED_ShowChar(115,3,'P',1);
  OLED_ShowNum(121,3,Main_uiconfigParam.Page_Index,1,0,1);
	
	//�� 0 ҳ
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
	
	//�� 1 ҳ
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
      Main_uiconfigParam.Para_Index=1;         //������λ
			Show_Para_Con(Main_uiconfigParam);
			Para_Prepare();
      if(Main_uiconfigParam.Page_Index<=0) 
        Main_uiconfigParam.Page_Index=Main_uiconfigParam.Page_Index_Limit; 
      else 
        Main_uiconfigParam.Page_Index--;
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
      Main_uiconfigParam.Para_Index=1;         //������λ
			Show_Para_Con(Main_uiconfigParam);
			Para_Prepare();
      if(Main_uiconfigParam.Page_Index>=Main_uiconfigParam.Page_Index_Limit) 
        Main_uiconfigParam.Page_Index=0; 
      else 
        Main_uiconfigParam.Page_Index++;
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
			Show_Para_Con(Main_uiconfigParam);
    }
    else
    { 
			if(Main_uiconfigParam.Page_Index==1)     //�޸ĵ�1ҳ����
      {
				
			}
			
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				
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
			Show_Para_Con(Main_uiconfigParam);
    }
    else
    { 
			if(Main_uiconfigParam.Page_Index==1)     //�޸ĵ�1ҳ����
      {
				;
			}
			
			if(Main_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				;
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
