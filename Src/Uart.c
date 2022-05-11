/*
 * Uart.c
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#include "Uart.h"
#include "Uart_Cfg.h"
#include "stm32f401xc.h"


USART_TypeDef USARTs[] = {USART1, USART2, USART6};

void UART_Init(void)
{
         /* Loop on each device in configuration list */
    int counter;
    for(counter = 0; counter<MAX_NUM_OF_DEVICES; counter++)
    {
        USART_TypeDef UART = USARTs[ConfigurationList[counter].uart_id];

        /* Enable clk from RCC */
        switch(ConfigurationList[counter].uart_id)
        {
            case 0:
            {
                RCC->APB1ENR = 1<< RCC_APB1ENR_USART2EN_Pos;
            }
            break;
            case 1:
            {
                RCC->APB2ENR = 1<< RCC_APB2ENR_USART1EN_Pos;
            }
            break;
            case 2:
            {
                RCC->APB2ENR = 1<< RCC_APB2ENR_USART6EN_Pos;
            }
            break;
            default:    exit(1); break;
        }

        /* Baud rate definition */
        UART->BRR = 0x683;

        /* Word length 8-bytes */
        UART->CR1 &= ~(1<< USART_CR1_M_Pos);

        /* Enable UART */
        UART->CR1 |= 1<< USART_CR1_UE;

    }

}


unsigned char UART_RecvSync(unsigned char DeviceId)
{
    if(DeviceId >= MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef UART = USARTs[ConfigurationList[DeviceId].uart_id];
        /* Wait until receive buffer is not empty */
        while( !(UART->SR & (1U<< USART_SR_RXNE_Pos)));
        return UART->DR;
    }
    return 0xff;
}


void UART_SendSync(unsigned char DeviceId, unsigned char data)
{
    if(DeviceId >= MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef UART = USARTs[ConfigurationList[DeviceId].uart_id];
        UART->DR = data;
        /* Wait until tranfer complete flag is set */
        while( !(UART->SR & (1U<< USART_SR_TC_Pos)));

        /* Clear the flag */
        UART->SR &= ~(1<< USART_SR_TC_Pos);
    }
}


void UART_SendStr(unsigned char DeviceId, char* str)
{
    if(DeviceId >= MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef UART = USARTs[ConfigurationList[DeviceId].uart_id];
        while(*str != '\0')
        {
            UART_SendSync(DeviceId, *str);
            str++;
        }
    }
    else
    {
        exit(1);
    }
}


unsigned char UART_GetStatus(void)
{

}
