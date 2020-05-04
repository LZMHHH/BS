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

/*UIͬ��*/
typedef struct
{
	u8       Sync;                  //�Ƿ���ͬ��ģʽ0��������
	
	
	u8       Step_Index;            //��������
	u8       Page_Index;            //ҳ������
	u8       Page_Index_Last;       //�ϴ�ҳ������
	u8       Para_Index;            //��������
	u8       Para_IfControl;        //�����Ƿ�ɿ�

}ui_t;

/*********************** �ⷢ ***********************/
/*ͨѶ���ݽṹ*/
typedef struct
{
	u8  name;
	u8  mode;
	int cycle;
}led_t;



/* LED�����nameID ����LED������data[2]*/
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

/*********************** �м� ***********************/
/*ͨѶ���ݽṹ*/
typedef struct 
{
	float temperature;     //�¶�
	float huimidity;			 //ʪ��
}huimiture_t;
typedef struct
{
	float BH_Voltage;        //��������
}light_t;
typedef struct
{
	u16  PM2_5_Vol;   //pm2.5��ֵ
	u16  PM10_Vol;    //pm10��ֵ
}pms_t;
typedef struct
{
	float   temperature;
	float   pressure; 
	float   humidity;
	float   asl;
}bme_t;
/* canled�Ľṹ��������һ��ͨ��ͷ�ļ� */
typedef struct
{
	int    Second;
	int    Minute;
	int    Hour;
	int    Week;     
	int    Day;      
	int    Month;   
	int    Year;    
	float  Temp;
	char   Switch;  //���ӿ���
	u16    num_save;//���ο�������Ĵ���
}clock_t;

/* ����ǽ */
typedef struct _connect_t connect_t;
/* �㲥 */
extern connect_t   uart3Connect;
extern huimiture_t Huimiture;
extern light_t     Light;
extern pms_t       Pms;
extern bme_t       Bme;
extern clock_t     ClockA;
extern clock_t     SetClock;
extern ui_t        envUIPara;
extern ui_t        carUIPara;

/*********************** ���� ***********************/
/*ͨѶ���ݽṹ*/
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
extern encoder_t   Encoder;
extern motor_t     Motorpwm;

void CommunicateParaInit(void);


#endif /* __USART_H */
