#include "DIO.h"
#include "LED.h"
#include "SSD.h"

int main()
{
    DIO_Init();
    SSD_Init();

    while(1)
    {
        SSD_MainFunction();
    }
    return 0;
}

