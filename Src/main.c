#include "stm32f401xc.h"
#include "Uart.h"
#include "DIO.h"


int main(void)
{
    DIO_Init();
    UART_Init();
    UART_SendStr(0, "Hello UART");


  while (1)
  {

  }

}
