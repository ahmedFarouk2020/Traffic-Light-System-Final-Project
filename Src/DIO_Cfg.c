/*
 * DIO_Cfg.c
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#include "DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] =
{
    {/* led1  */
     0,
     0,
     1,/* OUT */
     0,
     0,
     255 /* NO AF */
    },
    {/* Channel1 UART_TX */
      0, /*port*/
      2, /* pin */
      2,/* AF */
      0, /* no pull resistors */
      0, /* PP */
      7 /* AF7 */
     },
     {/* Channel2 UART_RX */
       0, /*port*/
       3, /* pin */
       2,/* AF */
       0, /* no pull resistors */
       0, /* PP */
       7 /* AF7 */
      }
};


const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS] = {
       {
            {0,1,2,3},
            4
       }
};
