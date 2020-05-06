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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __PROTOCOL_H
#define	__PROTOCOL_H


#include "includes.h" 

/*�ϱ�״̬ö��*/
typedef enum
{
  enReTno = 0,  //       ���ݴ��Ϳ���  (Ҳ����˵������ϵĻع�)
	enReTing,     //       ���ݱ������,���뷢��״̬
	enReTed,      //       ���ͺ����Ѿ�ִ��
}State_ReData;


/* ͨѶ����״̬ */
typedef enum
{
  enBreak  = 0x00,  //�Ͽ�
	enSig1   = 0x01,  //һ��
	enSig2   = 0x02,  //����
	enSig3   = 0x03,  //����
}connect_e;
typedef struct _connect_t
{
	volatile  TickType_t tickCount;
	connect_e status;
}connect_t;


#define MSG_MAX_DATA_SIZE 30
/*ͨѶ���ݽṹ*/
typedef struct
{
	u8 msg_head;   /* ��Ϣͷ ���β��� "$" ��Ϊ0x24 */
	u8 msgID;
	u8 mcuID;
	u8 dataLen;
	u8 data[MSG_MAX_DATA_SIZE];
}msg_t;



/* Э��ID */
#define MSG_HEAD '$'
/* ������IDΪmsg_id */
/*����ָ��ID*/
typedef enum 
{
	UP_VERSION	= 0x00,
	UP_STATUS		= 0x01,
	UP_ACK      = 0x02,
  UP_DATA     = 0x03,

}upmsgID_e;
/*����ָ��ID*/
typedef enum 
{
	DOWN_COMMAND	= 0x01,
	DOWN_ACK		  = 0x02,
	DOWN_REMOTOR	= 0x50,
	
}downmsgID_e;
/* mcuID�� */
typedef enum
{
	enIDBroadcast = 0x00,   // �㲥ID��
  enIDRemote    = 0x01,      // mcuID��
	enIDCar       = 0x02,      // mcuID��
	enIDEnvironment = 0x03, // mcuID��
}MCU_ID;
/*ң�������������ң����data[0]*/
typedef enum 
{
	enCMD,
	enDATA,
}remoterType_e;


/* kind:��������ң����data[1] */
typedef enum 
{
	KIND_MOVE   	= 0x01,
	KIND_LED		  = 0x02,
	KIND_MOTOR	  = 0x03,
	KIND_ENCODER	= 0x04,
	KIND_UI     	= 0x05,
	KIND_KEY     	= 0x06,
	
	CMD_CHANGE_MODE	=	0x21,	/*�л�ģʽ*/
	
}kind_e;

/********************************************************** 
	canͨѶ
**********************************************************/
/* can֡ID */
/* data[0] ΪMCUID��ͬ�� */
/* data[1] ΪCMD��DATA��ͬ�� */
/* data[2] Ϊһ�� */
/* data[3] Ϊ���� */
/* data[4-7] ���� */

/* can֡ID */
#define 	CAN_EVNID    0x031
#define 	CAN_LEDID    0x032
#define 	CAN_KEYID    0x033
#define 	CAN_TIMEID   0x034
#define 	CAN_UIID     0x035
#define 	CAN_MOTORID  0x036

/* data[2] Ϊһ�� */
/* ����kind */
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
#define   CAN_CARMOTORA    0x61
#define   CAN_CARMOTORB    0x62
#define   CAN_CARMOTORC    0x63
#define   CAN_CARMOTORD    0x64

/* data[3] Ϊ���� */
/* ��������kind */
#define 	CAN_Temperature  0x11
#define 	CAN_Humidity     0x12
#define 	CAN_Light        0x13
#define 	CAN_PM2_5        0x14
#define 	CAN_PM10         0x15
#define 	CAN_Pressure     0x16
#define 	CAN_Hight        0x17
#define 	CAN_PriAD        0x18
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
#define 	CAN_PwmOut       0x61
#define 	CAN_Encoder      0x65


/* �����α�����ַ�������   5λ���� */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);

/* ͨѶ���ַ�װ */

void msgAnalyze(msg_t *p);
void canmsgAnalyze(CanRxMsg *p);
#endif /* __USART_H */
