/**
  ******************************************************************************
  * @file    control.h
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
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
#ifndef __CONTROL_H
#define __CONTROL_H

#include "includes.h"

typedef struct class_carmoveval CLASS_CarMoveVal;

/* 小车移动值 */
struct class_carmoveval
{	
	int    MoveX;     //小车移动X轴
	int    MoveY;     //小车移动Y轴
	int    MoveZ;     //小车移动Z轴	
};

/*控制小车模式*/
typedef enum 
{
	enNoCon,   /* 不控制 */
	enJoystick,/* 摇杆控制 */
	enMpuAcc,  /* 加速度控制 */
	enMpuAng,  /* 角度控制 */
}ConMode_e;


/* 广播 */
extern ConMode_e        ConCarMode;
extern CLASS_CarMoveVal CarMoveVal;



long map(long x, long in_min, long in_max, long out_min, long out_max);
int myabs(int a);

void ParaInit(void);

#endif
