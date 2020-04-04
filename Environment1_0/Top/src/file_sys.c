#include "file_sys.h"

#if IFFILESYSTEM

FATFS fs_sd;  //sd卡


/*
*********************************************************************************************************
*	函 数 名: File_sys_init
*	功能说明: 文件系统初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void File_sys_init(void)
{
  u8 num_time = 0;  //循环初始化SD计时
	while(SD_Init())
	{
		
		Usar1_SendString(DEBUG1_USARTx,"SD Card Error!\r\n");
		Usar1_SendString(DEBUG1_USARTx,"Please Check!\r\n");
		num_time++;
		if(num_time > 30)  //3秒跳过
		{
			  Usar1_SendString(DEBUG1_USARTx,"Ignore SD Card!\r\n");
				break;
		}
	}
	if(num_time <= 30)
	{
		Usar1_SendString(DEBUG1_USARTx,"The SD Card was inserted successfully!\r\n");
	}

}


/*
*********************************************************************************************************
*	函 数 名: File_sys_init
*	功能说明: 文件系统初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void File_sys_init_rtos(void)
{
  u8 num_time = 0;  //循环初始化SD计时
	
	//通信
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为pdTRUE */
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	while(SD_Init())
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             "SD Card Error!\r\n",     /* 发送的消息内容 */
                             xMaxBlockTime);           /* 等待时间 0.5 */
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             "Please Check!\r\n",      /* 发送的消息内容 */
                             xMaxBlockTime);           /* 等待时间 0.5 */
		num_time++;
		if(num_time > 30)  //3秒跳过
		{
				xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             "Ignore SD Card!\r\n",        /* 发送的消息内容 */
                             xMaxBlockTime);               /* 等待时间 0.5 */
				break;
		}
	}
	if(num_time <= 30)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* 消息队列的句柄 */
                             "The SD Card was inserted successfully!\r\n",        /* 发送的消息内容 */
                             xMaxBlockTime);               /* 等待时间 0.5 */
	}

}

#endif







