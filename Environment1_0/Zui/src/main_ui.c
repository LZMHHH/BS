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
	Main_uiconfigParam.Page_Index_Limit    = 5;
	
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
	
	Show_Para_Con(&Main_uiconfigParam);
	
	Main_uiconfigParam.Step_Index          = 1;
	Main_uiconfigParam.Page_Index          = 1;
	Main_uiconfigParam.Page_Index_Last     = 0;
	Main_uiconfigParam.Para_Index          = 0;
	Main_uiconfigParam.Para_IfControl      = false;
	
}



void Main_ZUI(void)
{
	u8 h;    //��ʾ��ϵ��
	u8 Ph;   //������ϵ��
	
	
	
	/* ҳ�� */
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Main_uiconfigParam.Page_Index,1,0,1);
	
	/* �ź� */
	OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
	
	
	//�� 0 ҳ
	if(Main_uiconfigParam.Page_Index == 0)
	{  
		
		
		/* ��ʾʱ�� */
		OLED_ShowNum(40,56,ClockA.Hour,2,0,1);
		OLED_ShowString(52,56,":",1);
		OLED_ShowNum(58,56,ClockA.Minute,2,0,1);
		OLED_ShowString(70,56,":",1);
		OLED_ShowNum(76,56,ClockA.Second,2,0,1);
	
	}
	
	//�� 1 ҳ
	if(Main_uiconfigParam.Page_Index == 1)
	{  

		h = 1;
		//1��
	  Ph = 1;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"Temp :",1);
			OLED_ShowString(54,(7-h)*8,"`C",1);
			OLED_ShowNum(86,(7-h)*8,Huimiture.temperature,5,1,1);
			h++;
	  }
		
		//2��
	  Ph = 2;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"Huim :",1);
			OLED_ShowString(54,(7-h)*8,"%RH",1);
			OLED_ShowNum(86,(7-h)*8,Huimiture.huimidity,5,1,1);
			h++;
	  }
	
		//3��
	  Ph = 3;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"Light:",1);
			OLED_ShowString(54,(7-h)*8,"lx",1);
			OLED_ShowNum(86,(7-h)*8,Light.BH_Voltage,5,1,1);
			h++;
	  }
		
		//4��
	  Ph = 4;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"PM2.5:",1);
			OLED_ShowString(54,(7-h)*8,"ug/m3",1);
			OLED_ShowNum(86,(7-h)*8,Pms.PM2_5_Vol,5,1,1);
			h++;
	  }
		
		//5��
	  Ph = 5;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"PM10 :",1);
			OLED_ShowString(54,(7-h)*8,"ug/m3",1);
			OLED_ShowNum(86,(7-h)*8,Pms.PM10_Vol,5,1,1);
			h++;
	  }
		
		//6��
	  Ph = 6;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"BME_P:",1);
			OLED_ShowString(54,(7-h)*8,"hPa",1);
			OLED_ShowNum(86,(7-h)*8,Bme.pressure,5,1,1);
			h++;
	  }
		
		//7��
	  Ph = 7;
	  if(Main_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			OLED_ShowString(0,(7-h)*8,"BME_T:",1);
			OLED_ShowString(54,(7-h)*8,"`C",1);
			OLED_ShowNum(86,(7-h)*8,Bme.temperature,5,1,1);
			h++;
	  }
		
	}
	
	//�� 2 ҳ
	if(Main_uiconfigParam.Page_Index == 2)
	{  

		OLED_ShowNum(30,56,ClockA.Second,3,0,1);
		OLED_ShowNum(30,48,ClockA.Minute,3,0,1);
		OLED_ShowNum(30,40,ClockA.Hour,3,0,1);
		OLED_ShowNum(30,32,ClockA.Day,3,0,1);
		OLED_ShowNum(30,24,ClockA.Week,3,0,1);
		OLED_ShowNum(30,16,ClockA.Month,3,0,1);
		OLED_ShowNum(30,8,ClockA.Year,5,0,1);
		OLED_ShowNum(80,56,ClockA.Temp,3,1,1);
		
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
			Show_Para_Con(&Main_uiconfigParam);
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
			Show_Para_Con(&Main_uiconfigParam);
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
			Show_Para_Con(&Main_uiconfigParam);
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
			Show_Para_Con(&Main_uiconfigParam);
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
