/*
 * EVD.h
 *
 *  Created on: May 22, 2022
 *      Author: Farouk
 */

#ifndef INC_EVD_H_
#define INC_EVD_H_

extern unsigned char EVD_DataFrame[3];
extern unsigned char App_EmergencyFlag;

/* Function Prototypes */
void EVD_Init(void);
void EVD_MainFunction(void);

#endif /* INC_EVD_H_ */
