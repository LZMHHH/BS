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
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "control.h"	

/* 小车控制模式 */
ConMode_e        ConCarMode;
/* 小车移动值 */
CLASS_CarMoveVal CarMoveVal;

/* 数学公式 */
//转移范围
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 /****************************************************************************
  * @brief    绝对值函数
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

/*数据初始化*/
void ParaInit(void)
{
	/* 小车控制模式 */
	ConCarMode = enJoystick;
	
	
	Main_uiconfigParamInit();
	
}