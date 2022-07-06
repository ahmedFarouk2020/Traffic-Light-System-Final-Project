/*
 * Button.c
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */
#include "Button.h"
#include "DIO.h"
#include "Adc.h"


#define IS_IN_PRESSED_REGION(reading)  ((reading) < 2200)

extern unsigned char App_ButtonRequest;


unsigned char Button_GetLevel(void)
{
    unsigned int digital_reading = ADC_GetReading();

    if(  IS_IN_PRESSED_REGION(digital_reading) )
    {
        return 1;
    }
    return 0;
}


void Button_MainFunction(void) // 10 ms
{
    static unsigned char count = 0;
    unsigned char button_reading = Button_GetLevel();
    if(button_reading == 1)
    {
        count = (count<10)? (count+1) : 10;
    }
    else
    {
        count = 0;
    }

    if(count == 10)
    {
        App_ButtonRequest = 1; // higher priority task (no protection needed)
    }
    else
    {
        App_ButtonRequest = App_ButtonRequest | 0; // higher priority task (no protection needed)
    }
    DIO_ChannelWrite(15,button_reading);

}
