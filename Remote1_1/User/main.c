
/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   主函数.
  ******************************************************************************
  * @attention
  *
  * 实验平台:LZM
  * 
  * Wechat：qabc132321
  *
	* FreeRTOS  毕设遥控器
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
											变量声明
**********************************************************************************************************
*/
//static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskLed  = NULL;
static TaskHandle_t xHandleTaskKey  = NULL;
static TaskHandle_t xHandleTaskUart1Rx   = NULL;  //串口任务
static TaskHandle_t xHandleTaskUart1Tx   = NULL;  //串口任务
			 TaskHandle_t xHandleTaskDisplay   = NULL;  //显示任务
			 TaskHandle_t xHandleTaskJoyStick  = NULL;  //摇杆任务
			 TaskHandle_t xHandleTaskMpu       = NULL;  //Mpu任务

		
/* 消息队列的句柄 */		
/* 长数据队列句柄 */
       TaskHandle_t xQueue_uart1Rx  = NULL;  //uart1的接收消息队列
			 TaskHandle_t xQueue_uart1Tx  = NULL;  //uart1的发送消息队列

//普通值队列句柄
			 TaskHandle_t vQueue_JoystickLeft  = NULL; //左摇杆Data句柄
			 TaskHandle_t vQueue_JoystickRight = NULL; //右摇杆Data句柄


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
	
	//硬件初始化
  bsp_Init();
	
	/* 显示数据初始化 */
	DisplayInit();
	
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
	
    xTaskCreate( vTaskLed,   	        /* 任务函数  */
                 "Task Led",     	    /* 任务名    */
                 128,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 6,                 	/* 任务优先级*/
                 &xHandleTaskLed );   /* 任务句柄  */
	
	  xTaskCreate( vTaskKey,   	        /* 任务函数  */
                 "Task Key",     	    /* 任务名    */
                 128,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 9,                 	/* 任务优先级*/
                 &xHandleTaskKey );   /* 任务句柄  */
	
		xTaskCreate( vTaskDisplay,   	      /* 任务函数  */
							 "Task Display",          /* 任务名    */
							 256,                   	/* 任务栈大小，单位word，也就是4字节 */
							 NULL,              	    /* 任务参数  */
							 7,                     	/* 任务优先级*/
							 &xHandleTaskDisplay );   /* 任务句柄  */
							 
		xTaskCreate( vTaskMpu,  	          /* 任务函数  */
							 "Task Mpu",              /* 任务名    */
							 128,                   	/* 任务栈大小，单位word，也就是4字节 */
							 NULL,              	    /* 任务参数  */
							 10,                     	/* 任务优先级*/
							 &xHandleTaskMpu );       /* 任务句柄  */
		
		xTaskCreate( vTaskJoystick,   	    /* 任务函数  */
							 "Task JoyStick",         /* 任务名    */
							 128,                   	/* 任务栈大小，单位word，也就是4字节 */
							 NULL,              	    /* 任务参数  */
							 11,                     	/* 任务优先级*/
							 &xHandleTaskJoyStick );  /* 任务句柄  */
							 
		xTaskCreate( vTaskUart1Rx,   	        /* 任务函数  */
								 "Task Uart1Rx",          /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 12,                 	    /* 任务优先级*/
								 &xHandleTaskUart1Rx );   /* 任务句柄  */
								 
		xTaskCreate( vTaskUart1Tx,   	        /* 任务函数  */
								 "Task Uart1Rx",          /* 任务名    */
								 256,                   	/* 任务栈大小，单位word，也就是4字节 */
								 NULL,              	    /* 任务参数  */
								 12,                 	    /* 任务优先级*/
								 &xHandleTaskUart1Tx );   /* 任务句柄  */
	
}


/*
*********************************************************************************************************
*	函 数 名: AppObjCreate
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

/* 
	创建普通值队列句柄 
*/

  /* 创建左摇杆数据队列 */
  vQueue_JoystickLeft  = xQueueCreate((UBaseType_t ) 1,                  /* 消息队列的长度 */
                                     (UBaseType_t ) sizeof(CLASS_Joystick));   /* 消息的大小 */
	/* 创建右摇杆数据队列 */
  vQueue_JoystickRight = xQueueCreate((UBaseType_t ) 1,                  /* 消息队列的长度 */
                                     (UBaseType_t ) sizeof(CLASS_Joystick));   /* 消息的大小 */


}
