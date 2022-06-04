/*
 * app.c
 *
 *  Created on: Jun 3, 2022
 *      Author: Farouk
 */


#define APP_GREEN_STATE      0
#define APP_RED_STATE        1
#define APP_YELLOW_STATE     2

unsigned char App_EmergencyFlag;
unsigned char App_CurrentState;

unsigned char App_Counter;

void App_Init(void)
{
    App_Counter = 0;
    App_EmergencyFlag = 0;
    App_CurrentState = APP_GREEN_STATE;
}

void App_MainFunction(void) /* 1 second */
{
    switch(App_CurrentState)
    {
        case APP_GREEN_STATE: /* Default state */
        {
            if((App_EmergencyFlag==0) && (Button_Request==1))
            {
                /* clear request */
                Button_Request = 0;
                /* display 10 on 7-segment */
                SSD_Display(10);
                /* set counter to 10 */
                App_Counter = 10;

                App_CurrentState = APP_YELLOW_STATE;
            }
        }
        break;
        case APP_YELLOW_STATE:
        {
            if(App_Counter == 0)
            {
                Led_TurnOff(LED_YELLOW);
                Led_TurnOn(LED_RED);
                /* display 30 on 7-segment */
                SSD_Display(30);
                /* set counter to 30 */
                App_Counter = 30;
                App_CurrentState = APP_RED_STATE;
            }
            App_Counter--;
            /* display on 7-segment */
            SSD_Display(App_Counter);
            Led_TurnOn(LED_YELLOW);
        }
        break;
        case APP_RED_STATE:
        {
            if(App_Counter == 0)
            {
                Led_TurnOff(LED_RED);
                Led_TurnOn(LED_GREEN);

                App_CurrentState = APP_GREEN_STATE;
            }
            App_Counter--;
            /* display on 7-segment */
            SSD_Display(App_Counter);
        }
        break;
        default: /* System Fault */
        {
            Led_TurnOn(LED_GREEN);
            Led_TurnOn(LED_RED);
            Led_TurnOn(LED_YELLOW);
        }
        break;
    }
}





























