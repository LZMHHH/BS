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
	
	enPWM     = 0x01,
	enPID     = 0x02,
	enPWMSelf = 0x03,
	enPIDSelf = 0x04,
	enPWMGS   = 0x05,
	enPIDGS   = 0x06,
	
}car_motor_e;
/* С��ʵ��״̬���� */
typedef enum{
	
	enSTOP = 0x00,
	enMOVE = 0x01,
	
}car_move_e;


typedef struct{
	/* �����ٶ�ֵ */
	int speedX;
	int speedY;
	int speedZ;	
	
	u16 MaxPwm;
	
	u8  mode;
	
	u8  flag;
	
}car_t;


/* �㲥 */
typedef struct class_motor CLASS_Motor;
typedef struct class_pid   CLASS_Pid;

extern   CLASS_Motor MotorA;
extern   CLASS_Motor MotorB;
extern   CLASS_Motor MotorC;
extern   CLASS_Motor MotorD;
extern   car_t       Car;
extern   CLASS_Pid   MotorAllPID;


extern   volatile TickType_t CarTickCount; 


void vTaskMoveCtrl( void * pvParameters );
void canSendMotorData(void);
void canSendEncoderData(void);
void canSendCarData(void);
void canSendMotorPidData(void);
void canSendHwbzData(void);
void uart1SendMotorData(void);
void uart1SendEncoderData(void);
void uart1SendCarData(void);
void uart1SendMotorPidData(void);
void uart1SendHwbzData(void);
#endif







