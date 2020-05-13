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
	DOWN_REQ      = 0x03,
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
#define 	CAN_KEYID    0x033
#define 	CAN_TIMEID   0x034
#define 	CAN_UIID     0x035
#define 	CAN_MOTORID  0x036
#define 	CAN_CARDATAID 0x037
#define 	CAN_BZID     0x038

/* data[2] 为一分 */
/* 器件kind */
#define 	CAN_EMPTY    0x00   /* 保留 */
#define 	CAN_SHTX     0x11
#define 	CAN_GY30     0x12
#define 	CAN_PMS      0x13
#define 	CAN_BME      0x14
#define 	CAN_MQ2      0x15
#define 	CAN_MQ8      0x16
#define 	CAN_MQ7      0x17
#define   CAN_LEDA     0x21
#define   CAN_LEDB     0x22
#define   CAN_FMQ      0x23
#define   CAN_KEYU     0x31
#define   CAN_KEYD     0x32
#define   CAN_KEYL     0x33
#define   CAN_KEYR     0x34
#define   CAN_KEYM     0x35
#define   CAN_DS3231   0x41
#define   CAN_SETCLOCK 0x42
#define   CAN_CARUI    0x51
#define   CAN_ENVUI    0x52
#define   CAN_CARMOTOR     0x60
#define   CAN_CARMOTORA    0x61
#define   CAN_CARMOTORB    0x62
#define   CAN_CARMOTORC    0x63
#define   CAN_CARMOTORD    0x64
#define   CAN_HWBZ         0x81
#define   CAN_VL53L0X      0x82

/* data[3] 为二分 */
/* 环境参数kind */
#define 	CAN_Empty        0x00   /* 保留 */
#define 	CAN_Val          0x0a  
#define 	CAN_MaxVal       0x0b   
#define 	CAN_Temperature  0x11
#define 	CAN_Humidity     0x12
#define 	CAN_Light        0x13
#define 	CAN_PM2_5        0x14
#define 	CAN_PM10         0x15
#define 	CAN_AQI          0x16
#define 	CAN_Pressure     0x17
#define 	CAN_Hight        0x18
#define 	CAN_PriAD        0x19
#define 	CAN_LedMode      0x21
#define 	CAN_LedFre       0x22
#define 	CAN_KeyRet       0x31
#define 	CAN_Second       0x41
#define 	CAN_Minute       0x42
#define 	CAN_Hour         0x43
#define 	CAN_Day          0x44
#define 	CAN_Week         0x45
#define 	CAN_Month        0x46
#define 	CAN_Year         0x47
#define 	CAN_ClockMode    0x48
#define 	CAN_SaveNum      0x49
#define 	CAN_UIReq        0x50
#define 	CAN_UIStepIndex  0x51
#define 	CAN_UIPageIndex  0x52
#define 	CAN_UIPageIndexLast  0x53
#define 	CAN_UIPareIndex  0x54
#define 	CAN_UIParaIfControl  0x55
#define 	CAN_UIPageReq    0x5a
#define 	CAN_PwmOut       0x61
#define 	CAN_Encoder      0x65
#define 	CAN_P            0x6a
#define 	CAN_I            0x6b
#define 	CAN_D            0x6c
#define 	CAN_Shield       0x70
#define 	CAN_TempAddShield 0x71
#define 	CAN_TempRedShield 0x72
#define 	CAN_HuimShield  0x73
#define 	CAN_PM2_5Shield 0x74
#define 	CAN_PM10Shield  0x75
#define 	CAN_MODE        0x80
#define 	CAN_TempAddMode 0x81
#define 	CAN_TempRedMode 0x82
#define 	CAN_HuimMode    0x83
#define 	CAN_FactorA     0x91
#define 	CAN_Offset      0x9a
#define 	CAN_TempOffset  0x9b
#define 	CAN_HuimOffset  0x9c
#define 	CAN_TempAddPwm  0xa1
#define 	CAN_TempRedPwm  0xa2



/* 把整形编码成字符串数据   5位数字 */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);

/* 通讯部分封装 */
/* 通用 */
void sendCmd(upmsgID_e msg_id,MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait);
void sendData(upmsgID_e msg_id,MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);

void sendRmotorCmd(MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait);
void sendRmotorData(MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);

void msgAnalyze(msg_t *p);
void canmsgAnalyze(CanRxMsg *p);
#endif /* __USART_H */
