/**
  ******************************************************************************
  * @file    communicate.h
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
#ifndef __COMMUNICATE_H
#define	__COMMUNICATE_H


#include "includes.h" 

/*********************** �ⷢ ***********************/

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



/* �㲥 */
extern encoder_t Encoder;
extern motor_t   Motorpwm;

/*********************** ���� ***********************/
/*ͨѶ���ݽṹ*/
/*LED*/
typedef struct
{
	u8  name;
	u8  mode;
	int cycle;
}led_t;

/* LED�����nameID ����LED������data[2] */
#define NAME_LEDA 0x01
#define NAME_LEDB 0x02
#define NAME_FMQ  0x11

/* KEY�����nameID ����KEY������data[2] */
#define NAME_KEYU 0x01 /* ���� */
#define NAME_KEYD 0x02
#define NAME_KEYL 0x03
#define NAME_KEYR 0x04
#define NAME_KEYM 0x05

/* �㲥 */
extern led_t carLEDA;
extern led_t carFMQ;
extern led_t envLEDA;
extern led_t envLEDB;
extern led_t envFMQ;



void CommunicateParaInit(void);


#endif /* __USART_H */
