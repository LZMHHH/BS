/**
  ******************************************************************************
  * @file    bsp_uart2.c
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ����ʹ�ý����ж�.
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "bsp_usart2.h"

static uint8_t SendBuff[DEBUG2_TX_BSIZE];
static uint8_t ReadBuff[DEBUG2_RX_BSIZE];

//����
void UART2_DMA_Config(void);

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(uint8_t priority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG2_UART_Tx_DMA_IRQ;   // ����DMAͨ�����ж����� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x07;      // ���ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG2_USART_IRQ;         //�����ж�����
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������   //DMA��
  * @param  ��
  * @retval ��
  */
void UART2_Config(uint8_t priority)
{
	GPIO_InitTypeDef GPIO_InitStructurex;
	USART_InitTypeDef USART_InitStructurex;
	
	
	// �򿪴���GPIO��ʱ��
	DEBUG2_USART_GPIO_APBxClkCmd(DEBUG2_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG2_USART_APBxClkCmd(DEBUG2_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructurex.GPIO_Pin = DEBUG2_USART_TX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructurex.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG2_USART_TX_GPIO_PORT, &GPIO_InitStructurex);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructurex.GPIO_Pin = DEBUG2_USART_RX_GPIO_PIN;
	GPIO_InitStructurex.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG2_USART_RX_GPIO_PORT, &GPIO_InitStructurex);
	
	//�ж����ȼ�����
	NVIC_Configuration(priority);
	 // ���� DMA ����
	UART2_DMA_Config();  
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructurex.USART_BaudRate = DEBUG2_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructurex.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructurex.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructurex.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructurex.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructurex.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG2_USARTx, &USART_InitStructurex);
	
	
	
	// ʹ�ܴ��ڽ����жϣ�����������ģ�
	//USART_ITConfig(DEBUG2_USARTx, USART_IT_RXNE, ENABLE);	
	// ʹ�ܴ��ڿ����ж�
	USART_ITConfig(DEBUG2_USARTx, USART_IT_IDLE, ENABLE);
	// ʹ�ܴ���
	USART_Cmd(DEBUG2_USARTx, ENABLE);		
	// ����DMA
	USART_DMACmd(DEBUG2_USARTx, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(DEBUG2_USARTx, USART_DMAReq_Rx, ENABLE);


	
  // ���������ɱ�־
	//USART_ClearFlag(USART3, USART_FLAG_TC);     
}

/**
  * @brief  USARTx TX DMA ���ã��ڴ浽����(UART2->DR)
  * @param  ��
  * @retval ��
  */
void UART2_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	  //////////////   TX    /////////////
	  // �ر�DMA
		DMA_Cmd (DEBUG2_UART_Tx_DMA_Channel,DISABLE);
	  // �ָ�ȱʡֵ
	  DMA_DeInit(DEBUG2_UART_Tx_DMA_Channel);  
	  // ���ô��ڷ������ݼĴ���	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG2_USARTx->DR);
	  // ���÷��ͻ������׵�ַ
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff; 
    // ��������λĿ�꣬�ڴ滺���� ->����Ĵ���  
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;      
    // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ	
    DMA_InitStructure.DMA_BufferSize = DEBUG2_TX_BSIZE;      
    // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // �ڴ滺������ַ���ӵ���
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // �������ݿ��8λ��1���ֽ�	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// �ڴ����ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// ���δ���ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // ���ȼ�����		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // �ر��ڴ浽�ڴ��DMAģʽ		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // д������		
    DMA_Init(DEBUG2_UART_Tx_DMA_Channel, &DMA_InitStructure);
    // ���DMA���б�־		
    DMA_ClearFlag(DEBUG2_UART_Tx_DMA_FLAG);       
    // �ر�DMA		
    DMA_Cmd(DEBUG2_UART_Tx_DMA_Channel, DISABLE); 
		// ��������DMAͨ���ж�
    DMA_ITConfig(DEBUG2_UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);  


    /////////////////  RX   //////////////
    // �ر�DMA
		DMA_Cmd (DEBUG2_UART_Rx_DMA_Channel,DISABLE);
	  // �ָ�ȱʡֵ
	  DMA_DeInit(DEBUG2_UART_Rx_DMA_Channel);  
	  // ���ô��ڷ������ݼĴ���	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&DEBUG2_USARTx->DR);
	  // ���÷��ͻ������׵�ַ
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ReadBuff; 
    // ��������λĿ�꣬����Ĵ���->�ڴ滺����   
	  DMA_InitStructure.DMA_DIR =  DMA_DIR_PeripheralSRC;      
    // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ	
    DMA_InitStructure.DMA_BufferSize = DEBUG2_RX_BSIZE;      
    // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        
	  // �ڴ滺������ַ���ӵ���
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;             
    // �������ݿ��8λ��1���ֽ�	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
		// �ڴ����ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        
		// ���δ���ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
    // ���ȼ�����		
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;      
    // �ر��ڴ浽�ڴ��DMAģʽ		
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        
    // д������		
    DMA_Init(DEBUG2_UART_Rx_DMA_Channel, &DMA_InitStructure);
    // ���DMA���б�־		
    DMA_ClearFlag(DEBUG2_UART_Rx_DMA_FLAG);    
		
    // ��������DMAͨ�����ȴ���������  		
    DMA_Cmd(DEBUG2_UART_Rx_DMA_Channel, ENABLE);                                 

	
}

//DMA----------
volatile static u8 uart2_sending = 0;
//��ʼ����
void Uart2_Start_DMA_Tx(uint16_t size)
{	
	  uart2_sending = 1;     //������
   	// ����Ҫ���͵��ֽ���Ŀ
    DEBUG2_UART_Tx_DMA_Channel->CNDTR = (uint16_t)size; 
	  //��ʼDMA����
    DMA_Cmd(DEBUG2_UART_Tx_DMA_Channel, ENABLE);        
}
//��������ж�
void DEBUG2_UART_Tx_DMA_IRQHandler(void)
{
    if(DMA_GetITStatus(DEBUG2_UART_Tx_DMA_FLAG))
    {
			  uart2_sending = 0;     //����
        DMA_ClearFlag(DEBUG2_UART_Tx_DMA_FLAG);         // �����־
			  DMA_Cmd(DEBUG2_UART_Tx_DMA_Channel, DISABLE);   // �ر�DMAͨ��   
        
    }
}
//����  //�ж�   //�����Э��д
void DEBUG2_USART_IRQHandler(void)
{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	  static u8 num = 0;   //��ϵ�����ٸ� 20 �ֽ�  
	  static u8 index = 0;   //���ֽ�ʱ ǰ����ֽ��ܺ�
	
    if(USART_GetITStatus(DEBUG2_USARTx, USART_IT_IDLE) != RESET)  // �����ж�
    {
			  USART_ClearITPendingBit( DEBUG2_USARTx, USART_IT_IDLE );  //��������ж�
			  USART_ReceiveData(DEBUG2_USARTx); //��DR,ֻ�ж���һ�Σ��������������־
			  USART_ClearFlag( DEBUG2_USARTx, USART_FLAG_IDLE );  //��SR��ʵ���������־
			
			  DMA_Cmd(DEBUG2_UART_Rx_DMA_Channel, DISABLE);       // �ر�DMA ����ֹ����
			  DMA_ClearFlag( DEBUG2_UART_Rx_DMA_FLAG );           // ��DMA��־λ
			  num = DEBUG2_RX_BSIZE - DMA_GetCurrDataCounter(DEBUG2_UART_Rx_DMA_Channel); //��ý��յ����ֽ���
			  DEBUG2_UART_Rx_DMA_Channel->CNDTR = DEBUG2_RX_BSIZE;    //  ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
			  

			  //Flage_StateRx = State_RTno;     //�������
			  //�����������˼�Ǵ������걾�������ٿ�������
			  //DMA_Cmd(DEBUG2_UART_Rx_DMA_Channel, ENABLE);        //DMA �������ȴ����ݡ�ע�⣬����жϷ�������֡�����ʺܿ죬MCU����������˴ν��յ������ݣ��ж��ַ������ݵĻ������ﲻ�ܿ������������ݻᱻ���ǡ���2�ַ�ʽ�����
			
#if DEBUG2_SAFETY
				xQueueSendFromISR(  xQueue_uart2Rx,               /* ��Ϣ���еľ�� */
                    (void *)ReadBuff,                   /* ���͵���Ϣ���� */
                            &xHigherPriorityTaskWoken); /* �����ȼ������Ƿ񱻻��ѵ�״̬���� */

#else
				xQueueSendFromISR(  xQueue_uart2Rx,               /* ��Ϣ���еľ�� */
				            (void *)&ReadBuff,                    /* ���͵���Ϣ���� �����ַ����ĵ�ַ*/
                            &xHigherPriorityTaskWoken);   /* �����ȼ������Ƿ񱻻��ѵ�״̬���� */

#endif
										
				memset(ReadBuff, 0x00, num+1);  

				DEBUG2_UART_Rx_DMA_Channel->CMAR  = (uint32_t)ReadBuff; 					
				DMA_Cmd(DEBUG2_UART_Rx_DMA_Channel, ENABLE);

				
        USART_ReceiveData( DEBUG2_USARTx ); // Clear IDLE interrupt flag bit
    }
		
		//����и����ȼ�����Ҫ�л������л�
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/* �������ݣ��ٴο��������Ż��� 
		sizeΪ-1�����Զ����㳤��
*/
void Uart2_DMA_SendString( char *SendString,short int size)
{
	if(size < 0)
	{
		size = strlen(SendString);
	}
	
//	while(DMA_GetFlagStatus(DEBUG2_UART_Tx_DMA_FLAG) == RESET){;}
		while(uart2_sending);
	

	 *(SendBuff + size + 1) = '\0';
	 memcpy(SendBuff, SendString, size);
	 
 
	 Uart2_Start_DMA_Tx(size);
}


/*
	PMS ����
*/
void bsp_PMS_Init(void)
{
	UART2_Config(7);                     //=====��ʼ������
}


