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
  enIDRemote = 0x00,      // mcuID��
	enIDCar    = 0x01,      // mcuID��
	enIDEnvironment = 0x02, // mcuID��
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


/* �����α�����ַ�������   5λ���� */
char Protocol3_EncodeCInt(char* ProtocolString, const char *pSrc,long int pnum, u8 pSite);


/* ͨѶ���ַ�װ */
/* ͨ�� */
void sendCmd(upmsgID_e msg_id,MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait);
void sendData(upmsgID_e msg_id,MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);

void sendRmotorCmd(MCU_ID mcu_id,kind_e cmd, u8 data,TickType_t xTicksToWait);
void sendRmotorData(MCU_ID mcu_id,kind_e kind,u8 *data, u8 len,TickType_t xTicksToWait);

void msgAnalyze(msg_t *p);
#endif /* __USART_H */
