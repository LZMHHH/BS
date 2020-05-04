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
	/* car */
	DOWN_COMMAND	= 0x01,
	DOWN_ACK		  = 0x02,
	DOWN_REMOTOR	= 0x50,
	
}downmsgID_e;


/* kind:种类用于遥控中data[1] */
typedef enum 
{
	KIND_MOVE   	= 0x01,
	KIND_LED		  = 0x02,
	KIND_MOTOR	  = 0x03,
	KIND_ENCODER	= 0x04,
	KIND_KEY     	= 0x05,
	KIND_UI     	= 0x11,
	KIND_UIREQ    = 0x12,
	KIND_SHT3X    = 0x21,
	KIND_GY30     = 0x22,
	KIND_PMS      = 0x23,
	KIND_BME      = 0x24,
	
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
