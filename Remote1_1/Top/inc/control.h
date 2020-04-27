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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __CONTROL_H
#define __CONTROL_H

#include "includes.h"

typedef struct class_carmoveval CLASS_CarMoveVal;

/* С���ƶ�ֵ */
struct class_carmoveval
{	
	int    MoveX;     //С���ƶ�X��
	int    MoveY;     //С���ƶ�Y��
	int    MoveZ;     //С���ƶ�Z��	
};

/*����С��ģʽ*/
typedef enum 
{
	enNoCon,   /* ������ */
	enJoystick,/* ҡ�˿��� */
	enMpuAcc,  /* ���ٶȿ��� */
	enMpuAng,  /* �Ƕȿ��� */
}ConMode_e;


/* �㲥 */
extern ConMode_e        ConCarMode;
extern CLASS_CarMoveVal CarMoveVal;



long map(long x, long in_min, long in_max, long out_min, long out_max);
int myabs(int a);

void ParaInit(void);

#endif
