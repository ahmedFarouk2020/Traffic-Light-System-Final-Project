/*
 * DIO_Cfg.c
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#include "DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] =
{
    {/* led1 */
     1,
     10,
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
    },
    {1,0,1,0,0,255},   /* channel3 SS a pin */
    {1,1,1,0,0,255},   /* channel4 SS b pin */
    {1,2,1,0,0,255},   /* channel5 SS c pin */
    {1,3,1,0,0,255},   /* channel6 SS d pin */
    {1,4,1,0,0,255},   /* channel7 SS e pin */
    {1,5,1,0,0,255},   /* channel8 SS f pin */
    {1,6,1,0,0,255},   /* channel9 SS g pin */

    {1,7,1,0,0,255},     /* channel10 Control pin1 */
    {1,8,1,0,0,255},     /* channel11 Control pin2 */
    {0,1,0,1,0,255},     /* CH12 - simulate button Button */
    {0,0,1,0,0,255},   /*CH13 - led 1 */
    {0,6,1,0,0,255}, /* CH14 - led 2 */

    {0,7,1,0,0,255}, /* CH15 - led indicator for debugging */
    //{0,5,0,0,0,255} /* CH16 - Analog button */

};


const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS] = {
       {
            {3,4,5,6,7,8,9,10},
            8
       },
       {
           {3,4,5,6,7,8,9,11},
           8
       }
};
