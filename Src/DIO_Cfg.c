/*
 * DIO_Cfg.c
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#include "DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] =
{
     {/* Channel-8 UART_TX */
      0, /*port*/
      2, /* pin */
      2,/* output */
      0, /* no pull resistors */
      0, /* PP */
      7 /* AF7 */
     }
};


const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS] = {
       {
            {0,1,2,3},
            4
       },
       {
            {5,6,7,8},
            4
      }
};
