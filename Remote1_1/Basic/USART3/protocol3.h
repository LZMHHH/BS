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
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __PROTOCOL3_H
#define	__PROTOCOL3_H


#include "includes.h" 

/*�ϱ�״̬ö��*/
typedef enum
{
  enReTno = 0,  //       ���ݴ��Ϳ���  (Ҳ����˵������ϵĻع�)
	enReTing,     //       ���ݱ������,���뷢��״̬
	enReTed,      //       ���ͺ����Ѿ�ִ��
}State_ReData;

/* mcuID�� */
typedef enum
{
  enIDRemote = 0x00,      // mcuID��
	enIDCAR    = 0x01,      // mcuID��
	enIDEnvironment = 0x02, // mcuID��
}MCU_ID;

/*ң���������*/
typedef enum 
{
	enCMD,
	enDATA,
}remoterType_e;

#define MSG_MAX_DATA_SIZE 30
/*ͨѶ���ݽṹ*/
typedef struct
{
	u8 msgID;
	u8 mcuID;
	u8 dataLen;
	u8 data[MSG_MAX_DATA_SIZE];
}msg_t;


/* Э��ID */
/*����ָ��ID*/
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

/*����ָ��ID*/
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

/*��������*/
/* car */
#define  CMD_CHANGE_MODE		0x01	/*�л�ģʽ*/




/* �����α�����ַ�������   5λ���� */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);


/* ͨѶ���ַ�װ */
void sendRmotorCmd(MCU_ID mcu_id,u8 cmd, u8 data,TickType_t xTicksToWait);
void sendRmotorData(MCU_ID mcu_id,u8 *data, u8 len,TickType_t xTicksToWait);

#endif /* __USART_H */
