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

/*���ݳ�ʼ��*/
void ParaInit(void)
{
	/* С������ģʽ */
	ConCarMode = enJoystick;
	
	
	Main_uiconfigParamInit();
	
}