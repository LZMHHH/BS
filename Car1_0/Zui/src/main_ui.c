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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
									OLED_ShowString(108,(7-h)*8,(u8 *)" ON",1);
									break;
						case enOFF:
									OLED_ShowString(108,(7-h)*8,(u8 *)"OFF",1);
									break;
						case enFre:
									OLED_ShowString(108,(7-h)*8,(u8 *)"Cyc",1);
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
	
	//��  ҳ
	if(Main_uiconfigParam.Page_Index == 4)
	{  
		OLED_ShowNum(0,0,mpu_data.Acceleration_X,4,2,1);
		OLED_ShowNum(0,8,mpu_data.Acceleration_Y,4,2,1);
		OLED_ShowNum(0,16,mpu_data.Acceleration_Z,4,2,1);		
		OLED_ShowNum(60,16,mpu_data.Gyro_BalanceZ,4,2,1);
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
		else
		{
			
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
