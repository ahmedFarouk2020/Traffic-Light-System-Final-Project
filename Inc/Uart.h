/*
 * Uart.h
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#ifndef INC_UART_H_
#define INC_UART_H_



/* APIs Declarations */

void UART_Init(void);

unsigned char UART_RecvAsync(void);

void UART_Send(unsigned char uartId, unsigned char data);

void UART_SendStr(unsigned char uartIdId, char* str);

unsigned char UART_GetStatus(void);



#endif /* INC_UART_H_ */
