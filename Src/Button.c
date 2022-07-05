/*
 * Button.c
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */
#include "Button.h"
#include "DIO.h"
#include "Adc.h"

extern unsigned char Button_Request;
//extern void vTaskSuspendAll(void);
//extern void xTaskResumeAll(void);

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

void Button_Init(void)
{
    Button_Request = 0;
}

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

    if( digital_reading < 2200 )
    {
        return 1;
    }
    return 0;
}


//unsigned char Button_GetLevel(unsigned char button_id)
//{
////    unsigned char button_reading = Adc_GetReading();
//    unsigned char button_reading;
//    if( button_reading > 1000 )
//    {
//        return 1;
//    }
//    return 0;
//}


//void Button_MainFunction(void) // 10 ms
//{
//    static unsigned char count = 0;
//
//
//    unsigned char button_level = Button_GetLevel(0);
//
//    if(button_level == 1)
//    {
//        if(count == 10) {}
//        else
//        {
//            count = (count+1)%11;
//        }
//    }
//    else
//    {
//        count = 0;
//    }
//
//    if(count == 10)
//    {
//        Button_Request = 1;
//    }
//    else
//    {
//        Button_Request = 0;
//    }
//
//}

void Button_MainFunction(void) // 10 ms
{
    unsigned char button_reading = Button_GetLevel();
    if(button_reading == 1)
    {
        Button_Request = 1;
    }
    else
    {
        Button_Request = Button_Request | 0;
    }
    DIO_ChannelWrite(15,button_reading);

}
