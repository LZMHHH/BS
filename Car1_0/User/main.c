
/**
  ******************************************************************************
  * @file    main.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:LZM
  * 
  * Wechat��qabc132321
  *
	*         RO-data ��ʾ ������ĳ��� const temp;
	*					RW-data ��ʾ �ѳ�ʼ����ȫ�ֱ���
	*					ZI-data ��ʾ δ��ʼ����ȫ�ֱ���
	*					
	*					����ʱ �� RAM = RW+ZI
	*					��дʱ �� Flash = Code + RO + RW
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
void AppTaskCreate ( void );
void AppObjCreate  ( void );
//void vTaskLed      ( void * pvParameters );
//void vTaskCpu      ( void * pvParameters );
//void vTaskKey      ( void * pvParameters );
//void vTaskDisplay  ( void * pvParameters );
//void vTaskUart1Rx  ( void * pvParameters );
//void vTaskUart1Tx  ( void * pvParameters );
//void vTaskCanRx    ( void * pvParameters );
//void vTaskCanTx    ( void * pvParameters );
//void vTaskMoveCtrl ( void * pvParameters );
//void vTaskMpu      ( void * pvParameters );
//void vTaskDistance ( void * pvParameters );


/*
**********************************************************************************************************
											������
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskLed       = NULL;  //LED����
#if IFPRINTTASK
static TaskHandle_t xHandleTaskCpu       = NULL;  //CPU����
#endif
static TaskHandle_t xHandleTaskKey       = NULL;  //KEY����
static TaskHandle_t xHandleTaskUart1Rx   = NULL;  //��������
static TaskHandle_t xHandleTaskUart1Tx   = NULL;  //��������
static TaskHandle_t xHandleTaskCanRx     = NULL;  //Can����
static TaskHandle_t xHandleTaskCan       = NULL;  //Can����
			 TaskHandle_t xHandleTaskDisplay   = NULL;  //��ʾ����
			 TaskHandle_t xHandleTaskMoveCtrl  = NULL;  //�ƶ���������
			 TaskHandle_t xHandleTaskMpu       = NULL;  //����������
			 TaskHandle_t xHandleTaskSendData  = NULL;  //�ϴ����ݴ�������
			 TaskHandle_t xHandleTaskEnvironment = NULL;  //�ϱ�������������
			 TaskHandle_t xHandleTaskDistance  = NULL;  //��������
/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */			 
       TaskHandle_t xQueue_uart1Rx       = NULL;  //uart1�Ľ�����Ϣ����
			 TaskHandle_t xQueue_uart1Tx       = NULL;  //uart1�ķ�����Ϣ����
			 TaskHandle_t xQueue_canRx         = NULL;  //can�Ľ�����Ϣ����
			 TaskHandle_t xQueue_canTx         = NULL;  //can�ķ�����Ϣ����
			 SemaphoreHandle_t BinarySem_Mpu   = NULL;  //mpu��ֵ�ź���
       EventGroupHandle_t Event_SendData = NULL;  //�ϴ������¼���־����
			 EventGroupHandle_t Event_canSendData = NULL;  //�ϴ������¼���־����



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
	
	//bsp��ʼ��
  bsp_Init();

	/* ������ʼ�� */
	ParametersInit();
		
#if IFPRINTTASK
	/* 1. ��ʼ��һ����ʱ���жϣ����ȸ��ڵδ�ʱ���жϣ������ſ��Ի��׼ȷ��ϵͳ��Ϣ ��������Ŀ�ģ�ʵ����
		  Ŀ�в�Ҫʹ�ã���Ϊ������ܱȽ�Ӱ��ϵͳʵʱ�ԡ�
	   2. Ϊ����ȷ��ȡFreeRTOS�ĵ�����Ϣ�����Կ��ǽ�����Ĺر��ж�ָ��__set_PRIMASK(1); ע�͵��� 
	*/
	vSetupSysInfoTest();
#endif	
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
	
    xTaskCreate( vTaskLed,   	            /* ������  */
                 "Task Led",     	        /* ������    */
                 128,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	    /* �������  */
                 6,                     	/* �������ȼ�*/
                 &xHandleTaskLed );       /* ������  */
#if IFPRINTTASK	
		xTaskCreate( vTaskCpu,   	            /* ������  */
                 "Task Cpu",     	        /* ������    */
                 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              	    /* �������  */
                 3,                     	/* �������ȼ�*/
                 &xHandleTaskCpu );       /* ������  */
#endif	
	  xTaskCreate( vTaskKey,   	            /* ������  */
                 "Task Key",     	        /* ������    */
                 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,                  	/* �������  */
                 6,                     	/* �������ȼ�*/
                 &xHandleTaskKey );       /* ������  */

		xTaskCreate( vTaskDisplay,   	      /* ������  */
							   "Task Display",          /* ������    */
							   256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							   NULL,              	    /* �������  */
							   7,                     	/* �������ȼ�*/
							   &xHandleTaskDisplay );   /* ������  */

		xTaskCreate( vTaskMoveCtrl,   	      /* ������  */
							   "Task MoveCtrl",          /* ������    */
							   256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							   NULL,              	    /* �������  */
							   11,                     	/* �������ȼ�*/
							   &xHandleTaskMoveCtrl );   /* ������  */
								 
		xTaskCreate( vTaskDistance,   	      /* ������  */
							   "Task Distance",         /* ������    */
							   128,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
							   NULL,              	    /* �������  */
							   10,                     	/* �������ȼ�*/
							   &xHandleTaskMoveCtrl );   /* ������  */
								 
//		xTaskCreate( vTaskMpu,   	             /* ������  */
//							   "Task Mpu",               /* ������    */
//							   256,                   	 /* ����ջ��С����λword��Ҳ����4�ֽ� */
//							   NULL,              	     /* �������  */
//							   11,                     	 /* �������ȼ�*/
//							   &xHandleTaskMpu );        /* ������  */

	  xTaskCreate( vTaskUart1Rx,   	        /* ������  */
								 "Task Uart1Rx",          /* ������    */
								 512,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 13,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Rx );   /* ������  */
								 
		xTaskCreate( vTaskUart1Tx,   	        /* ������  */
								 "Task Uart1Tx",          /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 12,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Tx );   /* ������  */
								 
		xTaskCreate( vTaskCanRx,   	          /* ������  */
								 "Task CanRx",            /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 12,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Rx );   /* ������  */
								 
		xTaskCreate( vTaskCanTx,   	          /* ������  */
								 "Task CanTx",            /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 12,                 	    /* �������ȼ�*/
								 &xHandleTaskUart1Tx );   /* ������  */
		
		xTaskCreate( vTaskcanSendData,   	      /* ������  */
								 "Task SendData",         /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 10,                 	    /* �������ȼ�*/
								 &xHandleTaskSendData );  /* ������  */
						
//		xTaskCreate( vTaskEnvironment,   	      /* ������  */
//								 "Task Environment",        /* ������    */
//								 256,                   	  /* ����ջ��С����λword��Ҳ����4�ֽ� */
//								 NULL,              	      /* �������  */
//								 10,                 	      /* �������ȼ�*/
//								 &xHandleTaskEnvironment ); /* ������  */
		
		xTaskCreate( vTaskSendData,   	      /* ������  */
								 "Task Uart1Tx",          /* ������    */
								 256,                   	/* ����ջ��С����λword��Ҳ����4�ֽ� */
								 NULL,              	    /* �������  */
								 10,                 	    /* �������ȼ�*/
								 &xHandleTaskSendData );  /* ������  */

	
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
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
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 10,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) DEBUG1_RX_BSIZE);   /* ��Ϣ�Ĵ�С */
	
	 /* xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 10,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) DEBUG1_TX_BSIZE);   /* ��Ϣ�Ĵ�С */
	
#else
	/* �����洢ָ�����xQueue_uart1Tx */
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 10,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) sizeof(uint32_t));   /* ��Ϣ�Ĵ�С */
	
	/* �����洢ָ�����xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 10,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) sizeof(uint32_t));   /* ��Ϣ�Ĵ�С */
	
#endif	
	if(NULL != xQueue_uart1Rx && NULL != xQueue_uart1Tx)
	{
//		Uart1_DMA_SendString("������Ϣ���гɹ�!\r\n",-1);
	}

	 /* xQueue_canTx */
  xQueue_canRx = xQueueCreate((UBaseType_t ) 15,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) (sizeof(CanRxMsg)+2));   /* ��Ϣ�Ĵ�С */
	
	 /* xQueue_canRx */
  xQueue_canTx = xQueueCreate((UBaseType_t ) 15,                  /* ��Ϣ���еĳ��� */
                                (UBaseType_t ) (sizeof(CanTxMsg)+2));   /* ��Ϣ�Ĵ�С */

	 /* ���� BinarySem */
  BinarySem_Mpu = xSemaphoreCreateBinary();	 
  if(NULL != BinarySem_Mpu)
	{
//    Uart1_DMA_SendString("BinarySem_Handle��ֵ�ź��������ɹ�!\r\n",-1);
	}
	
	 /* ���� Event_Handle */
  Event_SendData = xEventGroupCreate();	 

	Event_canSendData = xEventGroupCreate();	 
}

