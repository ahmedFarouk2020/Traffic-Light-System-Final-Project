#include "ADC.h"
#include "stm32f401xc.h"

void ADC_Init(void)
{
/* Enable port A clock */
	RCC->AHB1ENR |= ( 0x1 << 0 );
/* Select Analog mode for pin 0 */
	GPIOA->MODER |= ( 0x3 << 10 );
/* Select no pull-up, pull-down  */
	GPIOA->PUPDR &= ~( 0x3 << 10 );
/* Enable ADC1 clock */
	RCC->APB2ENR |= ( 0x1 << 8 );
/* Enable ADC */
	ADC1->CR2 |= ( 0x1 << 0 );
/* Select ADC1 12-bits Resolution */
	ADC1->CR1 &= ~( 0x3 << 24 );
/* ADC prescaler PCLK2 divided by 2 */
	ADC->CCR &= ~( 0x3 << 16 );
/* Select data to be right alignment */
	ADC1->CR2 &= ~( 0x1 << 11 ) ;
/* Select channel 5 regular */
	ADC1->SQR1 &= ~( 0xF << 20 );  /* Select 1 Conversion */
	ADC1->SQR3 &= ~( 0x1F << 0 );  /* select channel 5 to be 1st conversion in regular sequence */
	ADC1->SQR3 |= (0x05<< 0) ;
/*select single mode */
	ADC1->CR2 &= ~( 0x1 << 1 );
/*select 3 Cycle sampling time */
	ADC1->SMPR2 &= ~( 0x7 << 15 );

}

unsigned int ADC_GetReading(void)
{
	unsigned int Data = 0 ;
	/* Start conversion of regular channels */
	ADC1->CR2 |= ( 0x1 << 30 );
	/* wait until conversion done */
	while(!(ADC1->SR & (0x1 << 1U)));
	Data = ADC1->DR;
	return Data;
}


