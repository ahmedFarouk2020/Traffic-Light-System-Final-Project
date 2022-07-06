/*
 * EVD.c
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */

#include "EVD.h"
#include "DIO.h"

extern void DIO_ChannelWrite(unsigned char ChannelId, unsigned char Data);// for debugging

static unsigned char EVD_EmergencyState;
unsigned char EVD_DataFrame[3];

static unsigned char EVD_ParserStatus;

void EVD_Init(void)
{
    EVD_ParserStatus = 0;
    EVD_EmergencyState = 0;

    EVD_DataFrame[0] = 0;
    EVD_DataFrame[1] = 0;
    EVD_DataFrame[2] = 0;
}


/*
 * Check if the data is meaningful and check for vehicle ID
 */
void EVD_ParseFrame(unsigned char frame[])
{
    if(EVD_DataFrame[0] == 'S'/*0xAA*/ && EVD_DataFrame[2] == 'U'/*0x55*/)
    {
        if( (EVD_DataFrame[1] == '2'/*0x02*/) || (EVD_DataFrame[1] == '3'/*0x03*/) ) {
            // set emergency
            EVD_EmergencyState = 1;

        }
        else
        {
            EVD_EmergencyState = 0;
        }
    }
}

//void EVD_ParseFrame(unsigned char frame[])
//{
//    if( (EVD_DataFrame[1] == '2'/*0x02*/) || (EVD_DataFrame[1] == '3'/*0x03*/) ) {
//        // set emergency
//        EVD_EmergencyState = 1;
//    }
//    else
//    {
//        EVD_EmergencyState = 0;
//    }
//}


void EVD_ResetEmergency() /* Callback from timer */
{
    App_EmergencyFlag = 0;
    DIO_ChannelWrite(15,0);
}

void EVD_MainFunction(void)
{
    EVD_ParseFrame(EVD_DataFrame);

    if(EVD_EmergencyState == 1) // Emergency?
    {
        App_EmergencyFlag = 1; // app won't interrupt it (highest priority task)
    }
    else {}
}
