/**
  ******************************************************************************
  * @file    MpuTask.h
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __MPUTASK_H_
#define __MPUTASK_H_

#include "includes.h"

//MPU
#define PI 3.14159265   //系数

typedef struct 
{
	
	//MPU
	int   Temperature;                         //显示温度
//	float Angle_BalanceX;                          //平衡倾角X 
//	float Angle_BalanceY;                          //平衡倾角Y
//	float Angle_BalanceZ;                          //平衡倾角Z 
//	float Gyro_BalanceX;                            //陀螺仪X
//	float Gyro_BalanceY;                            //陀螺仪Y
	float Gyro_BalanceZ;                            //陀螺仪Z
	float Acceleration_X;                          //X轴加速度计
	float Acceleration_Y;                          //Y轴加速度计
	float Acceleration_Z;                          //Z轴加速度计
	float Mechanical_deviation;                    //机械偏差;
	
}CLASS_mpu_data;


extern CLASS_mpu_data mpu_data;


void vTaskMpu( void * pvParameters );

void Get_Angle(CLASS_mpu_data *mpudata,u8 way);
u8   Period_Control(void);


#endif
