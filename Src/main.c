#include "DIO.h"
#include "LED.h"
#include "SSD.h"

int main()
{
    DIO_Init();
//    Led_Init();
    SSD_Init();
        SSD_MainFunction();

    while(1)
    {
//        Led_Color = 0;
//        Led_MainFunction();
//        DIO_ChannelWrite(5, 1);
    }
    return 0;
}

