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


void canCommunicateParaInit(void);


#endif /* __USART_H */
