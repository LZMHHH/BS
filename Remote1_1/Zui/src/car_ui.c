/**
  ******************************************************************************
  * @file    car_ui.c
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

#include "car_ui.h"


CLASS_UIconfigParam Car_uiconfigParam;


void Car_uiconfigParamInit(void)
{
	Car_uiconfigParam.Page_Index_Limit    = 5;
	
	Car_uiconfigParam.Para_Index_Limit[0] = 7;
	Car_uiconfigParam.Para_Index_Limit[1] = 7;
	Car_uiconfigParam.Para_Index_Limit[2] = 8;
	Car_uiconfigParam.Para_Index_Limit[3] = 4;
	
	Car_uiconfigParam.Step_Index_Limit    = 6;
	
	Car_uiconfigParam.Step_Size[0]        =   0.001;
	Car_uiconfigParam.Step_Size[1]        =   0.01;
	Car_uiconfigParam.Step_Size[2]        =   0.1;
	Car_uiconfigParam.Step_Size[3]        =   1.0;
	Car_uiconfigParam.Step_Size[4]        =  10.0;
	Car_uiconfigParam.Step_Size[5]        = 100.0;
	
	Show_Para_Con(&Car_uiconfigParam);
	
	Car_uiconfigParam.Step_Index          = 1;
	Car_uiconfigParam.Page_Index          = 1;
	Car_uiconfigParam.Page_Index_Last     = 0;
	Car_uiconfigParam.Para_Index          = 0;
	Car_uiconfigParam.Para_IfControl      = false;
	
	Car_uiconfigParam.Sync                = false;
	
	
}


void Car_ZUI(void)
{
	u8 h;    //��ʾ��ϵ��
	u8 Ph;   //������ϵ��
	

	/* �ź� */
	if(uart3Connect.status == enBreak)
	{
		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
	}
	else
	{
		OLED_DrawBMP(2,56,UI_ASIGNAL8X8,8,8);
	}
	
	/* ͬ�� */
	if(carUIPara.Sync)
	{
		OLED_ShowString(20,56,(u8 *)"T",1);
	}
	else
	{
		OLED_ShowString(20,56,(u8 *)"X",1);
	}
	
	
	/* ҳ�� */
	OLED_ShowChar(109,56,'c',1);
	OLED_ShowChar(115,56,'P',1);
  OLED_ShowNum(121,56,Car_uiconfigParam.Page_Index,1,0,1);

	
	//�� 1 ҳ
	if(Car_uiconfigParam.Page_Index == 1)
	{  
		h = 1;
		//1��
	  Ph = 1;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MApwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutA,6,0,1);
			h++;
	  }
		
		//2��
	  Ph = 2;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MAenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorA,6,0,1);
			h++;
	  }
		
		//3��
	  Ph = 3;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutB,6,0,1);
			h++;
	  }
		
		//4��
	  Ph = 4;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MBenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorB,6,0,1);
			h++;
	  }
		
		//5��
	  Ph = 5;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutC,6,0,1);
			h++;
	  }
		
		//6��
	  Ph = 6;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MCenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorC,6,0,1);
			h++;
	  }
		
		//7��
	  Ph = 7;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDpwm :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Motorpwm.pwmoutD,6,0,1);
			h++;
	  }
		
		//8��
	  Ph = 8;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"MDenc :",1);
			}		
			OLED_ShowNum(92,(7-h)*8,Encoder.motorD,6,0,1);
			h++;
	  }
		
	}
	
	//�� 3 ҳ
	if(Car_uiconfigParam.Page_Index == 3)
	{  
		
		OLED_ShowNum(49,56,Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index],3,3,1);
		
		h = 1;
		//1��
	  Ph = 1;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAs:",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAs:",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(carLEDA.mode)
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
					switch(carLEDA.mode)
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
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAc:",1); //LedA����˸����
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cLedAc:",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,carLEDA.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,carLEDA.cycle,5,0,1);
			}
			h++;
	  }
		
		//3��
	  Ph = 3;
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqs :",1);
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqs :",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					switch(carFMQ.mode)
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
					switch(carFMQ.mode)
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
	  if(Car_uiconfigParam.Para_Index_Show[Ph] != 0 && h < 8)
	  {
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == false)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqc :",1); //LedA����˸����
					Oled_Colour = 0;
			}
			else
			{
					OLED_ShowString(0,(7-h)*8,(u8 *)"cFmqc :",1);
			}	
			if(Car_uiconfigParam.Para_Index == Ph && Car_uiconfigParam.Para_IfControl == true)
			{
					Oled_Colour = 1;     //fanzhuan
					OLED_ShowNum(98,(7-h)*8,carFMQ.cycle,5,0,1);
					Oled_Colour = 0;				
			}
			else
			{
					OLED_ShowNum(98,(7-h)*8,carFMQ.cycle,5,0,1);
			}
			h++;
	  }
	}
	
}


/************************************ ��Ӧ�İ������� **********************************/


//Ԥ������,��ֹ���߿��Ƹ��²���   �ڲ���һ�������л�ҳ��ʱ����׼����ʾ���ݣ�
static void Para_Prepare(void)
{
  if(Car_uiconfigParam.Page_Index_Last != Car_uiconfigParam.Page_Index)
  {
    Car_uiconfigParam.Page_Index_Last = Car_uiconfigParam.Page_Index;
    OLED_Clear();
  }
  
  if(Car_uiconfigParam.Page_Index==4)
  {
		
  }

}

void Car_uictrl(void)
{
	//�м�������
	if(Key_PM.Key_RetVal == enKey_Click)
	{
    if(Car_uiconfigParam.Para_IfControl==false && ((Car_uiconfigParam.Page_Index == 1)   
																							   || (Car_uiconfigParam.Page_Index == 2)  
																								 || (Car_uiconfigParam.Page_Index == 3)  
																								 || (Car_uiconfigParam.Page_Index == 4))) 
			 Car_uiconfigParam.Para_IfControl=true;    //�ɿ�ҳ
    else                                                                  
			 Car_uiconfigParam.Para_IfControl=false;

		
		/* ͬ�� */
		if(carUIPara.Sync == true)
		{
			sendCmd(DOWN_REMOTOR,KIND_KEY,NAME_KEYM,10);
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
		if(Car_uiconfigParam.Para_IfControl)  
    {
      if(Car_uiconfigParam.Step_Index >= Car_uiconfigParam.Step_Index_Limit)
           Car_uiconfigParam.Step_Index = 0
			;
      else Car_uiconfigParam.Step_Index++;
    }
    else
    {
      if(Car_uiconfigParam.Page_Index<=0) 
        Car_uiconfigParam.Page_Index=Car_uiconfigParam.Page_Index_Limit; 
      else 
        Car_uiconfigParam.Page_Index--;		
			Car_uiconfigParam.Para_Index=1;         //����������λ
			Show_Para_Con(&Car_uiconfigParam);
			Para_Prepare();
      OLED_Clear();
			
			
    }
		/* ͬ�� */
		if(carUIPara.Sync == true)
		{
			sendCmd(DOWN_REMOTOR,KIND_KEY,NAME_KEYL,10);
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
		if(Car_uiconfigParam.Para_IfControl)  
    {
      if(Car_uiconfigParam.Step_Index <= 0)
           Car_uiconfigParam.Step_Index = Car_uiconfigParam.Step_Index_Limit;
      else Car_uiconfigParam.Step_Index--;
    }
    else
    {
      if(Car_uiconfigParam.Page_Index>=Car_uiconfigParam.Page_Index_Limit) 
        Car_uiconfigParam.Page_Index=0; 
      else 
        Car_uiconfigParam.Page_Index++;		
			Car_uiconfigParam.Para_Index=1;         //������λ
			Show_Para_Con(&Car_uiconfigParam);
			Para_Prepare();			
      OLED_Clear();
    }
		
		/* ͬ�� */
		if(carUIPara.Sync == true)
		{
			sendCmd(DOWN_REMOTOR,KIND_KEY,NAME_KEYR,10);
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
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
      if(Car_uiconfigParam.Para_Index<=1) Car_uiconfigParam.Para_Index = Car_uiconfigParam.Para_Index_Limit[Car_uiconfigParam.Page_Index];
      else              Car_uiconfigParam.Para_Index--;		
			Show_Para_Con(&Car_uiconfigParam);
    }
    else
    { 
			
			if(Car_uiconfigParam.Page_Index==3)     //�޸ĵ�3����
      {
				//������
				switch(Car_uiconfigParam.Para_Index)
				{
					case 1:
							switch(carLEDA.mode)
							{
								case enON:
											carLEDA.mode = enOFF;
											break;
								case enOFF:
											carLEDA.mode = enFre;
											break;
								case enFre:
											carLEDA.mode = enON;
											break;
								default:
											carLEDA.mode = enON;
											break;
							}
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carLEDA,sizeof(carLEDA),10);						
							break;
					case 2:
							carLEDA.cycle += Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index];
							if(carLEDA.cycle > 10000) carLEDA.cycle = 10000;
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carLEDA,sizeof(carLEDA),10);
							break;
					case 3:
							switch(carFMQ.mode)
							{
								case enON:
											carFMQ.mode = enOFF;
											break;
								case enOFF:
											carFMQ.mode = enFre;
											break;
								case enFre:
											carFMQ.mode = enON;
											break;
								default:
											carFMQ.mode = enON;
											break;
							}
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carFMQ,sizeof(carFMQ),10);
							break;
					case 4:
							carFMQ.cycle += Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index];
							if(carFMQ.cycle > 10000) carFMQ.cycle = 10000;
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carFMQ,sizeof(carFMQ),10);
							break;
					default:break;
				}
			}
			
			
		}
		
		/* ͬ�� */
		if(carUIPara.Sync == true)
		{
			sendCmd(DOWN_REMOTOR,KIND_KEY,NAME_KEYU,10);
		}

		Key_PU.Key_RetVal = enKey_No;   //��־��λ
	}
	
	//�ϼ���������
	if(Key_PU.Key_RetVal == enKey_LongPress)
	{

		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
		
			if(Car_uiconfigParam.Page_Index==2)     //�޸ĵ�2ҳ����
      {
				
			}
		}
		
	}
	
	//�¼�������
	if(Key_PD.Key_RetVal == enKey_Click)
	{
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			if(Car_uiconfigParam.Para_Index>=Car_uiconfigParam.Para_Index_Limit[Car_uiconfigParam.Page_Index]) Car_uiconfigParam.Para_Index = 1;
      else              Car_uiconfigParam.Para_Index++;
			Show_Para_Con(&Car_uiconfigParam);
    }
    else
    { 
			if(Car_uiconfigParam.Page_Index==3)     //�޸ĵ�3ҳ����
      {
				//������
				switch(Car_uiconfigParam.Para_Index)
				{
					case 1:
							switch(carLEDA.mode)
							{
								case enON:
											carLEDA.mode = enFre;
											break;
								case enFre:
											carLEDA.mode = enOFF;
											break;
								case enOFF:
											carLEDA.mode = enON;
											break;
								default:
											carLEDA.mode = enON;
											break;
							}
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carLEDA,sizeof(carLEDA),10);
							break;
					case 2:
							carLEDA.cycle -= Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index];
							if(carLEDA.cycle <  -1) carLEDA.cycle =  -1;
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carLEDA,sizeof(carLEDA),10);
							break;
					case 3:
							switch(carFMQ.mode)
							{
								case enON:
											carFMQ.mode = enFre;
											break;
								case enFre:
											carFMQ.mode = enOFF;
											break;
								case enOFF:
											carFMQ.mode = enON;
											break;
								default:
											carFMQ.mode = enON;
											break;
							}
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carFMQ,sizeof(carFMQ),10);
							break;
					case 4:
							carFMQ.cycle -= Car_uiconfigParam.Step_Size[Car_uiconfigParam.Step_Index];
							if(carFMQ.cycle <  -1) carFMQ.cycle =  -1;
							/* ͬ�� */
							if(carUIPara.Sync == false)
								sendRmotorData(enIDRemote,KIND_LED,(u8*)&carFMQ,sizeof(carFMQ),10);
							break;
					default:break;
				}
			}		
			
		}
		/* ͬ�� */
		if(carUIPara.Sync == true)
		{
			sendCmd(DOWN_REMOTOR,KIND_KEY,NAME_KEYD,10);
		}

		Key_PD.Key_RetVal = enKey_No;   //��־��λ
	}
	//�¼���������
	if(Key_PD.Key_RetVal == enKey_LongPress)
	{
		if(Car_uiconfigParam.Para_IfControl == false) 
    {
			;
    }
    else
    { 
			;
		}
	}	
}

