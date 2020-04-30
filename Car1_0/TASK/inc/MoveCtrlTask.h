/**
  ******************************************************************************
  * @file    MoveCtrlTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   �ƶ���������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __MOVECTRLTASK_H
#define __MOVECTRLTASK_H	 
#include "includes.h"


/* С������ */
#define CAR_PARAMETER_X   0.1115   //����x��/2
#define CAR_PARAMETER_Y   0.8   //����y��/2

/* С���������ģʽ */
typedef enum{
	
	CAR_MOTOR_PWM = 0x00,
	CAR_MOTOR_PID = 0x01,
	
}car_motor_e;

typedef struct{
	/* �����ٶ�ֵ */
	float speedX;
	float speedY;
	float speedZ;	
}car_t;


/* �㲥 */
typedef struct class_motor CLASS_Motor;

extern   CLASS_Motor MotorA;
extern   CLASS_Motor MotorB;
extern   CLASS_Motor MotorC;
extern   CLASS_Motor MotorD;
extern   car_t       Car;
extern   car_motor_e Car_Motor;

extern   volatile TickType_t CarTickCount; 


void vTaskMoveCtrl( void * pvParameters );


#endif







