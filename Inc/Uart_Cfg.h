/*
 * Uart_Cfg.h
 *
 *  Created on: May 11, 2022
 *      Author: Farouk
 */

#ifndef INC_UART_CFG_H_
#define INC_UART_CFG_H_

#define MAX_NUM_OF_DEVICES 1

/* Buad rate values (options) */
#define _9600
#define _115200

typedef struct {
    unsigned char uart_id;// 0-> uart1  1-> uart2   2->uart6
    unsigned char data_size;// 0:9
    unsigned char buad_rate;// macros

}Uart_Config;


extern const Uart_Config ConfigurationList[MAX_NUM_OF_DEVICES];


#endif /* INC_UART_CFG_H_ */
