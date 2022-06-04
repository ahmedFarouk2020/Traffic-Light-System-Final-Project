/*
 * Button.c
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */


unsigned char Button_Request;
extern unsigned char App_PedestrianReq;

void Button_Init(void)
{
    Button_Request = 0;
}

unsigned char Button_GetLevel(unsigned char button_id)
{
    unsigned char button_reading = Adc_GetReading();
    if( (button_level > X)  && (button_level< X) )
    {
        return 1;
    }
    return 0;
}


void Button_MainFunction(void) // 10 ms
{
    static count = 0;
    unsigned char button_level = Button_GetLevel(button_ID);
    if(button_level == 1)
    {
        count = (cout+1)%11;
    }
    if(count == 10)
    {
        Button_Request = 1;
    }
    else
    {
        Button_Request = 0;
    }

}
