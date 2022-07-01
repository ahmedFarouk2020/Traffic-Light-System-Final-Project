#include "Button.h"
#include "ADC.h"

unsigned char Button_Request;
extern unsigned char App_PedestrianReq;

void Button_Init(void)
{
    Button_Request = 0;
}

unsigned char Button_GetLevel(void)
{
    unsigned int digital_reading = ADC_GetReading();
//    float analog_value = digital_reading * (5 / 4096) ;

    if( digital_reading < 2048 )
    {
        return 1;
    }
    return 0;
}


void Button_MainFunction(void) // 10 ms
{
    static int count = 0;
    unsigned char button_level = Button_GetLevel();
    if(button_level == 1)
	{
		count = (count+1) % 11 ;
	}
    else
    {
    	count = 0 ;
    }
    if(count == 10)
    {
        Button_Request = 1;
    }
    else
    {

    }

}





