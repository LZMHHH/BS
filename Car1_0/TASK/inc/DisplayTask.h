/**
  ******************************************************************************
  * @file    DisplayTask.h
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef __DISPLAYTASK_H
#define __DISPLAYTASK_H	 
#include "includes.h"


/* 状态机表 */
typedef enum 
{
    MAIN_ui,      /* 主模式 */
	  CAR_ui,       /* 小车模式 */
    ENVI_ui,      /* 环境监控模式 */
}ui_mode;

#define Num_Para_Max   16                  //单页最多参数限制
/* 别名 */
typedef  struct  class_uiconfigParam    CLASS_UIconfigParam;
/* 界面显示参数 */
struct class_uiconfigParam 
{
	u8       Page_Index_Limit;      //横页限制（实际页=P+1;）
	u8       Para_Index_Limit[10];      //各页参数限制Page_Index_Limit+1
	u8       Step_Index_Limit;      //步长限制（实际步长=P+1;）
	float    Step_Size[10];             //步长Step_Index_Limit+1
	u8       Para_Index_Show[20];       //单页参数显示控制  0 不显示  1 显示N um_Para_Max+1。用于参数纵向超出页面
	
	u8       Step_Index;            //步长索引
	u8       Page_Index;            //页面索引
	u8       Page_Index_Last;       //上次页面索引
	u8       Para_Index;            //参数索引
	u8       Para_IfControl;        //参数是否可控
	
	u8       Sync;                  //是否与外同步
};




void setShow_ui(ui_mode ui);
void vTaskDisplay( void * pvParameters );
void Show_Para_Con(CLASS_UIconfigParam *ui_configparam);
void DisplayInit(void);

#endif







