/**
  ******************************************************************************
  * @file    bsp_usart3.h
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
#ifndef _BSP_USART3_H
#define	_BSP_USART3_H


#include "includes.h" 

#define DEBUG3_SAFETY                    1   /* 1Ϊ�棬ѡ��ȫ��0��ѡ��Ч�� */


#define  DEBUG3_USARTx                   USART3
#define  DEBUG3_USART_CLK                RCC_APB1Periph_USART3
#define  DEBUG3_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG3_USART_BAUDRATE           115200

// USART GPIO ���ź궨��
#define  DEBUG3_USART_GPIO_CLK           RCC_APB2Periph_GPIOB
#define  DEBUG3_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG3_USART_TX_GPIO_PORT       GPIOB   
#define  DEBUG3_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG3_USART_RX_GPIO_PORT       GPIOB
#define  DEBUG3_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG3_USART_IRQ                USART3_IRQn
#define  DEBUG3_USART_IRQHandler         USART3_IRQHandler

//DMA����
#define  DEBUG3_UART_Tx_DMA_Channel        DMA1_Channel2   // ���ڶ�Ӧ��DMA����ͨ��
#define  DEBUG3_UART_Tx_DMA_FLAG           DMA1_FLAG_GL2//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 
#define  DEBUG3_UART_Tx_DMA_IRQ            DMA1_Channel2_IRQn
#define  DEBUG3_UART_Tx_DMA_IRQHandler     DMA1_Channel2_IRQHandler
#define  DEBUG3_UART_Rx_DMA_Channel        DMA1_Channel3   // ���ڶ�Ӧ��DMA����ͨ��
#define  DEBUG3_UART_Rx_DMA_FLAG           DMA1_FLAG_GL3//DMA1_FLAG_TC3 | DMA1_FLAG_TE3 
#define  DEBUG3_UART_Rx_DMA_IRQ            DMA1_Channel3_IRQn
#define  DEBUG3_UART_Rx_DMA_IRQHandler     DMA1_Channel3_IRQHandler

// һ�η��͵�������
#define  DEBUG3_TX_BSIZE                   50
#define  DEBUG3_RX_BSIZE                   50






void USART3_Config(uint8_t priority);
void Usar3_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usar3_SendString( USART_TypeDef * pUSARTx, char *str);
void Usar3_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

//DMA
void Uart3_Start_DMA_Tx(uint16_t size);
void Uart3_DMA_SendString( u8 *SendString,short int size);


#endif /* __USART_H */


