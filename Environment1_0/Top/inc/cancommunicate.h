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

/* ����ǽ */
typedef struct _connect_t connect_t;
/* �㲥 */
extern connect_t   canConnect;
extern ui_t        carUIPara;
extern led_t       carLEDA;
extern led_t       carFMQ;
extern encoder_t   Encoder;
extern motor_t     Motorpwm;

void canCommunicateParaInit(void);


#endif /* __USART_H */
