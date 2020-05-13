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
/* ״̬���� */
typedef enum
{
   enLightMode_OFF,
	 enLightMode_GS,    //����ģʽ
	 enLightMode_RC,    //�ճ�ģʽ
}  enLight_Mode;
/*ͨѶ���ݽṹ*/
typedef struct 
{
	float temperature;     //�¶�
	float huimidity;			 //ʪ��
	
	float temp_offset;     //ƫ����ڵ��㣩
	float huim_offset;     //ƫ����ڵ��㣩
	
	float tempAdd_shieldVal;   //������ֵ
	float tempRed_shieldVal;   //������ֵ
	float huim_shieldVal;      //��ֵ
	
	u16   AddPwm;             //���ȷ���
	u16   RedPwm;             //���ȷ���
	
	u8    tempAdd_mode;       //����ģʽ
	u8    tempRed_mode;       //����ģʽ
	u8    huim_mode;          //ģʽ
}huimiture_t;
typedef struct
{
	float BH_Voltage;        //��������
	
	float shieldVal;   //��ֵ
	
	float a;           //����ϵ��
	
	u8    mode;        //enON������enOFF������
}light_t;
typedef struct
{
	u16  PM2_5_Vol;   //pm2.5��ֵ
	u16  PM10_Vol;    //pm10��ֵ
	
	u16  shieldPM2_5Val;
	u16  shieldPM10Val;
	
	u8   AQI;
	
	u8   mode;
}pms_t;
typedef struct
{
	float   temperature;
	float   pressure; 
	float   humidity;
	float   asl;
}bme_t;
typedef struct 
{	
	int    PriVal;      //ԭʼ������ADֵ
	int    ShieldVal;   //��ֵ
	
}gas_t;
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
extern gas_t       Smog;
extern gas_t       Hydrogen;
extern gas_t       CO;
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
/* �㲥 */
extern encoder_t   Encoder;
extern motor_t     Motorpwm;
extern car_t       Car;
extern hwbz_t    Hwbz_LD;
extern hwbz_t    Hwbz_LU;
extern hwbz_t    Hwbz_RU;
extern hwbz_t    Hwbz_RD;
extern distance_t Distance;
extern pid_t     MotorAllPID;

void CommunicateParaInit(void);


#endif /* __USART_H */
