/**
  ******************************************************************************
  * @file    bsp_encoder.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   编码器配置.
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "bsp_encoder.h"
 
 
/**************************************************************************
函数功能：把TIM3初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder1_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE1_TIM_APBxClock_FUN(ENCODE1_TIM_CLK, ENABLE);             //使能定时器3的时钟
  ENCODE1_GPIO_APBxClock_FUN(ENCODE1_TIM_A_GPIO_CLK|ENCODE1_TIM_B_GPIO_CLK|RCC_APB2Periph_AFIO , ENABLE);    //使能PB端口时钟

	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);//打开重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//禁止JTAG功能，把PB3，PB4作为普通IO口使用
	
	//  I/O口配置
  GPIO_InitStructure.GPIO_Pin =  ENCODE1_TIM_A_PIN;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
  GPIO_Init(ENCODE1_TIM_A_PORT, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
  
	//  I/O口配置
  GPIO_InitStructure.GPIO_Pin =  ENCODE1_TIM_B_PIN;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
  GPIO_Init(ENCODE1_TIM_B_PORT, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
	
	//**************定时器时基结构体配置***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);            //先把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入 //Fills each TIM_TimeBaseInitStruct member with its default value.
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器    不分频 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM向上计数  
  TIM_TimeBaseInit(ENCODE1_TIM, &TIM_TimeBaseStructure);      //初始化定时器
	
	//硬件编码器接口   这里A/B都采用上升触发    除了高级定时器以外，其它定时器的的编码器接口只能是channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
	
	//输入捕获配置                                       //因为用到编码器接口函数就对于默认配置好了其它参数
  TIM_ICStructInit(&TIM_ICInitStructure);             //先把TIM_ICInitStructure中的每一个参数按缺省值填入
  TIM_ICInitStructure.TIM_ICFilter = 10;              //输入捕获过滤器
  TIM_ICInit(ENCODE1_TIM, &TIM_ICInitStructure);      //初始化外围设备
  TIM_ClearFlag(ENCODE1_TIM, TIM_FLAG_Update);        //清除TIM的更新标志位
  TIM_ITConfig(ENCODE1_TIM, TIM_IT_Update, ENABLE);   //启用中断
	
  //Reset counter
  TIM_SetCounter(ENCODE1_TIM,0);
  TIM_Cmd(ENCODE1_TIM, ENABLE); 
}
/**************************************************************************
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder2_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE2_TIM_CLK, ENABLE);//使能定时器4的时钟
  ENCODE2_GPIO_APBxClock_FUN(ENCODE2_TIM_A_GPIO_CLK, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = ENCODE2_TIM_A_PIN|ENCODE2_TIM_B_PIN;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
  GPIO_Init(ENCODE2_TIM_A_PORT, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
	//**************定时器时基结构体配置***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //先把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM向上计数  
  TIM_TimeBaseInit(ENCODE2_TIM, &TIM_TimeBaseStructure);          //初始化定时器
	
	//硬件编码器接口   这里A/B都采用上升触发    除了高级定时器以外，其它定时器的的编码器接口只能是channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  
	//输入捕获配置                                                   //因为用到编码器接口函数就对于默认配置好了其它参数
	TIM_ICStructInit(&TIM_ICInitStructure);                         //先把TIM_ICInitStructure中的每一个参数按缺省值填入
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //输入捕获过滤器
  TIM_ICInit(ENCODE2_TIM, &TIM_ICInitStructure);                  //初始化外围设备
  TIM_ClearFlag(ENCODE2_TIM, TIM_FLAG_Update);                    //清除TIM的更新标志位
  TIM_ITConfig(ENCODE2_TIM, TIM_IT_Update, ENABLE);               //启用中断
	
  //Reset counter
  TIM_SetCounter(ENCODE2_TIM,0);
  TIM_Cmd(ENCODE2_TIM, ENABLE); 
}
/**************************************************************************
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder3_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE3_TIM_CLK, ENABLE);//使能定时器4的时钟
  ENCODE2_GPIO_APBxClock_FUN(ENCODE3_TIM_A_GPIO_CLK, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = ENCODE3_TIM_A_PIN|ENCODE3_TIM_B_PIN;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
  GPIO_Init(ENCODE2_TIM_A_PORT, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
	//**************定时器时基结构体配置***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //先把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM向上计数  
  TIM_TimeBaseInit(ENCODE3_TIM, &TIM_TimeBaseStructure);          //初始化定时器
	
	//硬件编码器接口   这里A/B都采用上升触发    除了高级定时器以外，其它定时器的的编码器接口只能是channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE3_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  
	//输入捕获配置                                                   //因为用到编码器接口函数就对于默认配置好了其它参数
	TIM_ICStructInit(&TIM_ICInitStructure);                         //先把TIM_ICInitStructure中的每一个参数按缺省值填入
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //输入捕获过滤器
  TIM_ICInit(ENCODE3_TIM, &TIM_ICInitStructure);                  //初始化外围设备
  TIM_ClearFlag(ENCODE3_TIM, TIM_FLAG_Update);                    //清除TIM的更新标志位
  TIM_ITConfig(ENCODE3_TIM, TIM_IT_Update, ENABLE);               //启用中断
	
  //Reset counter
  TIM_SetCounter(ENCODE3_TIM,0);
  TIM_Cmd(ENCODE3_TIM, ENABLE); 
}

/**************************************************************************
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder4_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE4_TIM_CLK, ENABLE);//使能定时器4的时钟
  ENCODE2_GPIO_APBxClock_FUN(ENCODE4_TIM_A_GPIO_CLK, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = ENCODE4_TIM_A_PIN|ENCODE4_TIM_B_PIN;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //浮空输入
  GPIO_Init(ENCODE4_TIM_A_PORT, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
	//**************定时器时基结构体配置***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //先把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM向上计数  
  TIM_TimeBaseInit(ENCODE4_TIM, &TIM_TimeBaseStructure);          //初始化定时器
	
	//硬件编码器接口   这里A/B都采用上升触发    除了高级定时器以外，其它定时器的的编码器接口只能是channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE4_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  
	//输入捕获配置                                                   //因为用到编码器接口函数就对于默认配置好了其它参数
	TIM_ICStructInit(&TIM_ICInitStructure);                         //先把TIM_ICInitStructure中的每一个参数按缺省值填入
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //输入捕获过滤器
  TIM_ICInit(ENCODE4_TIM, &TIM_ICInitStructure);                  //初始化外围设备
  TIM_ClearFlag(ENCODE4_TIM, TIM_FLAG_Update);                    //清除TIM的更新标志位
  TIM_ITConfig(ENCODE4_TIM, TIM_IT_Update, ENABLE);               //启用中断
	
  //Reset counter
  TIM_SetCounter(ENCODE4_TIM,0);
  TIM_Cmd(ENCODE4_TIM, ENABLE); 
}

/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 1:  Encoder_TIM= (short)ENCODE1_TIM -> CNT;  ENCODE1_TIM -> CNT=0;break;
		 case 2:  Encoder_TIM= (short)ENCODE2_TIM -> CNT;  ENCODE2_TIM -> CNT=0;break;	  
		 case 3:  Encoder_TIM= (short)ENCODE3_TIM -> CNT;  ENCODE3_TIM -> CNT=0;break;	  //编码器  
		 case 4:  Encoder_TIM= (short)ENCODE4_TIM -> CNT;  ENCODE4_TIM -> CNT=0;break;	  //编码器  
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/**************************************************************************
函数功能：TIM4中断服务函数
入口参数：无
返回  值：无
 note  ： 固件库
**************************************************************************/
void ENCODE2_TIM_INT_FUN(void)
{ 		    		  			  
	//更新与触发不一样，更新寄存器数值；计数器启动开始什么的触发；这里选更新
	if(TIM_GetITStatus( ENCODE2_TIM, TIM_IT_Update) != RESET )  //随便一个比较通道更新
	{    				   				     	    	
	}				   
	TIM_ClearITPendingBit( ENCODE2_TIM, TIM_IT_Update );//清除中断标志位 	    
}
/**************************************************************************
函数功能：TIM3中断服务函数
入口参数：无
返回  值：无
note  ： 寄存器
**************************************************************************/
void ENCODE1_TIM_INT_FUN(void)
{ 		    		  			    
	if(ENCODE1_TIM->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	ENCODE1_TIM->SR&=~(1<<0);//清除中断标志位 	    
}

