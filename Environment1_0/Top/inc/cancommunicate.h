/**
  ******************************************************************************
  * @file    cancommunicate.h
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
#ifndef __CANCOMMUNICATE_H
#define	__CANCOMMUNICATE_H


#include "includes.h" 

/* С���������ģʽ */
typedef enum{
	
	enPWM     = 0x01,
	enPID     = 0x02,
	enPWMSelf = 0x03,
	enPIDSelf = 0x04,
	enPWMGS   = 0x05,
	enPIDGS   = 0x06,
	
}car_motor_e;

/*UIͬ��*/
typedef struct _ui_t
{
	u8       Sync;                  //�Ƿ���ͬ��ģʽ0��������
	
	u8       Step_Index;            //��������
	u8       Page_Index;            //ҳ������
	u8       Page_Index_Last;       //�ϴ�ҳ������
	u8       Para_Index;            //��������
	u8       Para_IfControl;        //�����Ƿ�ɿ�

}ui_t;

typedef struct
{
	u8  name;
	u8  mode;
	int cycle;
}led_t;
/*������*/
typedef struct
{
	int  motorA;
	int  motorB;
	int  motorC;
	int  motorD;
}encoder_t;
/*���PWM*/
typedef struct
{
	int  pwmoutA;
	int  pwmoutB;
	int  pwmoutC;
	int  pwmoutD;
}motor_t;
typedef struct{

	u16 MaxPwm;
	
	u8  mode;
	
}car_t;
typedef struct{

	u8      status;     //״̬
}hwbz_t;
typedef struct{
	
	int xmm;
	
	int offset;
	
	int shieldVal;
}distance_t;
typedef struct{
	
	/* ֵ */
	float p;
	float i;
	float d;
	
}pid_t;

/* ����ǽ */
typedef struct _connect_t connect_t;
/* �㲥 */
extern connect_t   canConnect;
extern ui_t        carUIPara;
extern led_t       carLEDA;
extern led_t       carFMQ;
extern encoder_t   Encoder;
extern motor_t     Motorpwm;
extern car_t       Car;
extern hwbz_t    Hwbz_LD;
extern hwbz_t    Hwbz_LU;
extern hwbz_t    Hwbz_RU;
extern hwbz_t    Hwbz_RD;
extern distance_t Distance;
extern pid_t     MotorAllPID;

void canCommunicateParaInit(void);


#endif /* __USART_H */
