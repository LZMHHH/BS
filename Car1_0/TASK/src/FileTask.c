/**
  ******************************************************************************
  * @file    FileTask.c
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
#include "FileTask.h"

#if IFFILESYSTEM

void vTaskFile( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	
	/* �����ļ�ϵͳ */
	xReturn = f_mount(&fs_sd, "0:/", 0);
	/* ���SD����û��lss32�ļ�������д��� */
	xReturn = f_mkdir("0:/lss32");
	/* ���SD����û��lsstest�ļ�������д��� */
	xReturn = f_mkdir("0:/lsstest");
	while(1)
	{


	
	
		vTaskDelay( 1000 );
	}
}

#endif



