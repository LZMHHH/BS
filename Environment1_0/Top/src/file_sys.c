#include "file_sys.h"

#if IFFILESYSTEM

FATFS fs_sd;  //sd��


/*
*********************************************************************************************************
*	�� �� ��: File_sys_init
*	����˵��: �ļ�ϵͳ��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void File_sys_init(void)
{
  u8 num_time = 0;  //ѭ����ʼ��SD��ʱ
	while(SD_Init())
	{
		
		Usar1_SendString(DEBUG1_USARTx,"SD Card Error!\r\n");
		Usar1_SendString(DEBUG1_USARTx,"Please Check!\r\n");
		num_time++;
		if(num_time > 30)  //3������
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
*	�� �� ��: File_sys_init
*	����˵��: �ļ�ϵͳ��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void File_sys_init_rtos(void)
{
  u8 num_time = 0;  //ѭ����ʼ��SD��ʱ
	
	//ͨ��
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdTRUE */
	const      TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	
	while(SD_Init())
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             "SD Card Error!\r\n",     /* ���͵���Ϣ���� */
                             xMaxBlockTime);           /* �ȴ�ʱ�� 0.5 */
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             "Please Check!\r\n",      /* ���͵���Ϣ���� */
                             xMaxBlockTime);           /* �ȴ�ʱ�� 0.5 */
		num_time++;
		if(num_time > 30)  //3������
		{
				xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             "Ignore SD Card!\r\n",        /* ���͵���Ϣ���� */
                             xMaxBlockTime);               /* �ȴ�ʱ�� 0.5 */
				break;
		}
	}
	if(num_time <= 30)
	{
		xReturn = xQueueReceive( xQueue_uart1Tx,           /* ��Ϣ���еľ�� */
                             "The SD Card was inserted successfully!\r\n",        /* ���͵���Ϣ���� */
                             xMaxBlockTime);               /* �ȴ�ʱ�� 0.5 */
	}

}

#endif







