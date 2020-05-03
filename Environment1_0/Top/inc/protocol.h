/**
  ******************************************************************************
  * @file    protocol.h
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
#ifndef __PROTOCOL_H
#define	__PROTOCOL_H


#include "includes.h" 

/*上报状态枚举*/
typedef enum
{
  enReTno = 0,  //       数据传送空闲  (也可以说处理完毕的回归)
	enReTing,     //       数据编码完毕,进入发送状态
	enReTed,      //       发送函数已经执行
}State_ReData;


/* 通讯连接状态 */
typedef enum
{
  enBreak  = 0x00,  //断开
	enSig1   = 0x01,  //一格
	enSig2   = 0x02,  //二格
	enSig3   = 0x03,  //三格
}connect_e;
typedef struct _connect_t
{
	volatile  TickType_t tickCount;
	connect_e status;
}connect_t;


#define MSG_MAX_DATA_SIZE 30
/*通讯数据结构*/
typedef struct
{
	u8 msg_head;   /* 信息头 本次采用 "$" 即为0x24 */
	u8 msgID;
	u8 mcuID;
	u8 dataLen;
	u8 data[MSG_MAX_DATA_SIZE];
}msg_t;



/* 协议ID */
#define MSG_HEAD '$'
/* 上下行ID为msg_id */
/*上行指令ID*/
typedef enum 
{
	UP_VERSION	= 0x00,
	UP_STATUS		= 0x01,
	UP_ACK      = 0x02,
  UP_DATA     = 0x03,

}upmsgID_e;
/*下行指令ID*/
typedef enum 
{
	DOWN_COMMAND	= 0x01,
	DOWN_ACK		  = 0x02,
	DOWN_REMOTOR	= 0x50,
	
}downmsgID_e;
/* mcuID号 */
typedef enum
{
	enIDBroadcast = 0x00,   // 广播ID号
  enIDRemote    = 0x01,      // mcuID号
	enIDCar       = 0x02,      // mcuID号
	enIDEnvironment = 0x03, // mcuID号
}MCU_ID;
/*遥控数据类别：用于遥控中data[0]*/
typedef enum 
{
	enCMD,
	enDATA,
}remoterType_e;


/* kind:种类用于遥控中data[1] */
typedef enum 
{
	KIND_MOVE   	= 0x01,
	KIND_LED		  = 0x02,
	KIND_MOTOR	  = 0x03,
	KIND_ENCODER	= 0x04,
	KIND_UI     	= 0x05,
	KIND_KEY     	= 0x06,
	
	CMD_CHANGE_MODE	=	0x21,	/*切换模式*/
	
}kind_e;

/********************************************************** 
	can通讯
**********************************************************/
/* can帧ID */
/* data[0] 为MCUID，同上 */
/* data[1] 为CMD或DATA，同上 */
/* data[2] 为一分 */
/* data[3] 为二分 */
/* data[4-7] 数据 */

/* can帧ID */
#define 	CAN_EVNID    0x031
#define 	CAN_LEDID    0x032
#define 	CAN_TIMEID   0x033

/* data[2] 为一分 */
/* 器件kind */
#define 	CAN_SHTX     0x01
#define 	CAN_GY30     0x02
#define 	CAN_PMS      0x03
#define 	CAN_BME      0x04
#define   CAN_LEDA     0x11
#define   CAN_LEDB     0x12
#define   CAN_FMQ      0x13
#define   CAN_DS3231   0x21
#define   CAN_SETCLOCK 0x22

/* data[3] 为二分 */
/* 环境参数kind */
#define 	CAN_Temperature  0x01
#define 	CAN_Humidity     0x02
#define 	CAN_Light        0x03
#define 	CAN_PM2_5        0x04
#define 	CAN_PM10         0x05
#define 	CAN_Pressure     0x06
#define 	CAN_Hight        0x07
#define 	CAN_LedMode      0x11
#define 	CAN_LedFre       0x12
#define 	CAN_Second       0x21
#define 	CAN_Minute       0x22
#define 	CAN_Hour         0x23
#define 	CAN_Day          0x24
#define 	CAN_Week         0x25
#define 	CAN_Month        0x26
#define 	CAN_Year         0x27
#define 	CAN_ClockMode    0x28
#define 	CAN_SaveNum      0x29

/* 把整形编码成字符串数据   5位数字 */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);

/* 通讯部分封装 */

void msgAnalyze(msg_t *p);
void canmsgAnalyze(CanRxMsg *p);
#endif /* __USART_H */
