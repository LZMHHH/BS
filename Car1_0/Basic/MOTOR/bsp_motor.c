/**
  ******************************************************************************
  * @file    motor.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   电机端口初始化及 PWM 输出配置
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "bsp_motor.h"




/**  固件库
  * @brief  电机 I/O配置   
  * @param  无
  * @retval 用于正反转
  */
void MOTOR_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

/*********** 方向引脚 **************/
	
	/* 使能与 MOTORA 有关的时钟 */
	MOTORA_GPIO_APBxClock_FUN(MOTORA_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORA_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // 推挽输出 
  GPIO_Init(MOTORA_V_PORT, &GPIO_InitStructure);
	
	/* 使能与 MOTORB 有关的时钟 */
	MOTORA_GPIO_APBxClock_FUN(MOTORB_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORB_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // 推挽输出 
  GPIO_Init(MOTORB_V_PORT, &GPIO_InitStructure);
	
	/* 使能与 MOTORC 有关的时钟 */
	MOTORA_GPIO_APBxClock_FUN(MOTORC_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORC_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // 推挽输出 
  GPIO_Init(MOTORC_V_PORT, &GPIO_InitStructure);
	
	/* 使能与 MOTORD 有关的时钟 */
	MOTORA_GPIO_APBxClock_FUN(MOTORD_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORD_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // 推挽输出 
  GPIO_Init(MOTORD_V_PORT, &GPIO_InitStructure);
	
	
/*********** pwm引脚 **************/
	PWM_GPIO_APBxClock_FUN(PWM_TIM_CHANNEL_GPIO_CLK , ENABLE);   // 使能GPIO外设时钟使能
	
	//  PWM输出引脚初始化  用于信号
	//设置该引脚为复用输出功能,输出TIM1 CH2 CH3 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = PWMA_TIM_CHANNEL_PIN|PWMB_TIM_CHANNEL_PIN|PWMC_TIM_CHANNEL_PIN|PWMD_TIM_CHANNEL_PIN; //TIM_CH3 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CHANNEL_PORT, &GPIO_InitStructure);

}

/**  固件库
  * @brief  电机  定时器 PWM 配置     
  * @param  arr   ：PWM频率=72M/（arr+1）； psc ：分频
  * @retval 用于PWM配置
  */
void bsp_Motor_Init(u16 arr,u16 psc)    
{		 		
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;      //TIM Time Base Init structure definition
	  TIM_OCInitTypeDef        TIM_OCInitStructure;      // TIM Output Compare Init structure definition 
	
    MOTOR_GPIO_Init();	    //  PWM  电机I/O口初始化
	
	
	  PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, ENABLE);      // 定时器时钟初始化
 	  	
	/*--------------------时基结构体初始化-------------------------*/
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	，累计TIM_Period+1个频率后产生一个更新或者中断 
	  TIM_TimeBaseStructure.TIM_Period = arr; 
	//设置用来作为TIMx时钟频率除数的预分频值  不分频，CNT计数器的时钟 = Fck_int/(psc+1)
	  TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		//设置时钟分割:TDTS = Tck_tim，配置死区时间时需要用到
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
		//TIM向上计数模式
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
		//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	  TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure); 

 /*--------------------输出比较结构体定义-------------------------*/
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                      //选择定时器模式:TIM脉冲宽度调制模式1  （只有PWM1或PWM2）
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;          //比较输出使能        
	  TIM_OCInitStructure.TIM_Pulse = 0;                                     //设置初始脉宽
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;              //输出极性:TIM输出比较极性高
	  PWMB_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //相当于初始化通道
		PWMC_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	  PWMD_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //相当于初始化通道
//		PWMA_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);    /* 因为使用该语句失效，所以使用下面直接寄存器方式 */                   //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	  
		PWM_TIM->CCMR1|=6<<4;         //CH1 PWM1模式	
//		PWM_TIM->CCMR1|=6<<12;        //CH2 PWM1模式	
//		PWM_TIM->CCMR2|=6<<4;         //CH3 PWM1模式	
//		PWM_TIM->CCMR2|=6<<12;        //CH4 PWM1模式	
		
		PWM_TIM->CCER|=1<<0;         //CH1输出使能	
//		PWM_TIM->CCER|=1<<4;         //CH2输出使能	   
//		PWM_TIM->CCER|=1<<8;         //CH3输出使能	 
//		PWM_TIM->CCER|=1<<12;        //CH4输出使能
		
	  PWMA_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //使能 CH1预装载 
	  PWMB_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //使能 CH2预装载	
		PWMC_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //使能 CH1预装载 
	  PWMD_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);   
		
	  TIM_ARRPreloadConfig(PWM_TIM, ENABLE);                                 //使能TIMx在ARR上的预装载寄存器
		TIM_CtrlPWMOutputs(PWM_TIM,ENABLE);//使能TIM8外设的主输出
	  TIM_Cmd(PWM_TIM, ENABLE);                                              //使能TIM1	
		
		
} 

 /****************************************************************************
  * @brief    绝对值函数
  * @param    a
  * @retval   |a|
  * @author   LZM
  * @note      
  */
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
 /****************************************************************************
  * @brief    赋值给PWM寄存器
  * @param    哪一个电机；输出
  * @retval   无
  * @author   LZM
  * @note     此实验最大10000
  */
void Set_Pwm(MOTOR_ID id,int pwm)
{
	  
//	/* 限幅 */
//	if(pwm > Limit_Amplitude)
//		pwm = Limit_Amplitude;
//	else
//		if(pwm < -Limit_Amplitude)
//			pwm =  -Limit_Amplitude;
  
	switch(id)
	{
		case MotorA:
				/* 方向 */
				if(pwm < 0)
					AINA = 0;
				else
					AINA = 1;
				/* 输出pwm */
				PWMA=myabs(pwm);        // 转速大小
				break;
		case MotorB:
				/* 方向 */
				if(pwm < 0)
					AINB = 0;
				else
					AINB = 1;
				/* 输出pwm */
				PWMB=myabs(pwm);        // 转速大小
				break;
		case MotorC:
				/* 方向 */
				if(pwm < 0)
					AINC = 0;
				else
					AINC = 1;
				/* 输出pwm */
				PWMC=myabs(pwm);        // 转速大小
				break;
		case MotorD:
				/* 方向 */
				if(pwm < 0)
					AIND = 0;
				else
					AIND = 1;
				/* 输出pwm */
				PWMD=myabs(pwm);        // 转速大小
				break;
		default:
				break;
	}
	

}




