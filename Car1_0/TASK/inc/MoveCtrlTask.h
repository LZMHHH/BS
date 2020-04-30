/**
  ******************************************************************************
  * @file    MoveCtrlTask.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   移动控制任务
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __MOVECTRLTASK_H
#define __MOVECTRLTASK_H	 
#include "includes.h"


/* 小车数据 */
#define CAR_PARAMETER_X   0.1115   //车轮x轴/2
#define CAR_PARAMETER_Y   0.8   //车轮y轴/2

/* 小车电机控制模式 */
typedef enum{
	
	CAR_MOTOR_PWM = 0x00,
	CAR_MOTOR_PID = 0x01,
	
}car_motor_e;

typedef struct{
	/* 三轴速度值 */
	float speedX;
	float speedY;
	float speedZ;	
}car_t;


/* 广播 */
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







