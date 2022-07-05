/*
 * SSD.h
 *
 *  Created on: May 23, 2022
 *      Author: Farouk
 */

#ifndef INC_SSD_H_
#define INC_SSD_H_


#define COMMON_ANODE 0
#define COMMON_CATHOD 1

#define SSD_TYPE  COMMON_ANODE

#if SSD_TYPE == COMMON_CATHOD
    #define ZERO     0b00111111
    #define ONE      0b00110000
    #define TWO      0b01011011
    #define THREE    0b01001111
    #define FOUR     0b01100110
    #define FIVE     0b01101101
    #define SIX      0b01111101
    #define SEVEN    0b00000111
    #define EIGHT    0b01111111
    #define NINE     0b01101111
    #define DISABLE_SSD  255
#elif SSD_TYPE == COMMON_ANODE
    #define ZERO     ~0b00111111
    #define ONE      ~0b00110000
    #define TWO      ~0b01011011
    #define THREE    ~0b01001111
    #define FOUR     ~0b01100110
    #define FIVE     ~0b01101101
    #define SIX      ~0b01111101
    #define SEVEN    ~0b00000111
    #define EIGHT    ~0b01111111
    #define NINE     ~0b01101111
    #define DISABLE_SSD  ~255
#else
    #error "Enter SSD type";
#endif


void SSD_Init(void);

void SSD_Write(unsigned char display_id, unsigned char data);

void SSD_Display(unsigned char number);

void SSD_MainFunction();

#endif /* INC_SSD_H_ */
