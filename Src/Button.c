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



//void Get_ButtonReq(unsigned char *value) {
//    vTaskSuspendAll();
//    *value = Button_Request;
//    xTaskResumeAll();
//}
//
//void Set_ButtonReq(void) {
//    vTaskSuspendAll();
//    Button_Request = 1;
//    xTaskResumeAll();
//}


//unsigned char Button_GetLevel(void)
//{
//    int button_reading;
//    DIO_ChannelRead(12, (unsigned short int*)&button_reading);
//
//    if( button_reading == 0 ) // active low
//    {
//        return 1;
//    }
//    return 0;
//}

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
