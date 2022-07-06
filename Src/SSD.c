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

extern void vTaskSuspendAll(void);
extern void xTaskResumeAll(void);

unsigned char SSD_Data; // value of timer
static unsigned char SSD_ActiveDisplay; // id of the active display



void SSD_Init(void)
{
    SSD_Data = 0;
    SSD_ActiveDisplay = 0;
}

void SSD_Write(unsigned char display_id, unsigned char data)
{
    switch(data)
    {
        case 0:
        {
            DIO_ChannelGroupWrite(display_id, ZERO);
        }
        break;

        case 1:
        {
            DIO_ChannelGroupWrite(display_id, ONE);
        }
        break;

        case 2:
        {
            DIO_ChannelGroupWrite(display_id, TWO);
        }
        break;

        case 3:
        {
            DIO_ChannelGroupWrite(display_id, THREE);
        }
        break;

        case 4:
        {
            DIO_ChannelGroupWrite(display_id, FOUR);
        }
        break;

        case 5:
        {
            DIO_ChannelGroupWrite(display_id, FIVE);
        }
        break;

        case 6:
        {
            DIO_ChannelGroupWrite(display_id, SIX);
        }
        break;

        case 7:
        {
            DIO_ChannelGroupWrite(display_id, SEVEN);
        }
        break;

        case 8:
        {
            DIO_ChannelGroupWrite(display_id, EIGHT);
        }
        break;

        case 9:
        {
            DIO_ChannelGroupWrite(display_id, NINE);
        }
        break;

        case SSD_DISABLE:
        {
            DIO_ChannelGroupWrite(display_id, DISABLE_SSD);
        }
        break;

        default: /* Invalid input -> output 'F' */
        {
            DIO_ChannelGroupWrite(display_id, 0b01111001);
        }
        break;
    }
}

void SSD_Display(unsigned char number)
{
    SSD_Data = number;
}

void SSD_MainFunction(void)
{
    vTaskSuspendAll();
    unsigned char data = SSD_Data; // critical section
    xTaskResumeAll();

    // disable running display
    SSD_Write(SSD_ActiveDisplay, SSD_DISABLE);

    SSD_ActiveDisplay = (SSD_ActiveDisplay + 1)%2;

    if(SSD_ActiveDisplay == 1) // a7ad
    {
        data = data % 10;
    }
    else  // 34rat
    {
        data = data / 10;
    }

    SSD_Write(SSD_ActiveDisplay, data);

}
