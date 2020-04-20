/**
  ******************************************************************************
  * @file    bsp_uart2.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   这里使用接收中断.
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_USART2_H
#define	_BSP_USART2_H


#include "includes.h" 

#define  DEBUG2_SAFETY                   1   /* 1为真，选择安全，0则选择效率 */


#define  DEBUG2_USARTx                   USART2
#define  DEBUG2_USART_CLK                RCC_APB1Periph_USART2
#define  DEBUG2_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG2_USART_BAUDRATE           9600

// USART GPIO 引脚宏定义
#define  DEBUG2_USART_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  DEBUG2_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
   
#define  DEBUG2_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG2_USART_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG2_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG2_USART_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG2_USART_IRQ                USART2_IRQn
#define  DEBUG2_USART_IRQHandler         USART2_IRQHandler

//DMA配置
// 一次发送的数据量
#define  DEBUG2_TX_BSIZE                   50
#define  DEBUG2_RX_BSIZE                   50
#define  DEBUG2_UART_Tx_DMA_Channel        DMA1_Channel7   // 串口对应的DMA请求通道
#define  DEBUG2_UART_Tx_DMA_FLAG           DMA1_FLAG_GL7//DMA1_FLAG_TC2 | DMA1_FLAG_TE2 
#define  DEBUG2_UART_Tx_DMA_IRQ            DMA1_Channel7_IRQn
#define  DEBUG2_UART_Tx_DMA_IRQHandler     DMA1_Channel7_IRQHandler
#define  DEBUG2_UART_Rx_DMA_Channel        DMA1_Channel6   // 串口对应的DMA请求通道
#define  DEBUG2_UART_Rx_DMA_FLAG           DMA1_FLAG_GL6//DMA1_FLAG_TC3 | DMA1_FLAG_TE3 
#define  DEBUG2_UART_Rx_DMA_IRQ            DMA1_Channel6_IRQn
#define  DEBUG2_UART_Rx_DMA_IRQHandler     DMA1_Channel6_IRQHandler


typedef struct class_pms CLASS_Pms;

struct class_pms
{
	u16  PM2_5_Vol;   //pm2.5数值
	u16  PM10_Vol;    //pm10数值
};


void USART2_Config(uint8_t priority);
void Usar2_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usar2_SendString( USART_TypeDef * pUSARTx, char *str);
void Usar2_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

//DMA
void Uart2_Start_DMA_Tx(uint16_t size);
void Uart2_DMA_SendString( char *SendString,short int size);

//PMS
void bsp_PMS_Init(void);


#endif /* __USART_H */
