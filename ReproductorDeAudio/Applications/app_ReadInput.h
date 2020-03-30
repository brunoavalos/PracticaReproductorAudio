/*
 * app_ReadInput.h
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#ifndef APP_READINPUT_H_
#define APP_READINPUT_H_

#include "../drivers/fsl_gpio.h"
#include "../source/typedef_macros.h"
#include "app_Debounce.h"
#include "app_PITFlag.h"


extern unsigned char lub_ButtonState[NUMBERS_BUTTON];
extern void app_ReadInputValue(void);

#endif /* APP_READINPUT_H_ */
