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
/*********************** �ⷢ ***********************/
/*ͨѶ���ݽṹ*/

/* �㲥 */

/*********************** ���� ***********************/
/*ͨѶ���ݽṹ*/

/* �㲥 */

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
typedef struct _ui_t      ui_t;
/* �㲥 */
extern connect_t   canConnect;
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

void canCommunicateParaInit(void);


#endif /* __USART_H */
