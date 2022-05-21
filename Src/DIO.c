#include "DIO.h"
#include "stm32f4xx.h"
#include "DIO_Cfg.h"
#include <stdint.h>


#define NUM_OF_PORTS ((unsigned char)4)


GPIO_TypeDef * Ports[NUM_OF_PORTS] =
{GPIOA,
 GPIOB,
 GPIOC,
 GPIOD};

void DIO_Init(void)
 {
     unsigned char Loop;

     for(Loop = (unsigned char)0; Loop < DIO_NUM_OF_CHANNELS; Loop++)
     {
         unsigned char PortId;
         /*read the port Id from link time configuration*/
         PortId = DIO_ConfigParam[Loop].PortId;

         /*verify Port Id*/
         if(PortId < NUM_OF_PORTS)
         {
        	 /*Enable clock*/
        	 RCC->AHB1ENR |= (1<<PortId);
        	 GPIO_TypeDef * GPIOx =Ports[PortId];

             unsigned char PinNumber = DIO_ConfigParam[Loop].PinNum;
        	 /*this  bit always = 0 in input or output mode */
             GPIOx->MODER &= ~(1<<(PinNumber*2+1));

        	 /*if output or AF*/
             unsigned char port_direction = DIO_ConfigParam[Loop].PortDirection;
             if((port_direction==1) || (port_direction==2))
             {

                 /* Clear the bit field */
                 GPIOx->MODER &= (unsigned int)( ~((unsigned int)3 << (2U*PinNumber)) );

                 GPIOx->MODER |= (port_direction<<(PinNumber*2));

            	 /*if output type open drain*/
            	 if(DIO_ConfigParam[Loop].OutputType == 1)
            	 {
            		 GPIOx->OTYPER |= (1<<(PinNumber));
            	 }
            	 /*if output type push-pull*/
            	 else
            	 {
            		 GPIOx->OTYPER &= ~(1<<(PinNumber));
            	 }

            	 /* map AF pin to a peripheral pin */
            	 if(DIO_ConfigParam[Loop].AFMapping < 8)
            	 {
            	     GPIOx->AFR[0] = DIO_ConfigParam[Loop].AFMapping <<4*PinNumber;
            	 }
            	 else if(DIO_ConfigParam[Loop].AFMapping <= 15) {
            	     GPIOx->AFR[1] = DIO_ConfigParam[Loop].AFMapping <<4*PinNumber;
            	 }
            	 else {
            	     // do nothing
            	 }
             }
             /*if input*/
             else if(DIO_ConfigParam[Loop].PortDirection == 0)
             {

            	 GPIOx->MODER &= ~(1<<(PinNumber*2));
            	 /*pull up */
            	 if(DIO_ConfigParam[Loop].PuPd == 1u)
            	 {
            		 GPIOx->PUPDR |= (1<<(PinNumber*2));
            		 GPIOx->PUPDR &= ~(1<<(PinNumber*2+1));
            	 }
            	 /*pull down */
            	 else if(DIO_ConfigParam[Loop].PuPd == 2u)
				 {
            		 GPIOx->PUPDR |= (1<<(PinNumber*2+1));
            		 GPIOx->PUPDR &= ~(1<<(PinNumber*2));
				 }
            	 /* No pull-up, pull-down */
            	 else
            	 {
            		 GPIOx->PUPDR &= ~(1<<(PinNumber*2));
            		 GPIOx->PUPDR &= ~(1<<(PinNumber*2+1));

            	 }
             }
             /* AF */
             else {
                 // next update
             }

         }
         else
         {
             /*invalid port*/
             break;
         }
     }
 }

/*Function shall do the following:
1- To Validate Channel ID
2- To get the port ID from configuration based on the Channel ID
3- To write port for the masked pins with the passed data value
4- Data shall be written only for the output pins*/
void DIO_ChannelWrite(unsigned char ChannelId, unsigned char Data)
{

	if (ChannelId<DIO_NUM_OF_CHANNELS)
	{
		unsigned char PortId;
		PortId = DIO_ConfigParam[ChannelId].PortId;
		if(DIO_ConfigParam[ChannelId].PortDirection == 1)
		{
			GPIO_TypeDef * GPIOx =Ports[PortId];
			if(Data != 0)
			{
			    GPIOx->ODR|= (1<< (DIO_ConfigParam[ChannelId].PinNum));
			}
			else
			{
			    GPIOx->ODR &= ~(1<< (DIO_ConfigParam[ChannelId].PinNum));
			}
		}
		else // INPUT -> do nothing
		{
//			GPIO_TypeDef * GPIOx =Ports[PortId];
//			GPIOx->ODR &= ~(1<<(DIO_ConfigParam[ChannelId].PinNum));
		}

	}
}

/*
 * LSB in Data affect channel 0 in channel group
 */
void DIO_ChannelGroupWrite(unsigned char channelGroup_id, unsigned short int data)
{
    if(channelGroup_id < DIO_NUM_OF_CHANNELGROUPS){

        unsigned char it;
        unsigned char channel_data = (unsigned char)0;

        for(it = (unsigned char)0; it < DIO_ChannelGroupList[channelGroup_id].channelGroup_size; it++)
        {
            channel_data = data & (unsigned char)1;
            DIO_ChannelWrite(DIO_ChannelGroupList[channelGroup_id].channelsId[it], channel_data);
            data = data>> (unsigned char)1;
        }
    }
}


void DIO_ChannelGroupRead(unsigned char channelGroup_id, unsigned short int* DataPtr)
{
    *DataPtr = 0; /* reinit the buffer */

    if(channelGroup_id <= DIO_NUM_OF_CHANNELGROUPS)
    {
        unsigned char it ;
        unsigned short int channel_data = (unsigned short int)0;

        for(it = (unsigned char)0; it < DIO_ChannelGroupList[channelGroup_id].channelGroup_size; ++it)
        {
            DIO_ChannelRead(DIO_ChannelGroupList[channelGroup_id].channelsId[it], &channel_data);
            *DataPtr |= ( (channel_data&1) <<it );
        }
    }
}

/*Function shall do the following:
1- To Validate Channel ID
2- To get the port ID from configuration based on the Channel ID
3- To read port for the masked pins and other pins shall be returned by 0
4- Data shall be read only for the input pins*/

void DIO_ChannelRead(unsigned char ChannelId, unsigned short int *DataPtr)
{

	if (ChannelId<DIO_NUM_OF_CHANNELS)
		{
			unsigned char PortId;
			PortId = DIO_ConfigParam[ChannelId].PortId;
            GPIO_TypeDef * GPIOx =Ports[PortId];

			if(!DIO_ConfigParam[ChannelId].PortDirection)
			{
				 *DataPtr = ( (1<<(DIO_ConfigParam[ChannelId].PinNum)) & GPIOx->IDR)?1:0;
			}

		}

}
