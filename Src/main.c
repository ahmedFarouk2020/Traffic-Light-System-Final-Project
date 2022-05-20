#include "DIO.h"
#include "LED.h"

int main()
{
    DIO_Init();
    Led_Init();

    while(1)
    {
        Led_Color = 0;
        Led_MainFunction();
    }
    return 0;
}

