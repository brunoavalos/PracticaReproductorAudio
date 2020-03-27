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


extern unsigned char lub_ButtonState[2];
extern void app_ReadInputValue(void);

#endif /* APP_READINPUT_H_ */
