
/**
  ******************************************************************************
  * @file    main.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  * 实验平台:LZM
  * 
  * Wechat：qabc132321
  *
	*         RO-data 表示 程序定义的常量 const temp;
	*					RW-data 表示 已初始化的全局变量
	*					ZI-data 表示 未初始化的全局变量
	*					
	*					运行时 即 RAM = RW+ZI
	*					烧写时 即 Flash = Code + RO + RW
  ******************************************************************************
  */

#include "includes.h"

//1 printf，  是把格式字符串输出到标准输出（一般是屏幕，可以重定向）。
//2 sprintf， 是把格式字符串输出到指定字符串中，所以参数比printf多一个char*。那就是目标字符串地址。
//3 fprintf， 是把格式字符串输出到指定文件设备中，所以参数笔printf多一个文件指针FILE*。


/*
**********************************************************************************************************
											函数声明
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
//void vTaskFile     ( void * pvParameters );
//void vTaskCheck    ( void * pvParameters );
//void vTaskInit     ( void * pvParameters );
//void vTaskEnvironment( void * pvParameters );
//void vTaskClock    ( void * pvParameters );
//void vTaskLight    ( void * pvParameters );
//void vTaskPms      ( void * pvParameters );
//void vTaskBme      ( void * pvParameters );



/*
**********************************************************************************************************
											句柄变量声明
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskLed       = NULL;  //LED任务
#if IFPRINTTASK
static TaskHandle_t xHandleTaskCpu       = NULL;  //CPU任务
#endif
static TaskHandle_t xHandleTaskKey       = NULL;  //KEY任务
static TaskHandle_t xHandleTaskUart1Rx   = NULL;  //KEY任务
static TaskHandle_t xHandleTaskUart1Tx   = NULL;  //KEY任务
static TaskHandle_t xHandleTaskCanRx     = NULL;  //Can任务
static TaskHandle_t xHandleTaskCanTx     = NULL;  //Can任务
			 TaskHandle_t xHandleTaskDisplay   = NULL;  //显示任务
			 TaskHandle_t xHandleTaskEnvironment = NULL;  //环境数据采集任务
			 TaskHandle_t xHandleTaskClock     = NULL;  //时钟任务
			 TaskHandle_t xHandleTaskLight     = NULL;  //亮度任务
			 TaskHandle_t xHandleTaskPms       = NULL;  //PMs任务
			 TaskHandle_t xHandleTaskBme       = NULL;  //大气压任务
			 TaskHandle_t xHandleTaskSendData  = NULL;  //上传数据处理任务
			 
/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 * 
 */			 
       TaskHandle_t xQueue_uart1Rx       = NULL;  //uart1的接收消息队列
			 TaskHandle_t xQueue_uart1Tx       = NULL;  //uart1的发送消息队列
			 TaskHandle_t xQueue_uart2Rx       = NULL;  //uart2的接收消息队列
			 TaskHandle_t xQueue_canRx         = NULL;  //can的接收消息队列
			 TaskHandle_t xQueue_canTx         = NULL;  //can的发送消息队列
			 EventGroupHandle_t Event_canSendData = NULL;  //上传数据事件标志着组

#if IFFILESYSTEM
			 TaskHandle_t xHandleTaskFile      = NULL;  //file任务
			 TaskHandle_t xHandleTaskCheck     = NULL;  //file任务
			 TaskHandle_t xHandleTaskInit      = NULL;  //file任务
#endif




int main(void)
{
	/* 
	  在启动调度前，为了防止初始化STM32外设时有中断服务程序执行，这里禁止全局中断(除了NMI和HardFault)。
	  这样做的好处是：
	  1. 防止执行的中断服务程序中有FreeRTOS的API函数。
	  2. 保证系统正常启动，不受别的中断影响。
	  3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
	  在移植文件port.c中的函数prvStartFirstTask中会重新开启全局中断。通过指令cpsie i开启，__set_PRIMASK(1)
	  和cpsie i是等效的。
     */
	__set_PRIMASK(1);
	
	//bsp初始化
	bsp_Init();
	
	/* 参数初始化 */
	ParametersInit();

#if IFPRINTTASK
	/* 1. 初始化一个定时器中断，精度高于滴答定时器中断，这样才可以获得准确的系统信息 仅供调试目的，实际项
		  目中不要使用，因为这个功能比较影响系统实时性。
	   2. 为了正确获取FreeRTOS的调试信息，可以考虑将上面的关闭中断指令__set_PRIMASK(1); 注释掉。 
	*/
	vSetupSysInfoTest();
#endif	
	/* 创建任务 */
	AppTaskCreate();
	
	/* 创建消息 */
	AppObjCreate();
	
	/* 启动调度，开始执行任务 */
	vTaskStartScheduler();

	/* 
	  如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
	  heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
	

	  
	
}


/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
	
    xTaskCreate( vTaskLed,   	            /* 任务函数  */
                 "Task Led",     	        /* 任务名    */
                 64,                   	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	    /* 任务参数  */
                 6,                     	/* 任务优先级*/
                 &xHandleTaskLed );       /* 任务句柄  */
#if IFPRINTTASK	
		xTaskCreate( vTaskCpu,   	            /* 任务函数  */
                 "Task Cpu",     	        /* 任务名    */
                 256,                   	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	    /* 任务参数  */
                 3,                     	/* 任务优先级*/
                 &xHandleTaskCpu );       /* 任务句柄  */
#endif	
	  xTaskCreate( vTaskKey,   	            /* 任务函数  */
                 "Task Key",     	        /* 任务名    */
                 256,                   	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,                  	/* 任务参数  */
                 7,                     	/* 任务优先级*/
                 &xHandleTaskKey );       /* 任务句柄  */

		xTaskCreate( vTaskDisplay,   	      /* 任务函数  */
			   "Task Display",          /* 任务名    */
			   512,                   	/* 任务栈大小，单位word，也就是4字节 */
			   NULL,              	    /* 任务参数  */
			   6,                     	/* 任务优先级*/
			   &xHandleTaskDisplay );   /* 任务句柄  */


//	  xTaskCreate( vTaskUart1Rx,   	        /* 任务函数  */
//								 "Task Uart1Rx",          /* 任务名    */
//								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
//								 NULL,              	    /* 任务参数  */
//								 12,                 	    /* 任务优先级*/
//								 &xHandleTaskUart1Rx );   /* 任务句柄  */
//								 
//		xTaskCreate( vTaskUart1Tx,   	        /* 任务函数  */
//								 "Task Uart1Rx",          /* 任务名    */
//								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
//								 NULL,              	    /* 任务参数  */
//								 12,                 	    /* 任务优先级*/
//								 &xHandleTaskUart1Tx );   /* 任务句柄  */
								 
		xTaskCreate( vTaskCanRx,   	          /* 任务函数  */
								 "Task CanRx",            /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 12,                 	    /* 任务优先级*/
								 &xHandleTaskCanRx );     /* 任务句柄  */
								 
		xTaskCreate( vTaskCanTx,   	          /* 任务函数  */
								 "Task CanTx",            /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 12,                 	    /* 任务优先级*/
								 &xHandleTaskCanTx );     /* 任务句柄  */
								 
		xTaskCreate( vTaskcanSendData,   	      /* 任务函数  */
								 "Task SendData",         /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 11,                 	    /* 任务优先级*/
								 &xHandleTaskSendData );  /* 任务句柄  */

		xTaskCreate( vTaskEnvironment,   	      /* 任务函数  */
								 "Task Environment",        /* 任务名    */
								 256,                   	  /* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	      /* 任务参数  */
								 10,                 	      /* 任务优先级*/
								 &xHandleTaskEnvironment ); /* 任务句柄  */

		xTaskCreate( vTaskClock,   	            /* 任务函数  */
								 "Task Clock",              /* 任务名    */
								 128,                   	  /* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	      /* 任务参数  */
								 10,                 	      /* 任务优先级*/
								 &xHandleTaskClock );       /* 任务句柄  */

		xTaskCreate( vTaskLight,   	            /* 任务函数  */
								 "Task Light",              /* 任务名    */
								 128,                   	  /* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	      /* 任务参数  */
								 10,                 	      /* 任务优先级*/
								 &xHandleTaskLight );       /* 任务句柄  */
								 
		xTaskCreate( vTaskPms,   	              /* 任务函数  */
								 "Task Pms",                /* 任务名    */
								 128,                   	  /* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	      /* 任务参数  */
								 10,                 	      /* 任务优先级*/
								 &xHandleTaskPms );         /* 任务句柄  */
								 
		xTaskCreate( vTaskBme,   	              /* 任务函数  */
								 "Task Bme",                /* 任务名    */
								 256,                   	  /* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	      /* 任务参数  */
								 10,                 	      /* 任务优先级*/
								 &xHandleTaskBme );         /* 任务句柄  */


#if IFFILESYSTEM								 
		xTaskCreate( vTaskFile,   	          /* 任务函数  */
								 "Task File",             /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 8,                 	    /* 任务优先级*/
								 &xHandleTaskFile );      /* 任务句柄  */
								 
		xTaskCreate( vTaskCheck,   	        /* 任务函数  */
								 "Task Check",          /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 8,                 	    /* 任务优先级*/
								 &xHandleTaskCheck );   /* 任务句柄  */
								 
		xTaskCreate( vTaskInit,   	          /* 任务函数  */
								 "Task Init",             /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 8,                 	    /* 任务优先级*/
								 &xHandleTaskInit );      /* 任务句柄  */
#endif	
	
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建任务通信机制
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppObjCreate (void)
{
	
	/*****重要，注意消息接收地址数组要>=创建的单个消息大小。
				
				消息队列原理是copy data,如果把那个data赋值为指针，就相当于其他RTOS的原理：传地址。
	*****/

#if DEBUG1_SAFETY	
	 /* xQueue_uart1Tx */
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 5,                  /* 消息队列的长度 */
                                (UBaseType_t ) DEBUG1_RX_BSIZE);   /* 消息的大小 */
	
	 /* xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 1,                  /* 消息队列的长度 */
                                (UBaseType_t ) DEBUG1_TX_BSIZE);   /* 消息的大小 */
	
#else
	/* 创建存储指针变量xQueue_uart1Tx */
  xQueue_uart1Rx = xQueueCreate((UBaseType_t ) 5,                  /* 消息队列的长度 */
                                (UBaseType_t ) sizeof(uint32_t));   /* 消息的大小 */
	
	/* 创建存储指针变量xQueue_uart1Rx */
  xQueue_uart1Tx = xQueueCreate((UBaseType_t ) 5,                  /* 消息队列的长度 */
                                (UBaseType_t ) sizeof(uint32_t));   /* 消息的大小 */
	
#endif	

	/* 创建存储指针变量xQueue_uart2Tx */
  xQueue_uart2Rx = xQueueCreate((UBaseType_t ) 5,                  /* 消息队列的长度 */
                                (UBaseType_t ) DEBUG1_TX_BSIZE);   /* 消息的大小 */
					
	/* xQueue_canTx */
  xQueue_canRx = xQueueCreate((UBaseType_t ) 25,                  /* 消息队列的长度 */
                                (UBaseType_t ) (sizeof(CanRxMsg)+2));   /* 消息的大小 */
	
	 /* xQueue_canRx */
  xQueue_canTx = xQueueCreate((UBaseType_t ) 25,                  /* 消息队列的长度 */
                                (UBaseType_t ) (sizeof(CanTxMsg)+2));   /* 消息的大小 */
																

	/* 创建 Event_canSendData */
  Event_canSendData = xEventGroupCreate();	 

}

