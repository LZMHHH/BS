/**
  ******************************************************************************
  * @file    bsp_encoder.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ����������.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "bsp_encoder.h"
 
 
/**************************************************************************
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder1_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE1_TIM_APBxClock_FUN(ENCODE1_TIM_CLK, ENABLE);             //ʹ�ܶ�ʱ��3��ʱ��
  ENCODE1_GPIO_APBxClock_FUN(ENCODE1_TIM_A_GPIO_CLK|ENCODE1_TIM_B_GPIO_CLK|RCC_APB2Periph_AFIO , ENABLE);    //ʹ��PB�˿�ʱ��

	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);//����ӳ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//��ֹJTAG���ܣ���PB3��PB4��Ϊ��ͨIO��ʹ��
	
	//  I/O������
  GPIO_InitStructure.GPIO_Pin =  ENCODE1_TIM_A_PIN;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //��������
  GPIO_Init(ENCODE1_TIM_A_PORT, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
  
	//  I/O������
  GPIO_InitStructure.GPIO_Pin =  ENCODE1_TIM_B_PIN;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //��������
  GPIO_Init(ENCODE1_TIM_B_PORT, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
	
	//**************��ʱ��ʱ���ṹ������***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);            //�Ȱ�TIM_TimeBaseInitStruct�е�ÿһ��������ȱʡֵ���� //Fills each TIM_TimeBaseInitStruct member with its default value.
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // Ԥ��Ƶ��    ����Ƶ 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM���ϼ���  
  TIM_TimeBaseInit(ENCODE1_TIM, &TIM_TimeBaseStructure);      //��ʼ����ʱ��
	
	//Ӳ���������ӿ�   ����A/B��������������    ���˸߼���ʱ�����⣬������ʱ���ĵı������ӿ�ֻ����channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
	
	//���벶������                                       //��Ϊ�õ��������ӿں����Ͷ���Ĭ�����ú�����������
  TIM_ICStructInit(&TIM_ICInitStructure);             //�Ȱ�TIM_ICInitStructure�е�ÿһ��������ȱʡֵ����
  TIM_ICInitStructure.TIM_ICFilter = 10;              //���벶�������
  TIM_ICInit(ENCODE1_TIM, &TIM_ICInitStructure);      //��ʼ����Χ�豸
  TIM_ClearFlag(ENCODE1_TIM, TIM_FLAG_Update);        //���TIM�ĸ��±�־λ
  TIM_ITConfig(ENCODE1_TIM, TIM_IT_Update, ENABLE);   //�����ж�
	
  //Reset counter
  TIM_SetCounter(ENCODE1_TIM,0);
  TIM_Cmd(ENCODE1_TIM, ENABLE); 
}
/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder2_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE2_TIM_CLK, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  ENCODE2_GPIO_APBxClock_FUN(ENCODE2_TIM_A_GPIO_CLK, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = ENCODE2_TIM_A_PIN|ENCODE2_TIM_B_PIN;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //��������
  GPIO_Init(ENCODE2_TIM_A_PORT, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
	//**************��ʱ��ʱ���ṹ������***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //�Ȱ�TIM_TimeBaseInitStruct�е�ÿһ��������ȱʡֵ���� 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM���ϼ���  
  TIM_TimeBaseInit(ENCODE2_TIM, &TIM_TimeBaseStructure);          //��ʼ����ʱ��
	
	//Ӳ���������ӿ�   ����A/B��������������    ���˸߼���ʱ�����⣬������ʱ���ĵı������ӿ�ֻ����channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  
	//���벶������                                                   //��Ϊ�õ��������ӿں����Ͷ���Ĭ�����ú�����������
	TIM_ICStructInit(&TIM_ICInitStructure);                         //�Ȱ�TIM_ICInitStructure�е�ÿһ��������ȱʡֵ����
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //���벶�������
  TIM_ICInit(ENCODE2_TIM, &TIM_ICInitStructure);                  //��ʼ����Χ�豸
  TIM_ClearFlag(ENCODE2_TIM, TIM_FLAG_Update);                    //���TIM�ĸ��±�־λ
  TIM_ITConfig(ENCODE2_TIM, TIM_IT_Update, ENABLE);               //�����ж�
	
  //Reset counter
  TIM_SetCounter(ENCODE2_TIM,0);
  TIM_Cmd(ENCODE2_TIM, ENABLE); 
}
/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder3_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE3_TIM_CLK, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  ENCODE2_GPIO_APBxClock_FUN(ENCODE3_TIM_A_GPIO_CLK, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = ENCODE3_TIM_A_PIN|ENCODE3_TIM_B_PIN;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //��������
  GPIO_Init(ENCODE2_TIM_A_PORT, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
	//**************��ʱ��ʱ���ṹ������***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //�Ȱ�TIM_TimeBaseInitStruct�е�ÿһ��������ȱʡֵ���� 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM���ϼ���  
  TIM_TimeBaseInit(ENCODE3_TIM, &TIM_TimeBaseStructure);          //��ʼ����ʱ��
	
	//Ӳ���������ӿ�   ����A/B��������������    ���˸߼���ʱ�����⣬������ʱ���ĵı������ӿ�ֻ����channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE3_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  
	//���벶������                                                   //��Ϊ�õ��������ӿں����Ͷ���Ĭ�����ú�����������
	TIM_ICStructInit(&TIM_ICInitStructure);                         //�Ȱ�TIM_ICInitStructure�е�ÿһ��������ȱʡֵ����
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //���벶�������
  TIM_ICInit(ENCODE3_TIM, &TIM_ICInitStructure);                  //��ʼ����Χ�豸
  TIM_ClearFlag(ENCODE3_TIM, TIM_FLAG_Update);                    //���TIM�ĸ��±�־λ
  TIM_ITConfig(ENCODE3_TIM, TIM_IT_Update, ENABLE);               //�����ж�
	
  //Reset counter
  TIM_SetCounter(ENCODE3_TIM,0);
  TIM_Cmd(ENCODE3_TIM, ENABLE); 
}

/**************************************************************************
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder4_Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef       TIM_ICInitStructure;  
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  ENCODE2_TIM_APBxClock_FUN(ENCODE4_TIM_CLK, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  ENCODE2_GPIO_APBxClock_FUN(ENCODE4_TIM_A_GPIO_CLK, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = ENCODE4_TIM_A_PIN|ENCODE4_TIM_B_PIN;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;              //��������
  GPIO_Init(ENCODE4_TIM_A_PORT, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
	//**************��ʱ��ʱ���ṹ������***********************
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                    //�Ȱ�TIM_TimeBaseInitStruct�е�ÿһ��������ȱʡֵ���� 
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                      // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;          //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     ////TIM���ϼ���  
  TIM_TimeBaseInit(ENCODE4_TIM, &TIM_TimeBaseStructure);          //��ʼ����ʱ��
	
	//Ӳ���������ӿ�   ����A/B��������������    ���˸߼���ʱ�����⣬������ʱ���ĵı������ӿ�ֻ����channel 1/2
  TIM_EncoderInterfaceConfig(ENCODE4_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  
	//���벶������                                                   //��Ϊ�õ��������ӿں����Ͷ���Ĭ�����ú�����������
	TIM_ICStructInit(&TIM_ICInitStructure);                         //�Ȱ�TIM_ICInitStructure�е�ÿһ��������ȱʡֵ����
  TIM_ICInitStructure.TIM_ICFilter = 10;                          //���벶�������
  TIM_ICInit(ENCODE4_TIM, &TIM_ICInitStructure);                  //��ʼ����Χ�豸
  TIM_ClearFlag(ENCODE4_TIM, TIM_FLAG_Update);                    //���TIM�ĸ��±�־λ
  TIM_ITConfig(ENCODE4_TIM, TIM_IT_Update, ENABLE);               //�����ж�
	
  //Reset counter
  TIM_SetCounter(ENCODE4_TIM,0);
  TIM_Cmd(ENCODE4_TIM, ENABLE); 
}

/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 1:  Encoder_TIM= (short)ENCODE1_TIM -> CNT;  ENCODE1_TIM -> CNT=0;break;
		 case 2:  Encoder_TIM= (short)ENCODE2_TIM -> CNT;  ENCODE2_TIM -> CNT=0;break;	  
		 case 3:  Encoder_TIM= (short)ENCODE3_TIM -> CNT;  ENCODE3_TIM -> CNT=0;break;	  //������  
		 case 4:  Encoder_TIM= (short)ENCODE4_TIM -> CNT;  ENCODE4_TIM -> CNT=0;break;	  //������  
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/**************************************************************************
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
 note  �� �̼���
**************************************************************************/
void ENCODE2_TIM_INT_FUN(void)
{ 		    		  			  
	//�����봥����һ�������¼Ĵ�����ֵ��������������ʼʲô�Ĵ���������ѡ����
	if(TIM_GetITStatus( ENCODE2_TIM, TIM_IT_Update) != RESET )  //���һ���Ƚ�ͨ������
	{    				   				     	    	
	}				   
	TIM_ClearITPendingBit( ENCODE2_TIM, TIM_IT_Update );//����жϱ�־λ 	    
}
/**************************************************************************
�������ܣ�TIM3�жϷ�����
��ڲ�������
����  ֵ����
note  �� �Ĵ���
**************************************************************************/
void ENCODE1_TIM_INT_FUN(void)
{ 		    		  			    
	if(ENCODE1_TIM->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	ENCODE1_TIM->SR&=~(1<<0);//����жϱ�־λ 	    
}

