/**
  ******************************************************************************
  * @file    motor.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ����˿ڳ�ʼ���� PWM �������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H
#include "includes.h"	 

//  ������ֲ

/**************************MOTOR�������壬MOTOR��MOTOR********************************/
//                                ��������ת
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

/**************************MOTOR�������壬PWM ��ʱ�� �����ź궨��********************************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������ʹ�ø߼����ƶ�ʱ��TIM1
//��ʱ��
#define            PWM_TIM                   TIM8
#define            PWM_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            PWM_TIM_CLK               RCC_APB2Periph_TIM8


//ע�⣺��ʼ��ʱҪ��ͨ��˳���ʼ����Ԥװ��
// TIM1 ���ͨ��1    //�˿�����PWMAΪ׼
#define            PWM_GPIO_APBxClock_FUN         RCC_APB2PeriphClockCmd
#define            PWM_TIM_CHANNEL_GPIO_CLK       RCC_APB2Periph_GPIOC
#define            PWM_TIM_CHANNEL_PORT           GPIOC
#define            PWMA_TIM_CHANNEL_PIN           GPIO_Pin_6
#define            PWMB_TIM_CHANNEL_PIN           GPIO_Pin_7
#define            PWMC_TIM_CHANNEL_PIN           GPIO_Pin_8
#define            PWMD_TIM_CHANNEL_PIN           GPIO_Pin_9
// ��ʼ��ͨ������
#define            PWMA_TIM_CHANNEL    TIM_OC1Init
#define            PWMB_TIM_CHANNEL    TIM_OC2Init
#define            PWMC_TIM_CHANNEL    TIM_OC3Init
#define            PWMD_TIM_CHANNEL    TIM_OC4Init
//ʹ��ͨ������
#define            PWMA_TIM_CHANNEL_Config    TIM_OC1PreloadConfig
#define            PWMB_TIM_CHANNEL_Config    TIM_OC2PreloadConfig
#define            PWMC_TIM_CHANNEL_Config    TIM_OC3PreloadConfig
#define            PWMD_TIM_CHANNEL_Config    TIM_OC4PreloadConfig


// ռ�ձ�P=CCR/(ARR+1)    //ARR  is  PWM_TIM_PERIOD
#define PWMA   TIM8->CCR1  // PWM���
#define AINA   PBout(12)
#define PWMB   TIM8->CCR2  // PWM���
#define AINB   PBout(13)
#define PWMC   TIM8->CCR3  // PWM���
#define AINC   PBout(14)
#define PWMD   TIM8->CCR4  // PWM���
#define AIND   PBout(15)


/* ɨ��״̬���� */
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
	
	/* ֵ */
	int pwmtar;    /* Ŀ�������pwmֵ */
	int pwmout;    /* ���������pwmֵ */
	int encoderVal;/* ������ֵ */
	
	/* ���� */
//	__IO uint16_t ccr;         /* ccr�Ĵ��� */
	
};
struct class_pid
{
	
	/* ֵ */
	float p;
	float i;
	float d;
	
};



//void MiniBalance_PWM_Init(u16 arr,u16 psc);

void bsp_Motor_Init(u16 arr,u16 psc);
void Set_Pwm(CLASS_Motor *motor);
#endif





