#include "stm32f401xc.h"
#include "DIO.h"
#include "Uart.h"
#include "Adc.h"
#include "Button.h"
#include "SSD.h"
#include "LED.h"
#include "EVD.h"
#include "App.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "semphr.h"
#include "task.h"
#include "event_groups.h"

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)

/*
 * Everything is fine when timing constrains is not so hard
 * But when applying the constrains as per requirements, interrupt is not working and button response is so slow
 * It thinks the systems is overloaded (more than 100% utilization), so we need timing study
 */

SemaphoreHandle_t s;
TimerHandle_t t;
EventGroupHandle_t eventGroup_handle;


extern void EVD_ResetEmergency();


void TASK_Led_App(void *ptr) // period = 1 second
{
    const TickType_t Interval = pdMS_TO_TICKS(1000);

    TickType_t currentTick;
    currentTick = xTaskGetTickCount();

    while(1)
    {
        vTaskDelayUntil(&currentTick, Interval);

        App_MainFunction();
        Led_MainFunction();
    }
}

void TASK_SSD(void *ptr) // period = 10ms second
{
    const TickType_t Interval = pdMS_TO_TICKS(15);

    TickType_t currentTick;
    currentTick = xTaskGetTickCount();

    while(1)
    {
        vTaskDelayUntil(&currentTick, Interval);
        SSD_MainFunction();
    }
}


void TASK_EVD(void *ptr)
{

    while(1) {

        xEventGroupWaitBits(eventGroup_handle,BIT0|BIT1|BIT2 ,pdTRUE,pdTRUE,(TickType_t)portMAX_DELAY );

        EVD_MainFunction();
        DIO_ChannelWrite(15,1);

        if(App_EmergencyFlag == 1) // Emergency?
        {
            xTimerStart( t, pdMS_TO_TICKS(10000) );
        }
    }
}

void TASK_Button(void *ptr) // period 10 ms
{
    const TickType_t Interval = pdMS_TO_TICKS(10);

    TickType_t currentTick;
    currentTick = xTaskGetTickCount();

    while(1)
    {

        vTaskDelayUntil(&currentTick, Interval);

        Button_MainFunction();// بتبوظ تاسك ال EVD كمان
    }
}

int main()
{
    /* System Initializations */
    DIO_Init();
    ADC_Init();
    UART_Init();
    Led_Init();
    SSD_Init();
    EVD_Init();
    App_Init();


    TaskHandle_t handle_Led_App;
    TaskHandle_t handle_EVD;
    TaskHandle_t handle_Button;
    TaskHandle_t handle_SSD;

    t = xTimerCreate("Timer",pdMS_TO_TICKS(10000),pdFALSE,(void*) 0,(TimerCallbackFunction_t)EVD_ResetEmergency);

    eventGroup_handle = xEventGroupCreate();
    vSemaphoreCreateBinary(s);

    xTaskCreate(TASK_Led_App, "TASK_Led_App", ( unsigned short ) 350, NULL, 3, &handle_Led_App);
    xTaskCreate(TASK_EVD, "TASK_EVD", ( unsigned short ) 400, NULL, 1, &handle_EVD);
    xTaskCreate(TASK_SSD, "TASK_SSD", ( unsigned short ) 300, NULL, 4, &handle_SSD);
    xTaskCreate(TASK_Button,"TASK_Button", ( unsigned short ) 300, NULL, 2, &handle_Button);

    vTaskStartScheduler();

    while(1);
    return 0;
}


void USART2_IRQHandler(void)
{
    static unsigned char frameId = 0;

    if(xEventGroupGetBitsFromISR(eventGroup_handle) != 0x07)
    {
        vTaskSuspendAll();

        BaseType_t HP_Task = pdFALSE;
        BaseType_t Result = pdFALSE;

        Result = xEventGroupSetBitsFromISR(eventGroup_handle, (1<<frameId), &HP_Task );

        EVD_DataFrame[frameId] = USART2->DR;
        USART2->SR &= ~(1<< USART_SR_RXNE_Pos);

        frameId = (frameId + 1 ) % 3;

        xTaskResumeAll();

        if( Result != pdFAIL )
        {
            portYIELD_FROM_ISR( HP_Task );
        }

        DIO_ChannelWrite(15,1);
    }
    else
    {
        DIO_ChannelWrite(15,0);
    }

}
//void USART2_IRQHandler(void)
//{
//    BaseType_t xHigherPriorityTaskWoken, Result;
//
//    xHigherPriorityTaskWoken = pdFALSE;
//
//    Result = xEventGroupSetBitsFromISR(event, BIT_0, &xHigherPriorityTaskWoken );
//
//    USART2->SR &= ~(1<< USART_SR_RXNE_Pos);
//
//    EVD_DataFrame[1] = USART2->DR;
//
//    if( Result != pdFAIL )
//     {
//        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
//     }
//    // set event from ISR
////    EVD_ReceiveStatus = 1;
//
//}
