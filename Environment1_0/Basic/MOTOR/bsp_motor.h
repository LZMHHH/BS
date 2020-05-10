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
// 初始化通道函数
#define            PWMA_TIM_CHANNEL    TIM_OC1Init
#define            PWMB_TIM_CHANNEL    TIM_OC2Init
//使能通道函数
#define            PWMA_TIM_CHANNEL_Config    TIM_OC1PreloadConfig
#define            PWMB_TIM_CHANNEL_Config    TIM_OC2PreloadConfig


// 占空比P=CCR/(ARR+1)    //ARR  is  PWM_TIM_PERIOD
#define PWMA   TIM8->CCR1  // PWM输出
#define AINA   PBout(12)
#define PWMB   TIM8->CCR2  // PWM输出
#define AINB   PBout(13)



/* 扫描状态机表 */
typedef enum
{
    enMotorA,      /* M1 */
    enMotorB,      /* M2 */
}MOTOR_status;


typedef struct class_motor CLASS_Motor;
	
struct class_motor
{
	MOTOR_status name;
	
	/* 值 */
	int pwmout;    /* 最终输出的pwm值 */
	
};


//void MiniBalance_PWM_Init(u16 arr,u16 psc);

void bsp_Motor_Init(u16 arr,u16 psc);
void Set_Pwm(CLASS_Motor *motor);
#endif





