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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef __DISPLAYTASK_H
#define __DISPLAYTASK_H	 
#include "includes.h"


/* ״̬���� */
typedef enum 
{
    MAIN_ui,      /* ��ģʽ */
	  CAR_ui,       /* С��ģʽ */
    ENVI_ui,      /* �������ģʽ */
}ui_mode;

#define Num_Para_Max   16                  //��ҳ����������
/* ���� */
typedef  struct  class_uiconfigParam    CLASS_UIconfigParam;
/* ������ʾ���� */
struct class_uiconfigParam 
{
	u8       Page_Index_Limit;      //��ҳ���ƣ�ʵ��ҳ=P+1;��
	u8       Para_Index_Limit[10];      //��ҳ��������Page_Index_Limit+1
	u8       Step_Index_Limit;      //�������ƣ�ʵ�ʲ���=P+1;��
	float    Step_Size[10];             //����Step_Index_Limit+1
	u8       Para_Index_Show[20];       //��ҳ������ʾ����  0 ����ʾ  1 ��ʾN um_Para_Max+1�����ڲ������򳬳�ҳ��
	
	u8       Step_Index;            //��������
	u8       Page_Index;            //ҳ������
	u8       Page_Index_Last;       //�ϴ�ҳ������
	u8       Para_Index;            //��������
	u8       Para_IfControl;        //�����Ƿ�ɿ�
	
	u8       Sync;                  //�Ƿ�����ͬ��
};




void setShow_ui(ui_mode ui);
void vTaskDisplay( void * pvParameters );
void Show_Para_Con(CLASS_UIconfigParam *ui_configparam);
void DisplayInit(void);

#endif







