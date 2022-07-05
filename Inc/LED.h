/*
 * LED.h
 *
 *  Created on: May 20, 2022
 *      Author: Farouk
 */

#ifndef INC_LED_H_
#define INC_LED_H_


extern unsigned char Led_Color;

/* Led Colours */
#define LED_GREEN   0
#define LED_YELLOW  1
#define LED_RED     2


/* Function prototypes */
void Led_Init(void);
void Led_MainFunction(void);

void Led_TurnOff(unsigned char led_id);
void Led_TurnOn(unsigned char led_id);
#endif /* INC_LED_H_ */
