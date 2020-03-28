/*
 * app_NewButtonState.c
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#include "app_NewButtonState.h"

/* Valor de los botones */

T_UBYTE lub_ButtonState[2];

typedef enum{
	LongPress, /*0 */
	NormalPress /* 1*/
}NewButtonState;


void app_NewButtonState_Task(void)
{
	app_NewButtonInputValue();

	app_NewButtonCounter();
}

void app_NewButtonInputValue(void)
{
NewButtonState States;



}
