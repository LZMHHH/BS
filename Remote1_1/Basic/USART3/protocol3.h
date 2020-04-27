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

/* mcuID号 */
typedef enum
{
  enIDRemote = 0x00,      // mcuID号
	enIDCAR    = 0x01,      // mcuID号
	enIDEnvironment = 0x02, // mcuID号
}MCU_ID;

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
	u8 msgID;
	u8 mcuID;
	u8 dataLen;
	u8 data[MSG_MAX_DATA_SIZE];
}msg_t;


/* 协议ID */
/*上行指令ID*/
typedef enum 
{
	/* car */
	UP_VERSION	= 0x00,
	UP_STATUS		= 0x01,
	UP_SENSER		= 0x02,
	UP_RCDATA		= 0x03,
	UP_GPSDATA	= 0x04,
	UP_POWER		= 0x05,
	UP_MOTOR		= 0x06,
	UP_SENSER2	= 0x07,
	UP_FLYMODE	= 0x0A,
	UP_SPEED 		= 0x0B,
	UP_PID1			= 0x10,
	UP_PID2			= 0x11,
	UP_PID3			= 0x12,
	UP_PID4			= 0x13,
	UP_RADIO		= 0x20,
	UP_MSG			= 0x21,
	UP_CHECK		= 0x22,	
	UP_REMOTOR	= 0x30,
	UP_PRINTF		= 0x31,
	
	/* environment */
	
	

}upmsgID_e;

/*下行指令ID*/
typedef enum 
{
	/* car */
	DOWN_COMMAND	= 0x01,
	DOWN_ACK		  = 0x02,
	DOWN_RCDATA		= 0x03,
	DOWN_POWER		= 0x05,
	DOWN_FLYMODE	= 0x0A,
	DOWN_PID1		  = 0x10,
	DOWN_PID2		  = 0x11,
	DOWN_PID3		  = 0x12,
	DOWN_PID4		  = 0x13,
	DOWN_RADIO		= 0x40,
	DOWN_REMOTOR	= 0x50,
	
	
}downmsgID_e;

/*下行命令*/
/* car */
#define  CMD_CHANGE_MODE		0x01	/*切换模式*/




/* 把整形编码成字符串数据   5位数字 */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);


/* 通讯部分封装 */
void sendRmotorCmd(MCU_ID mcu_id,u8 cmd, u8 data,TickType_t xTicksToWait);
void sendRmotorData(MCU_ID mcu_id,u8 *data, u8 len,TickType_t xTicksToWait);

#endif /* __USART_H */
