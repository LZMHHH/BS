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
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __CANCOMMUNICATE_H
#define	__CANCOMMUNICATE_H


#include "includes.h" 
/*********************** 外发 ***********************/
/*通讯数据结构*/

/* 广播 */

/*********************** 接收 ***********************/
/*通讯数据结构*/

/* 广播 */

/*********************** 中间 ***********************/
/*通讯数据结构*/
typedef struct 
{
	float temperature;     //温度
	float huimidity;			 //湿度
}huimiture_t;
typedef struct
{
	float BH_Voltage;        //正常数据
}light_t;
typedef struct
{
	u16  PM2_5_Vol;   //pm2.5数值
	u16  PM10_Vol;    //pm10数值
}pms_t;
typedef struct
{
	float   temperature;
	float   pressure; 
	float   humidity;
	float   asl;
}bme_t;
/* canled的结构体在另外一个通信头文件 */
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
	char   Switch;  //闹钟开关
	u16    num_save;//本次开机保存的次数
}clock_t;

/* 防爆墙 */
typedef struct _connect_t connect_t;
typedef struct _ui_t      ui_t;
/* 广播 */
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
