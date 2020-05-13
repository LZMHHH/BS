/**
  ******************************************************************************
  * @file    protocol3.h
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
#ifndef __PROTOCOL3_H
#define	__PROTOCOL3_H


#include "includes.h" 

/*上报状态枚举*/
typedef enum
{
  enReTno = 0,  //       数据传送空闲  (也可以说处理完毕的回归)
	enReTing,     //       数据编码完毕,进入发送状态
	enReTed,      //       发送函数已经执行
}State_ReData;



/*遥控数据类别*/
typedef enum 
{
	enCMD,
	enDATA,
}remoterType_e;

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

/* mcuID号 */
typedef enum
{
	enIDBroadcast = 0x00,   // 广播ID号
  enIDRemote    = 0x01,      // mcuID号
	enIDCar       = 0x02,      // mcuID号
	enIDEnvironment = 0x03, // mcuID号
}MCU_ID;

/*上行指令ID*/
typedef enum 
{
	/* car */
	UP_VERSION	= 0x00,
	UP_STATUS		= 0x01,
	UP_ACK      = 0x02,
  UP_DATA     = 0x03,

	
	/* environment */
	
	

}upmsgID_e;

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

/*下行指令ID*/
typedef enum 
{
	DOWN_COMMAND	= 0x01,
	DOWN_ACK		  = 0x02,
	DOWN_REMOTOR	= 0x50,
	DOWN_REQ      = 0x03,
}downmsgID_e;


/* kind:种类用于遥控中data[1] */
typedef enum 
{
	KIND_MOVE   	= 0x01,
	KIND_LED		  = 0x02,
	KIND_MOTOR	  = 0x03,
	KIND_ENCODER	= 0x04,
	KIND_CARKEY   = 0x05,
	KIND_ENVKEY   = 0x06,
	KIND_CARDATA	= 0x07,
	KIND_MOTORPID	= 0x08,
	KIND_HWBZ    	= 0x09,
	KIND_Vl53l0XDATA = 0x0a,
	KIND_UI     	= 0x31,
	KIND_UIREQ    = 0x32,
	KIND_UIPAGEREQ = 0x33,
	KIND_SHT3X    = 0xa1,
	KIND_SHT3XCON = 0xa2,
	KIND_SHT3XMODE = 0xa3,
	KIND_GY30     = 0xa4,
	KIND_PMS      = 0xa5,
	KIND_BME      = 0xa6,
	KIND_SMOG     = 0xa7,
	KIND_HYDROGEN = 0xa8,
	KIND_CO       = 0xa9,
	KIND_DATE     = 0xb1,
	KIND_TIME     = 0xb2,
	KIND_SETDATE  = 0xb3,
	KIND_SETTIME  = 0xb4,
  KIND_CARUIPAGE0 = 0xc1,
	KIND_CARUIPAGE1 = 0xc2,
	KIND_CARUIPAGE2 = 0xc3,
	KIND_CARUIPAGE3 = 0xc4,
	KIND_ENVUIPAGE0 = 0xc5,
	KIND_ENVUIPAGE1 = 0xc6,
	KIND_ENVUIPAGE2 = 0xc7,
	KIND_ENVUIPAGE3 = 0xc8,
	KIND_ENVUIPAGE4 = 0xc9,
	KIND_ENVUIPAGE5 = 0xca,
	
	CMD_CHANGE_MODE	=	0x21,	/*切换模式*/
	
}kind_e;

/* KIND_UIREQ 用于CMD,下为请求哪一个MCU的UI*/
#define UIREQ_CAR          0x01
#define UIREQ_ENVIRONMENT  0x02

/* 把整形编码成字符串数据   5位数字 */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);


/* 通讯部分封装 */
/* 通用 */
void sendCmd(downmsgID_e msg_id,u8 cmd, u8 data,TickType_t xTicksToWait);
void sendData(downmsgID_e msg_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);

void sendRmotorCmd(MCU_ID mcu_id,u8 cmd, u8 data,TickType_t xTicksToWait);
void sendRmotorData(MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);


void msgAnalyze(msg_t *p);
#endif /* __USART_H */
