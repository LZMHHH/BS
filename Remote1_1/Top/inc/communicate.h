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
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __COMMUNICATE_H
#define	__COMMUNICATE_H


#include "includes.h" 

/* 小车电机控制模式 */
typedef enum{
	
	enPWM     = 0x01,
	enPID     = 0x02,
	enPWMSelf = 0x03,
	enPIDSelf = 0x04,
	enPWMGS   = 0x05,
	enPIDGS   = 0x06,
	
}car_motor_e;

/*UI同步*/
typedef struct
{
	u8       Sync;                  //是否开启同步模式0：不开启
	
	
	u8       Step_Index;            //步长索引
	u8       Page_Index;            //页面索引
	u8       Page_Index_Last;       //上次页面索引
	u8       Para_Index;            //参数索引
	u8       Para_IfControl;        //参数是否可控

}ui_t;

/*********************** 外发 ***********************/
/*通讯数据结构*/
typedef struct
{
	u8  name;
	u8  mode;
	int cycle;
}led_t;



/* LED种类的nameID 用于LED种类下data[2]*/
#define NAME_LEDA 0x01
#define NAME_LEDB 0x02
#define NAME_FMQ  0x11

/* KEY种类的nameID 用于KEY种类下data[2] */
#define NAME_KEYU 0x01 /* 单击 */
#define NAME_KEYD 0x02
#define NAME_KEYL 0x03
#define NAME_KEYR 0x04
#define NAME_KEYM 0x05



/* 广播 */
extern led_t carLEDA;
extern led_t carFMQ;
extern led_t envLEDA;
extern led_t envLEDB;
extern led_t envFMQ;

/*********************** 中间 ***********************/
/* 状态机表 */
typedef enum
{
   enLightMode_OFF,
	 enLightMode_GS,    //跟随模式
	 enLightMode_RC,    //日常模式
}  enLight_Mode;
/*通讯数据结构*/
typedef struct 
{
	float temperature;     //温度
	float huimidity;			 //湿度
	
	float temp_offset;     //偏差（用于调零）
	float huim_offset;     //偏差（用于调零）
	
	float tempAdd_shieldVal;   //加热阈值
	float tempRed_shieldVal;   //降温阈值
	float huim_shieldVal;      //阈值
	
	u16   AddPwm;             //加热风俗
	u16   RedPwm;             //加热风俗
	
	u8    tempAdd_mode;       //制热模式
	u8    tempRed_mode;       //制冷模式
	u8    huim_mode;          //模式
}huimiture_t;
typedef struct
{
	float BH_Voltage;        //正常数据
	
	float shieldVal;   //阈值
	
	float a;           //亮度系数
	
	u8    mode;        //enON：正向，enOFF：反向
}light_t;
typedef struct
{
	u16  PM2_5_Vol;   //pm2.5数值
	u16  PM10_Vol;    //pm10数值
	
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
	int    PriVal;      //原始的气体AD值
	int    ShieldVal;   //阈值
	
}gas_t;
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
/* 广播 */
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
/*********************** 接收 ***********************/
/*通讯数据结构*/
/*编码器*/
typedef struct
{
	int  motorA;
	int  motorB;
	int  motorC;
	int  motorD;
}encoder_t;
/*电机PWM*/
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

	u8      status;     //状态
}hwbz_t;
typedef struct{
	
	int xmm;
	
	int offset;
	
	int shieldVal;
}distance_t;
typedef struct{
	
	/* 值 */
	float p;
	float i;
	float d;
	
}pid_t;
/* 广播 */
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
