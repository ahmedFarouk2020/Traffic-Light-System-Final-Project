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


/*
 * Everything is fine when timing constrains is not so hard
 * But when applying the constrains as per requirements, interrupt is not working and button response is so slow
 * It thinks the systems is overloaded (more than 100% utilization), so we need timing study
 */

SemaphoreHandle_t s;
TimerHandle_t t;

unsigned char Button_Request;

extern void EVD_ResetEmergency();

void Get_ButtonReq(unsigned char *value) {
    vTaskSuspendAll();
    *value = Button_Request;
    xTaskResumeAll();
}

void Set_ButtonReq(void) {
    vTaskSuspendAll();
    Button_Request = 1;
    xTaskResumeAll();
}
void Reset_ButtonReq(void) {
    vTaskSuspendAll();
    Button_Request = 0;
    xTaskResumeAll();
}

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

        xSemaphoreTake(s, portMAX_DELAY);

        EVD_MainFunction();

        if(App_EmergencyFlag == 1) // Emergency?
        {
            xTimerStart( t, pdMS_TO_TICKS(10000) );
            DIO_ChannelWrite(15,1);
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
    Button_Init();
    SSD_Init();
    EVD_Init();
    App_Init();


    TaskHandle_t handle_Led_App;
    TaskHandle_t handle_EVD;
    TaskHandle_t handle_Button;
    TaskHandle_t handle_SSD;

    t = xTimerCreate("Timer",pdMS_TO_TICKS(10000),pdFALSE,(void*) 0,(TimerCallbackFunction_t)EVD_ResetEmergency);

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

    BaseType_t HP_Task = pdFALSE;

    xSemaphoreGiveFromISR(s,&HP_Task);

    EVD_DataFrame[1] = USART2->DR;
    USART2->SR &= ~(1<< USART_SR_RXNE_Pos);

    portYIELD_FROM_ISR( HP_Task );
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
