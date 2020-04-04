
/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:LZM
  * 
  * Wechat��qabc132321
  *
	* FreeRTOS  ����ң����
  ******************************************************************************
  */

#include "includes.h"

//1 printf��  �ǰѸ�ʽ�ַ����������׼�����һ������Ļ�������ض��򣩡�
//2 sprintf�� �ǰѸ�ʽ�ַ��������ָ���ַ����У����Բ�����printf��һ��char*���Ǿ���Ŀ���ַ�����ַ��
//3 fprintf�� �ǰѸ�ʽ�ַ��������ָ���ļ��豸�У����Բ�����printf��һ���ļ�ָ��FILE*��


/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static void AppTaskCreate ( void );
static void AppObjCreate  ( void );
//void vTaskLed      ( void * pvParameters );
//void vTaskKey      ( void * pvParameters );
//void vTaskDisplay  ( void * pvParameters );
//void vTaskJoyStick ( void * pvParameters );
//void vTaskMpu      ( void * pvParameters );
//void vTaskUart1Rx  ( void * pvParameters );
//void vTaskUart1Tx  ( void * pvParameters );



/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskLed  = NULL;
static TaskHandle_t xHandleTaskKey  = NULL;
static TaskHandle_t xHandleTaskUart1Rx   = NULL;  //��������
static TaskHandle_t xHandleTaskUart1Tx   = NULL;  //��������
			 TaskHandle_t xHandleTaskDisplay   = NULL;  //��ʾ����
			 TaskHandle_t xHandleTaskJoyStick  = NULL;  //ҡ������
			 TaskHandle_t xHandleTaskMpu       = NULL;  //Mpu����

		
/* ��Ϣ���еľ�� */		
/* �����ݶ��о�� */
       TaskHandle_t xQueue_uart1Rx  = NULL;  //uart1�Ľ�����Ϣ����
			 TaskHandle_t xQueue_uart1Tx  = NULL;  //uart1�ķ�����Ϣ����

//��ֵͨ���о��
			 TaskHandle_t vQueue_JoystickLeft  = NULL; //��ҡ��Data���
			 TaskHandle_t vQueue_JoystickRight = NULL; //��ҡ��Data���


int main(void)
{
	/* 
	  ����������ǰ��Ϊ�˷�ֹ��ʼ��STM32����ʱ���жϷ������ִ�У������ֹȫ���ж�(����NMI��HardFault)��
	  �������ĺô��ǣ�
	  1. ��ִֹ�е��жϷ����������FreeRTOS��API������
	  2. ��֤ϵͳ�������������ܱ���ж�Ӱ�졣
	  3. �����Ƿ�ر�ȫ���жϣ���Ҹ����Լ���ʵ��������ü��ɡ�
	  ����ֲ�ļ�port.c�еĺ���prvStartFirstTask�л����¿���ȫ���жϡ�ͨ��ָ��cpsie i������__set_PRIMASK(1)
	  ��cpsie i�ǵ�Ч�ġ�
     */
	__set_PRIMASK(1);
	
	//Ӳ����ʼ��
  bsp_Init();
	
	/* ��ʾ���ݳ�ʼ�� */
	DisplayInit();
	
	/* �������� */
	AppTaskCreate();
	
	/* ������Ϣ */
	AppObjCreate();
	
	/* �������ȣ���ʼִ������ */
	vTaskStartScheduler();

	/* 
	  ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п��������ڶ�ʱ��������߿��������
	  heap�ռ䲻����ɴ���ʧ�ܣ���Ҫ�Ӵ�FreeRTOSConfig.h�ļ��ж����heap��С��
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
	  
	
}


/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
	
    xTaskCreate( vTaskLed,   	        /* ������  */
                 "Task Led",     	    /* ������    */
                 128,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 6,                 	/* �������ȼ�*/
                 &xHandleTaskLed );   /* ������  */
	
	  xTaskCreate( vTaskKey,   	        /* ������  */
                 "Task Key",     	    /* ������    */
                 128,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	/* �������  */
                 9,                 	/* �������ȼ�*/
                 &xHandleTaskKey );   /* ������  */
	
		xTaskCreate( vTaskDisplay,   	      /* ������  */
							 "Task Display",          /* ������    */
							 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							 NULL,              	    /* �������  */
							 7,                     	/* �������ȼ�*/
							 &xHandleTaskDisplay );   /* ������  */
							 
		xTaskCreate( vTaskMpu,  	          /* ������  */
							 "Task Mpu",              /* ������    */
							 128,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							 NULL,              	    /* �������  */
							 10,                     	/* �������ȼ�*/
							 &xHandleTaskMpu );       /* ������  */
		
		xTaskCreate( vTaskJoystick,   	    /* ������  */
							 "Task JoyStick",         /* ������    */
							 128,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							 NULL,              	    /* �������  */
							 11,                     	/* �������ȼ�*/
							 &xHandleTaskJoyStick );  /* ������  */
							 
		xTaskCreate( vTaskUart1Rx,   	        /* ������  */
								 "Task Uart1Rx",          /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 12,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Rx );   /* ������  */
								 
		xTaskCreate( vTaskUart1Tx,   	        /* ������  */
								 "Task Uart1Rx",          /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 12,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Tx );   /* ������  */
	
}


/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨ�Ż���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
	/*****��Ҫ��ע����Ϣ���յ�ַ����Ҫ>=�����ĵ�����Ϣ��С��
				
				��Ϣ����ԭ����copy data,������Ǹ�data��ֵΪָ�룬���൱������RTOS��ԭ������ַ��
	*****/

#if DEBUG1_SAFETY	
	 /* xQueue_uart1Tx */
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 5,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) DEBUG1_RX_BSIZE);   /* ��Ϣ�Ĵ�С */
	
	 /* xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 1,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) DEBUG1_TX_BSIZE);   /* ��Ϣ�Ĵ�С */
	
#else
	/* �����洢ָ�����xQueue_uart1Tx */
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 5,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) sizeof(uint32_t));   /* ��Ϣ�Ĵ�С */
	
	/* �����洢ָ�����xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 5,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) sizeof(uint32_t));   /* ��Ϣ�Ĵ�С */
	
#endif	

/* 
	������ֵͨ���о�� 
*/

  /* ������ҡ�����ݶ��� */
  vQueue_JoystickLeft  = xQueueCreate((UBaseType_t ) 1,                  /* ��Ϣ���еĳ��� */
                                     (UBaseType_t ) sizeof(CLASS_Joystick));   /* ��Ϣ�Ĵ�С */
	/* ������ҡ�����ݶ��� */
  vQueue_JoystickRight = xQueueCreate((UBaseType_t ) 1,                  /* ��Ϣ���еĳ��� */
                                     (UBaseType_t ) sizeof(CLASS_Joystick));   /* ��Ϣ�Ĵ�С */


}
