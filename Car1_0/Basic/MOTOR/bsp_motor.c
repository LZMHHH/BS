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
#include "bsp_motor.h"




/**  �̼���
  * @brief  ��� I/O����   
  * @param  ��
  * @retval ��������ת
  */
void MOTOR_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

/*********** �������� **************/
	
	/* ʹ���� MOTORA �йص�ʱ�� */
	MOTORA_GPIO_APBxClock_FUN(MOTORA_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORA_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // ������� 
  GPIO_Init(MOTORA_V_PORT, &GPIO_InitStructure);
	
	/* ʹ���� MOTORB �йص�ʱ�� */
	MOTORA_GPIO_APBxClock_FUN(MOTORB_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORB_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // ������� 
  GPIO_Init(MOTORB_V_PORT, &GPIO_InitStructure);
	
	/* ʹ���� MOTORC �йص�ʱ�� */
	MOTORA_GPIO_APBxClock_FUN(MOTORC_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORC_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // ������� 
  GPIO_Init(MOTORC_V_PORT, &GPIO_InitStructure);
	
	/* ʹ���� MOTORD �йص�ʱ�� */
	MOTORA_GPIO_APBxClock_FUN(MOTORD_GPIO_CLK, ENABLE);	 
  /* R_V_G*/
  GPIO_InitStructure.GPIO_Pin = MOTORD_V_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // ������� 
  GPIO_Init(MOTORD_V_PORT, &GPIO_InitStructure);
	
	
/*********** pwm���� **************/
	PWM_GPIO_APBxClock_FUN(PWM_TIM_CHANNEL_GPIO_CLK , ENABLE);   // ʹ��GPIO����ʱ��ʹ��
	
	//  PWM������ų�ʼ��  �����ź�
	//���ø�����Ϊ�����������,���TIM1 CH2 CH3 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = PWMA_TIM_CHANNEL_PIN|PWMB_TIM_CHANNEL_PIN|PWMC_TIM_CHANNEL_PIN|PWMD_TIM_CHANNEL_PIN; //TIM_CH3 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_TIM_CHANNEL_PORT, &GPIO_InitStructure);

}

/**  �̼���
  * @brief  ���  ��ʱ�� PWM ����     
  * @param  arr   ��PWMƵ��=72M/��arr+1���� psc ����Ƶ
  * @retval ����PWM����
  */
void bsp_Motor_Init(u16 arr,u16 psc)    
{		 		
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;      //TIM Time Base Init structure definition
	  TIM_OCInitTypeDef        TIM_OCInitStructure;      // TIM Output Compare Init structure definition 
	
    MOTOR_GPIO_Init();	    //  PWM  ���I/O�ڳ�ʼ��
	
	
	  PWM_TIM_APBxClock_FUN(PWM_TIM_CLK, ENABLE);      // ��ʱ��ʱ�ӳ�ʼ��
 	  	
	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж� 
	  TIM_TimeBaseStructure.TIM_Period = arr; 
	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ��CNT��������ʱ�� = Fck_int/(psc+1)
	  TIM_TimeBaseStructure.TIM_Prescaler =psc; 
		//����ʱ�ӷָ�:TDTS = Tck_tim����������ʱ��ʱ��Ҫ�õ�
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
		//TIM���ϼ���ģʽ
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
		//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	  TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure); 

 /*--------------------����ȽϽṹ�嶨��-------------------------*/
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                      //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  ��ֻ��PWM1��PWM2��
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;          //�Ƚ����ʹ��        
	  TIM_OCInitStructure.TIM_Pulse = 0;                                     //���ó�ʼ����
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;              //�������:TIM����Ƚϼ��Ը�
	  PWMB_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //�൱�ڳ�ʼ��ͨ��
		PWMC_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	  PWMD_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);                       //�൱�ڳ�ʼ��ͨ��
//		PWMA_TIM_CHANNEL(PWM_TIM, &TIM_OCInitStructure);    /* ��Ϊʹ�ø����ʧЧ������ʹ������ֱ�ӼĴ�����ʽ */                   //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	  
		PWM_TIM->CCMR1|=6<<4;         //CH1 PWM1ģʽ	
//		PWM_TIM->CCMR1|=6<<12;        //CH2 PWM1ģʽ	
//		PWM_TIM->CCMR2|=6<<4;         //CH3 PWM1ģʽ	
//		PWM_TIM->CCMR2|=6<<12;        //CH4 PWM1ģʽ	
		
		PWM_TIM->CCER|=1<<0;         //CH1���ʹ��	
//		PWM_TIM->CCER|=1<<4;         //CH2���ʹ��	   
//		PWM_TIM->CCER|=1<<8;         //CH3���ʹ��	 
//		PWM_TIM->CCER|=1<<12;        //CH4���ʹ��
		
	  PWMA_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //ʹ�� CH1Ԥװ�� 
	  PWMB_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //ʹ�� CH2Ԥװ��	
		PWMC_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);                //ʹ�� CH1Ԥװ�� 
	  PWMD_TIM_CHANNEL_Config(PWM_TIM, TIM_OCPreload_Enable);   
		
	  TIM_ARRPreloadConfig(PWM_TIM, ENABLE);                                 //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
		TIM_CtrlPWMOutputs(PWM_TIM,ENABLE);//ʹ��TIM8����������
	  TIM_Cmd(PWM_TIM, ENABLE);                                              //ʹ��TIM1	
		
		
} 

 /****************************************************************************
  * @brief    ����ֵ����
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
  * @brief    ��ֵ��PWM�Ĵ���
  * @param    ��һ����������
  * @retval   ��
  * @author   LZM
  * @note     ��ʵ�����10000
  */
void Set_Pwm(MOTOR_ID id,int pwm)
{
	  
//	/* �޷� */
//	if(pwm > Limit_Amplitude)
//		pwm = Limit_Amplitude;
//	else
//		if(pwm < -Limit_Amplitude)
//			pwm =  -Limit_Amplitude;
  
	switch(id)
	{
		case MotorA:
				/* ���� */
				if(pwm < 0)
					AINA = 0;
				else
					AINA = 1;
				/* ���pwm */
				PWMA=myabs(pwm);        // ת�ٴ�С
				break;
		case MotorB:
				/* ���� */
				if(pwm < 0)
					AINB = 0;
				else
					AINB = 1;
				/* ���pwm */
				PWMB=myabs(pwm);        // ת�ٴ�С
				break;
		case MotorC:
				/* ���� */
				if(pwm < 0)
					AINC = 0;
				else
					AINC = 1;
				/* ���pwm */
				PWMC=myabs(pwm);        // ת�ٴ�С
				break;
		case MotorD:
				/* ���� */
				if(pwm < 0)
					AIND = 0;
				else
					AIND = 1;
				/* ���pwm */
				PWMD=myabs(pwm);        // ת�ٴ�С
				break;
		default:
				break;
	}
	

}




