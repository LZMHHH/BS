/**
  ******************************************************************************
  * @file    control.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "control.h"	
#include "bsp_mcuFlash.h"
/* С������ģʽ */
ConMode_e        ConCarMode;
/* С���ƶ�ֵ */
CLASS_CarMoveVal CarMoveVal;

/* ��ѧ��ʽ */
//ת�Ʒ�Χ
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 /****************************************************************************
  * @brief    ����ֵ����
  * @param    a
  * @retval   |a|
  * @author   LZM
  * @note      
  */
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


void ConParaInit(void)
{
	/* С������ģʽ */
	ConCarMode = enJoystick;
}


/*���ݳ�ʼ��*/
void ParaInit(void)
{
	ConParaInit();
	
	CommunicateParaInit();

}




//��������
//���� ��ǰ����������    
void SaveFlashJoyData(void)
{

	taskENTER_CRITICAL();
	
	//��¼ǰ�����Ȳ���
	FlashErase(INSector,1);
	

	Flash_Write(INSector,(const uint8 *)&Joystick_Left.Mode,2,0);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.Grade,2,2);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.XZeroSet,4,4);
	Flash_Write(INSector,(const uint8 *)&Joystick_Left.YZeroSet,4,8);
  Flash_Write(INSector,(const uint8 *)&Joystick_Left.XShieldVal,4,12);
  Flash_Write(INSector,(const uint8 *)&Joystick_Left.YShieldVal,4,16);
	
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.Mode,2,20);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.Grade,2,22);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.XZeroSet,4,24);
	Flash_Write(INSector,(const uint8 *)&Joystick_Right.YZeroSet,4,28);
  Flash_Write(INSector,(const uint8 *)&Joystick_Right.XShieldVal,4,32);
  Flash_Write(INSector,(const uint8 *)&Joystick_Right.YShieldVal,4,36);
	
	taskEXIT_CRITICAL();
}

void ReadFlashJoyData(void)
{

	taskENTER_CRITICAL();
	
	Joystick_Left.Mode = Flash_Read(INSector,0,u8);
	Joystick_Left.Grade = Flash_Read(INSector,2,u8);
	Joystick_Left.XZeroSet = Flash_Read(INSector,4,int);
	Joystick_Left.YZeroSet = Flash_Read(INSector,8,int);
  Joystick_Left.XShieldVal = Flash_Read(INSector,12,int);
  Joystick_Left.YShieldVal = Flash_Read(INSector,16,int);

	Joystick_Right.Mode = Flash_Read(INSector,20,u8);
	Joystick_Right.Grade = Flash_Read(INSector,22,u8);
	Joystick_Right.XZeroSet = Flash_Read(INSector,24,int);
	Joystick_Right.YZeroSet = Flash_Read(INSector,28,int);
  Joystick_Right.XShieldVal = Flash_Read(INSector,32,int);
  Joystick_Right.YShieldVal = Flash_Read(INSector,36,int);
	
	taskEXIT_CRITICAL();
}


