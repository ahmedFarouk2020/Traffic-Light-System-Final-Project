#include "stm32f401xc.h"
#include "Uart.h"
#include "DIO.h"

unsigned char buffer;

int main(void)
{
    DIO_Init();
    UART_Init();
    UART_SendStr(0, "Hello UART");
  while (1)
  {


      if(buffer == 'o')
      {
          DIO_ChannelWrite(0, 1);
      }
      else
      {
          DIO_ChannelWrite(0, 0);
      }
  }

}


