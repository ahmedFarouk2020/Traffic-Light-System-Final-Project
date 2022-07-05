/*
 * Uart.c
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

/******* The rest to be completed
 *
 * 1. Test the recieve function
 *
 * 2. Enable interrupts and use them with the code
 *
 */
#include "stm32f401xc.h"
#include "Uart.h"
#include "Uart_Cfg.h"
#include "DIO.h"

#define CLK 16000000U

/* External Variables */
extern unsigned char EVD_DataFrame[3];
extern unsigned char EVD_ReceiveStatus;


static USART_TypeDef* USARTs[3] = {USART1, USART2, USART6};

// Pin2A -> TX , Pin3A -> RX  UART2
// Pin9A -> TX , Pin10A -> RX Bootloader

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

        /* Word length 8-bytes */
        UART->CR1 &= ~(1<< USART_CR1_M_Pos); /* clear the bit M */
        UART->CR1 |= (ConfigurationList[counter].data_size<< USART_CR1_M_Pos); /* put the value into the bit M */

        /* Enable selected interrupts */
        UART->CR1 &= ~(7<<USART_CR1_RXNEIE_Pos); // clear interrupts fields
        UART->CR1 |= ConfigurationList[counter].needed_interrupts.RXNE<< USART_CR1_RXNEIE_Pos;
        UART->CR1 |= ConfigurationList[counter].needed_interrupts.TC<< USART_CR1_TCIE_Pos;
        UART->CR1 |= ConfigurationList[counter].needed_interrupts.TXE<< USART_CR1_TXEIE_Pos;

        /* Uart mode selection */
        switch(ConfigurationList[counter].uart_mode)
        {
            case 0: // Both
            {
                UART->CR1 |= 1<< USART_CR1_TE_Pos;
                UART->CR1 |= 1<< USART_CR1_RE_Pos;
            }
            break;
            case 1: // transmitter
            {
                UART->CR1 |= 1<< USART_CR1_TE_Pos;
                UART->CR1 &= ~(1<< USART_CR1_RE_Pos);
            }
            break;
            case 2: // receiver
            {
                UART->CR1 &= ~(1<< USART_CR1_TE_Pos);
                UART->CR1 |= 1<< USART_CR1_RE_Pos;
            }
            break;
            default: /* Error */ break;
        }

        /* Enable global interrupt flag */
        switch(ConfigurationList[counter].uart_id)
        {
            case 0:
            {
                NVIC_EnableIRQ(USART1_IRQn);
            }
            break;
            case 1:
            {
                NVIC_EnableIRQ(USART2_IRQn);
            }
            break;
            case 2:
            {
                NVIC_EnableIRQ(USART6_IRQn);
            }
            break;
            default: /* Error */ break;
        }

        /* Enable UART */
        UART->CR1 |= 1<< USART_CR1_UE_Pos;
    }

}


unsigned char UART_RecvAsync(unsigned char DeviceId)
{
    if(DeviceId >= MAX_NUM_OF_DEVICES)
    {
        USART_TypeDef* UART = USARTs[ConfigurationList[DeviceId].uart_id];
        return UART->DR;
    }
    return 0xff; /* Error */
}


unsigned char UART_RecvSync(unsigned char DeviceId)
{
    if(DeviceId < MAX_NUM_OF_DEVICES)
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
        UART->DR = (signed char)data;
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



/*
 * We can consider this design for Uart or make the ISR tranfer data to EVD and we only check if 3 frame arrives to inform EVD
 */
//void UART_MainFunction(void) // highest priority
//{
//    while(1)
//    {
//        unsigned char i;
//
//        for(i=0; i<3; i++)
//        {
//            // interrupt set(increment) a flag "Uart_receive" -> wait event
//            // clear event
//            EVD_DataFrame[i] = UART_RecvAsync(0);
//        }
//        EVD_ReceiveStatus = 1; // set event
//        // wait "Event" DataFrame is received
//        EVD_ReceiveStatus = 0;
//    }
//}


//void USART2_IRQHandler(void)
//{
//    static unsigned char i = 0;
//
//    USART2->SR &= ~(1<< USART_SR_RXNE_Pos);
//
//    i = (i + 1)%3;
//
//    if(EVD_ReceiveStatus == 0) {
//
//        EVD_DataFrame[i] = USART2->DR;
//
//        if(i == 0)
//        {
//            EVD_ReceiveStatus = 1;
//        }
//    }
//
//}



