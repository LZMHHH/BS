/**
  ******************************************************************************
  * @file    MpuTask.h
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __MPUTASK_H_
#define __MPUTASK_H_

#include "includes.h"

//MPU
#define PI 3.14159265   //ϵ��

typedef struct 
{
	
	//MPU
	int   Temperature;                         //��ʾ�¶�
//	float Angle_BalanceX;                          //ƽ�����X 
//	float Angle_BalanceY;                          //ƽ�����Y
//	float Angle_BalanceZ;                          //ƽ�����Z 
//	float Gyro_BalanceX;                            //������X
//	float Gyro_BalanceY;                            //������Y
	float Gyro_BalanceZ;                            //������Z
	float Acceleration_X;                          //X����ٶȼ�
	float Acceleration_Y;                          //Y����ٶȼ�
	float Acceleration_Z;                          //Z����ٶȼ�
	float Mechanical_deviation;                    //��еƫ��;
	
}CLASS_mpu_data;


extern CLASS_mpu_data mpu_data;


void vTaskMpu( void * pvParameters );

void Get_Angle(CLASS_mpu_data *mpudata,u8 way);
u8   Period_Control(void);


#endif
