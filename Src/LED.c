/*
 * LED.c
 *
 *  Created on: May 20, 2022
 *      Author: Farouk
 */
#include "LED.h"
#include "LED_Cfg.h"
#include "DIO.h"

#define LED_GREEN   0
#define LED_RED     1
#define LED_YELLOW  2

unsigned char Led_Color;


 void Led_TurnOn(unsigned char led_id)
{
    DIO_ChannelWrite(Leds[led_id], 1);
}


 void Led_TurnOff(unsigned char led_id)
{
    DIO_ChannelWrite(Leds[led_id], 0);
}


void Led_Init(void)
{
    Led_Color = 0;
    Led_TurnOff(1);
    Led_TurnOff(2);
    Led_TurnOn(0);
}


void Led_MainFunction(void)
{
    switch(Led_Color)
    {
        case 0: // green
        {
            Led_TurnOff(2);
            Led_TurnOff(1);
            Led_TurnOn(0);
        }
        break;
        case 1: // red
        {
            Led_TurnOff(2);
            Led_TurnOff(0);
            Led_TurnOn(1);
        }
        break;
        case 2: // yellow
        {
            Led_TurnOff(1);
            Led_TurnOff(0);
            Led_TurnOn(2);
        }
        break;

        default: /* Invalid Input */ break;
    }

}

