/*
 * Uart.c
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#include "Uart.h"
#include "Uart_Cfg.h"
#include "stm32f401xc.h"

#define CLK 16000000U


USART_TypeDef* USARTs[3] = {USART1, USART2, USART6};


void USART2_Init(void) {
//  GPIO_EnableClock(0);
//  GPIO_Init(0, 2, ALTERNATE_FUN, PUSH_PULL);
//
//  GPIOA->AFR[0] &= ~(0xf << 4 * 2);
//  GPIOA->AFR[0] |= 0x7 << 4 * 2;


  RCC->APB1ENR |= 1 << RCC_APB1ENR_USART2EN_Pos;

  USART2->CR1 &= ~(1 << USART_CR1_M_Pos);

  USART2->CR2 &= ~(USART_CR2_STOP);

  USART2->CR1 &= ~(1 << USART_CR1_OVER8_Pos);

  USART2->BRR = 0x683;  // Baud Rate 9600

  /* Enable Transmission block */
  USART2->CR1 |= (1 << USART_CR1_TE_Pos);

  // /* Enable Receive block */
  // USART2->CR1 |= (1 << USART_CR1_RE_Pos);

  /* Enable USART2 */
  USART2->CR1 |= (1 << USART_CR1_UE_Pos);
}




void UART_Init(void)
{
         /* Loop on each device in configuration list */
    int counter;
    for(counter = 0; counter<MAX_NUM_OF_DEVICES; counter++)
    {
        USART_TypeDef* UART = USARTs[ConfigurationList[counter].uart_id];
        /* Enable clk from RCC */
        switch(ConfigurationList[counter].uart_id)
        {
            case 0:
            {
                RCC->APB2ENR = 1<< RCC_APB2ENR_USART1EN_Pos;
            }
            break;
            case 1:
            {
                RCC->APB1ENR = 1<< RCC_APB1ENR_USART2EN_Pos;
            }
            break;
            case 2:
            {
                RCC->APB2ENR = 1<< RCC_APB2ENR_USART6EN_Pos;
            }
            break;
            default:    /* report error */ break;
        }

        /* Baud rate definition */
        float ClkDivider = CLK/(16.0*ConfigurationList[counter].buad_rate);
        unsigned short mantissa = (unsigned short int)ClkDivider;
        unsigned int fraction = (unsigned int)((ClkDivider-(float)mantissa) * 16 + 0.5) ;

        UART->BRR = (mantissa<<4 & 0x0ff0U) |(fraction & (0x0fU));
//        UART->BRR = 0x682;

        /* Word length 8-bytes */
        UART->CR1 &= ~(1<< USART_CR1_M_Pos); /* clear the bit M */
        UART->CR1 |= (ConfigurationList[counter].data_size<< USART_CR1_M_Pos); /* put the value into the bit M */


        /* transmitter enable */
        UART->CR1 |= 1<< USART_CR1_TE_Pos;
        /* receiver enable */
        UART->CR1 |= 1<< USART_CR1_RE_Pos;

        /* Enable UART */
        UART->CR1 |= 1<< USART_CR1_UE_Pos;
    }

}


unsigned char UART_RecvSync(unsigned char DeviceId)
{
    if(DeviceId >= MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef* UART = USARTs[ConfigurationList[DeviceId].uart_id];
        /* Wait until receive buffer is not empty */
        while( !(UART->SR & (1U<< USART_SR_RXNE_Pos)));
        return UART->DR;
    }
    return 0xff; /* Error */
}


void UART_SendSync(unsigned char DeviceId, unsigned char data)
{
    if(DeviceId < MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef* UART = USARTs[ConfigurationList[DeviceId].uart_id];
        UART->DR = data;
        /* Wait until tranfer complete flag is set */
        while( !(UART->SR & (1U<< USART_SR_TC_Pos)));

        /* Clear the flag */
        UART->SR &= ~(1<< USART_SR_TC_Pos);
    }
}


void UART_SendStr(unsigned char DeviceId, char* str)
{
    if(DeviceId < MAX_NUM_OF_DEVICES)
    {
        while(*str != '\0')
        {
            UART_SendSync(DeviceId, *str);
            str++;
        }
    }
    else
    {
        /* Report Error */
    }
}


unsigned char UART_GetStatus(void)
{
    return 1;
}


