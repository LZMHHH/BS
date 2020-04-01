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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "FileTask.h"

#if IFFILESYSTEM

void vTaskFile( void * pvParameters )
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	
	/* 挂载文件系统 */
	xReturn = f_mount(&fs_sd, "0:/", 0);
	/* 如果SD卡中没有lss32文件，会进行创建 */
	xReturn = f_mkdir("0:/lss32");
	/* 如果SD卡中没有lsstest文件，会进行创建 */
	xReturn = f_mkdir("0:/lsstest");
	while(1)
	{


	
	
		vTaskDelay( 1000 );
	}
}

#endif



