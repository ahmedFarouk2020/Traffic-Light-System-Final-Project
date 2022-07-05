/*
 * DIO_Cfg.h
 *
 *  Created on: Mar 23, 2022
 *      Author: Farouk
 */


#ifndef INC_DIO_CFG_H_
#define INC_DIO_CFG_H_

#define DIO_NUM_OF_CHANNELS               ((unsigned char)17)
#define DIO_NUM_OF_CHANNELGROUPS          ((unsigned char)2)
#define DIO_MAX_NUM_OF_CHANNELS_IN_GROUP  ((unsigned char)8)

typedef struct
{
    unsigned char PortId;
    unsigned char PinNum;
    unsigned char PortDirection;/*0 = input,1 = output 2=AF*/
    unsigned char PuPd; /*0 = No pull-up, pull-down,1 up,2 down*/
    unsigned char OutputType;/*0 = push-pull,1 = open drain*/
    unsigned char AFMapping; /* 0->15 -- see pinout to determine 255 if not AF*/

}DIO_ChannelConfigType;


typedef struct
{
    unsigned char channelsId[DIO_MAX_NUM_OF_CHANNELS_IN_GROUP];
    unsigned char channelGroup_size;
}DIO_ChannelGroupConfigType;



extern const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS];
extern const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS];

#endif /* INC_DIO_CFG_H_ */
