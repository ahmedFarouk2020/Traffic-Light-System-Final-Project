/*
 * Uart.h
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#ifndef INC_UART_H_
#define INC_UART_H_



/* APIs Declarations */
void USART2_Init(void);

void USART2_Transmit(const char* Str);


void UART_Init(void);

unsigned char UART_RecvSync(unsigned char DeviceId);

void UART_SendSync(unsigned char DeviceId, unsigned char data);

void UART_SendStr(unsigned char DeviceId, char* str);

unsigned char UART_GetStatus(void);

#endif /* INC_UART_H_ */
