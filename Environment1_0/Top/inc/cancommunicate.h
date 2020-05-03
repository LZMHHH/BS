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

/*UI同步*/
typedef struct _ui_t
{
	u8       Sync;                  //是否开启同步模式0：不开启
	
	u8       Step_Index;            //步长索引
	u8       Page_Index;            //页面索引
	u8       Page_Index_Last;       //上次页面索引
	u8       Para_Index;            //参数索引
	u8       Para_IfControl;        //参数是否可控

}ui_t;

/* 防爆墙 */
typedef struct _connect_t connect_t;
/* 广播 */
extern connect_t   canConnect;
extern ui_t        carUIPara;


void canCommunicateParaInit(void);


#endif /* __USART_H */
