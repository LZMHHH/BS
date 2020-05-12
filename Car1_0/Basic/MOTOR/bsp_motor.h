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
#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H
#include "includes.h"	 

//  方便移植

/**************************MOTOR参数定义，MOTOR或MOTOR********************************/
//                                用于正反转
#define             MOTORA_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             MOTORA_GPIO_CLK                        RCC_APB2Periph_GPIOB    
#define             MOTORA_V_PORT                          GPIOB   
#define             MOTORA_V_PIN                           GPIO_Pin_12
#define             MOTORB_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             MOTORB_GPIO_CLK                        RCC_APB2Periph_GPIOB    
#define             MOTORB_V_PORT                          GPIOB   
#define             MOTORB_V_PIN                           GPIO_Pin_13
#define             MOTORC_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             MOTORC_GPIO_CLK                        RCC_APB2Periph_GPIOB    
#define             MOTORC_V_PORT                          GPIOB   
#define             MOTORC_V_PIN                           GPIO_Pin_14
#define             MOTORD_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             MOTORD_GPIO_CLK                        RCC_APB2Periph_GPIOB    
#define             MOTORD_V_PORT                          GPIOB   
#define             MOTORD_V_PIN                           GPIO_Pin_15

/**************************MOTOR参数定义，PWM 定时器 及引脚宏定义********************************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 这里我们使用高级控制定时器TIM1
//定时器
#define            PWM_TIM                   TIM8
#define            PWM_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            PWM_TIM_CLK               RCC_APB2Periph_TIM8


//注意：初始化时要按通道顺序初始化及预装载
// TIM1 输出通道1    //端口先以PWMA为准
#define            PWM_GPIO_APBxClock_FUN         RCC_APB2PeriphClockCmd
#define            PWM_TIM_CHANNEL_GPIO_CLK       RCC_APB2Periph_GPIOC
#define            PWM_TIM_CHANNEL_PORT           GPIOC
#define            PWMA_TIM_CHANNEL_PIN           GPIO_Pin_6
#define            PWMB_TIM_CHANNEL_PIN           GPIO_Pin_7
#define            PWMC_TIM_CHANNEL_PIN           GPIO_Pin_8
#define            PWMD_TIM_CHANNEL_PIN           GPIO_Pin_9
// 初始化通道函数
#define            PWMA_TIM_CHANNEL    TIM_OC1Init
#define            PWMB_TIM_CHANNEL    TIM_OC2Init
#define            PWMC_TIM_CHANNEL    TIM_OC3Init
#define            PWMD_TIM_CHANNEL    TIM_OC4Init
//使能通道函数
#define            PWMA_TIM_CHANNEL_Config    TIM_OC1PreloadConfig
#define            PWMB_TIM_CHANNEL_Config    TIM_OC2PreloadConfig
#define            PWMC_TIM_CHANNEL_Config    TIM_OC3PreloadConfig
#define            PWMD_TIM_CHANNEL_Config    TIM_OC4PreloadConfig


// 占空比P=CCR/(ARR+1)    //ARR  is  PWM_TIM_PERIOD
#define PWMA   TIM8->CCR1  // PWM输出
#define AINA   PBout(12)
#define PWMB   TIM8->CCR2  // PWM输出
#define AINB   PBout(13)
#define PWMC   TIM8->CCR3  // PWM输出
#define AINC   PBout(14)
#define PWMD   TIM8->CCR4  // PWM输出
#define AIND   PBout(15)


/* 扫描状态机表 */
typedef enum
{
    enMotorA,      /* M1 */
    enMotorB,      /* M2 */
    enMotorC,      /* M3 */
		enMotorD,      /* M4 */
}MOTOR_status;


typedef struct class_motor CLASS_Motor;
typedef struct class_pid   CLASS_Pid;	

struct class_motor
{
	MOTOR_status name;
	
	/* 值 */
	int pwmtar;    /* 目标输出的pwm值 */
	int pwmout;    /* 最终输出的pwm值 */
	int encoderVal;/* 编码器值 */
	
	/* 配置 */
//	__IO uint16_t ccr;         /* ccr寄存器 */
	
};
struct class_pid
{
	
	/* 值 */
	float p;
	float i;
	float d;
	
};



//void MiniBalance_PWM_Init(u16 arr,u16 psc);

void bsp_Motor_Init(u16 arr,u16 psc);
void Set_Pwm(CLASS_Motor *motor);
#endif





