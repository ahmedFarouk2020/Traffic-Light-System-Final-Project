/*
 * Uart_Cfg.h
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#ifndef INC_UART_CFG_H_
#define INC_UART_CFG_H_

#define MAX_NUM_OF_DEVICES 1



/* Data word size */
#define _8BITS     0
#define _9BITS     1

typedef struct {
    unsigned char uart_id;// 0-> uart1  1-> uart2   2->uart6
    unsigned char data_size;// _8BITS, _9BITS
    unsigned int buad_rate;// 9600  115200

}Uart_Config;


extern const Uart_Config ConfigurationList[MAX_NUM_OF_DEVICES];


#endif /* INC_UART_CFG_H_ */
