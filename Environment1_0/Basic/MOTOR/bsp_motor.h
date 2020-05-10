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
// ��ʼ��ͨ������
#define            PWMA_TIM_CHANNEL    TIM_OC1Init
#define            PWMB_TIM_CHANNEL    TIM_OC2Init
//ʹ��ͨ������
#define            PWMA_TIM_CHANNEL_Config    TIM_OC1PreloadConfig
#define            PWMB_TIM_CHANNEL_Config    TIM_OC2PreloadConfig


// ռ�ձ�P=CCR/(ARR+1)    //ARR  is  PWM_TIM_PERIOD
#define PWMA   TIM8->CCR1  // PWM���
#define AINA   PBout(12)
#define PWMB   TIM8->CCR2  // PWM���
#define AINB   PBout(13)



/* ɨ��״̬���� */
typedef enum
{
    enMotorA,      /* M1 */
    enMotorB,      /* M2 */
}MOTOR_status;


typedef struct class_motor CLASS_Motor;
	
struct class_motor
{
	MOTOR_status name;
	
	/* ֵ */
	int pwmout;    /* ���������pwmֵ */
	
};


//void MiniBalance_PWM_Init(u16 arr,u16 psc);

void bsp_Motor_Init(u16 arr,u16 psc);
void Set_Pwm(CLASS_Motor *motor);
#endif





