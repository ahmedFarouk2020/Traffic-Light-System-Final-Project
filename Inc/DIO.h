/*
 * DIO.h
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

void DIO_Init(void);
void DIO_ChannelWrite(unsigned char ChannelId, unsigned char Data);
void DIO_ChannelRead(unsigned char ChannelId, unsigned short int *DataPtr);
void DIO_ChannelGroupWrite(unsigned char channelGroup_id, unsigned short int data);
void DIO_ChannelGroupRead(unsigned char channelGroup_id, unsigned short int* DataPtr);
#endif /* INC_DIO_H_ */
