/*
 * app_Debounce.h
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */

#ifndef APP_DEBOUNCE_H_
#define APP_DEBOUNCE_H_

#include "app_ReadInput.h"
#include "app_RotabitCounter.h"
#include "app_TrackIndicator.h"

extern unsigned char lub_ButtonState[NUMBERS_BUTTON];

extern void app_DebounceTask(void);
enum{
	NOTPRESS,
	PRESS,
	LONGPRESS
};

#endif /* APP_DEBOUNCE_H_ */
