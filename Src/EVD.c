/*
 * EVD.c
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */

unsigned char EVD_DataFrame[3];
unsigned char EVD_ReceiveStatus;
unsigned char EVD_ParserStatus;
unsigned char EVD_EmergencyState;
unsigned char buffer;


void EVD_Init(void)
{
    EVD_ReceiveStatus = 0;
    EVD_ParserStatus = 0;
    EVD_EmergencyState = 0;
}


/*
 * Check if the data is meaningful and check for vehicle ID
 */
void EVD_ParseFrame(unsigned char frame[])
{
    if(EVD_DataFrame[0] == 0xAA && EVD_DataFrame[2] == 0x55)
    {
        if( (EVD_DataFrame[1] == 0x02) || (EVD_DataFrame[1] == 0x03) ) {
            // set emergency
            EVD_EmergencyState = 1;
        }
    }
}

void EVD_ResetEmergency(void) /* Callback from timer */
{
    EVD_EmergencyState = 0;
}

void EVD_MainFunction(void)
{
    if(EVD_ReceiveStatus == 1) /* New frame arrives */
    {
        EVD_ReceiveStatus = 0;
        EVD_ParseFrame(EVD_DataFrame);
    }

    unsigned char state = EVD_EmergencyState;

    if(state == 1) /* Emergency? */
    {
        // set timer 10 sec and once timer expired the callback zero the emergency
    }
}
