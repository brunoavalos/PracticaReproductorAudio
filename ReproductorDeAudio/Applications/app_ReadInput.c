/*
 * app_ReadInput.c
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#include "app_ReadInput.h"

T_UBYTE lub_ButtonState[NUMBERS_BUTTON];
void app_ReadInputValue(void)
{
	/* Previous Buttom */
	lub_ButtonState[0] = GPIO_ReadPinInput(GPIOD, 0);
	/* Next Button */
	lub_ButtonState[1] = GPIO_ReadPinInput(GPIOD, 2);
	/* Play Buttom */
	lub_ButtonState[2] = GPIO_ReadPinInput(GPIOD, 3);

}
