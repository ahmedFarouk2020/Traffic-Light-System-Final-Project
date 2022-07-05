/*
 * app.c
 *
 *  Created on: Jun 3, 2022
 *      Author: Farouk
 */
#include "App.h"
#include "Button.h"
#include "SSD.h"
#include "LED.h"


#define APP_GREEN_STATE      0
#define APP_RED_STATE        1
#define APP_YELLOW_STATE     2

/* External Variables */
extern unsigned char Button_Request;
extern unsigned char Led_Color;

/* Global Variables */
unsigned char App_EmergencyFlag;

extern void vTaskSuspendAll(void);
extern void xTaskResumeAll(void);
extern void Get_ButtonReq(unsigned char *value);
extern void Set_ButtonReq(void);
extern void Reset_ButtonReq(void);

void Get_AppEmergencyFlag(unsigned char *buffer) {
    vTaskSuspendAll();
    *buffer = App_EmergencyFlag;
    xTaskResumeAll();
}


/* Private variables */
static unsigned char App_CurrentState;
static unsigned char App_SavedRequest;
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
            unsigned char request;
            unsigned char Emergency_Flag;
            Get_ButtonReq(&request);
            Get_AppEmergencyFlag(&Emergency_Flag);

            if((Emergency_Flag==0) && (request==1))
            {
                /* clear request */
                Reset_ButtonReq();
				
				/* clear saved request */
				App_SavedRequest = 0;
                /* set counter to 10 */
                App_Counter = 10;
                /* display 10 on 7-segment */
                SSD_Display(App_Counter);

                App_CurrentState = APP_YELLOW_STATE;
            }
        }
        break;

        case APP_YELLOW_STATE:
        {
            if(App_Counter == 0)
            {
                Led_Color = LED_RED;
                /* set counter to 30 */
                App_Counter = 30;
                /* display 30 on 7-segment */
                SSD_Display(App_Counter);
                App_CurrentState = APP_RED_STATE;
            }
            else
            {
                App_Counter--;
                /* display on 7-segment */
                SSD_Display(App_Counter);
                Led_Color = LED_YELLOW;
            }
            /* clear request */
            Reset_ButtonReq();
        }
        break;

        case APP_RED_STATE:
        {
            if(App_Counter == 0)
            {
                Led_Color = LED_GREEN;
                App_CurrentState = APP_GREEN_STATE;
            }
            else
            {
                App_Counter--;
                /* display on 7-segment */
                SSD_Display(App_Counter);
            }
            /* clear request */
            Reset_ButtonReq();
        }
        break;
        default: /* System Fault */
        {
            Led_TurnOn(LED_GREEN);
            Led_TurnOn(LED_RED);
            Led_TurnOn(LED_YELLOW);
            while(1);
        }
        break;
    }
}
