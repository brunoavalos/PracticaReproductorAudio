/*
 * app_Debounce.h
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */

#ifndef APP_DEBOUNCE_H_
#define APP_DEBOUNCE_H_

#include "app_ReadInput.h"
extern unsigned char lub_ButtonState[NUMBERS_BUTTON];

enum{
	NOTPRESS,
	PRESS,
	LONGPRESS
};

#endif /* APP_DEBOUNCE_H_ */
