/*
 * SSD.c
 *
 *  Created on: May 23, 2022
 *      Author: Farouk
 */

#include "DIO.h"
#include "DIO_Cfg.h"
#include "SSD.h"

#define SSD_DISABLE   10

unsigned char SSD_Data; // value of timer
static unsigned char SSD_ActiveDisplay; // id of the active display



void SSD_Init(void)
{
    SSD_Data = 60;
    SSD_ActiveDisplay = 0;
}


void SSD_Write(unsigned char display_id, unsigned char data)
{
    switch(data)
    {
        case 0:
        {
            DIO_ChannelGroupWrite(display_id, 0b00111111);
        }
        break;

        case 1:
        {
            DIO_ChannelGroupWrite(display_id, 0b00110000);
        }
        break;

        case 2:
        {
            DIO_ChannelGroupWrite(display_id, 0b01011011);
        }
        break;

        case 3:
        {
            DIO_ChannelGroupWrite(display_id, 0b01001111);
        }
        break;

        case 4:
        {
            DIO_ChannelGroupWrite(display_id, 0b01100110);
        }
        break;

        case 5:
        {
            DIO_ChannelGroupWrite(display_id, 0b01101101);
        }
        break;

        case 6:
        {
            DIO_ChannelGroupWrite(display_id, 0b01111101);
        }
        break;

        case 7:
        {
            DIO_ChannelGroupWrite(display_id, 0b00000111);
        }
        break;

        case 8:
        {
            DIO_ChannelGroupWrite(display_id, 0b01111111);
        }
        break;

        case 9:
        {
            DIO_ChannelGroupWrite(display_id, 0b01101111);
        }
        break;

        case SSD_DISABLE:
        {
            DIO_ChannelGroupWrite(display_id, 255);
        }
        break;

        default: /* Invalid input -> output 'F' */
        {
            DIO_ChannelGroupWrite(display_id, 0b01111001);
        }
        break;
    }
}



void SSD_MainFunction(void)
{
    // disable running display
    SSD_Write(SSD_ActiveDisplay, SSD_DISABLE);

    SSD_ActiveDisplay = (SSD_ActiveDisplay + 1)%2;

    // get data from timer
    // ...
    unsigned char data = SSD_Data; // critical section

    if(SSD_ActiveDisplay == 0) // a7ad
    {
        data = data % 10;
    }
    else  // 34rat
    {
        data = data / 10;
    }

    SSD_Write(SSD_ActiveDisplay, data);

}
