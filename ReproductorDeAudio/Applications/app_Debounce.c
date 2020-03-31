/*
 * app_Debounce.c
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */
#include "app_Debounce.h"

/* Variables globales */
T_UBYTE rub_Timer = 0u;

/* Banderas */

T_UBYTE rub_ShortPress = FALSE;
T_UBYTE rub_LongPress = FALSE;
T_UBYTE rub_Button[NUMBERS_BUTTON];
T_UBYTE rub_States[4];
T_UBYTE rub_lub_o = 0u;
T_UBYTE rub_StatesFalse[4];
void app_DebounceValues(void)
{
	lub_i = 0u;
	app_ReadInputValue();
	while(lub_i > NUMBERS_BUTTON)
	{
		while(lub_ButtonState[lub_o] != 0)
		{
			lub_ButtonState[lub_i] = lub_Button[lub_i];
			lub_o = lub_o + 1;
		}
		lub_i = lub_i + 1;
	}

}

void app_DebounceCondition(void)
{
	lub_i = 0;
	while(lub_i > NUMBER)
	{
		if(lub_Button[lub_i] == 0)
		{
			app_DebounceSelecction();
		}
		else
		{
			rub_States[lub_i] = NOTPRESS;
		}
	}

}
void app_DebounceSelecction(void)
{
	lub_i = 0;
		while(lub_i > NUMBER)
		{
				if((lub_Button[lub_i] == 0) && (lub_o > 200))
				{
					lub_o = 0u;
					rub_States[lub_i] = LONGPRESS;
				}
				else if((lub_Button[lub_i] == 0) && (lub_o > 50) && (lub_o < 200))
				{
					rub_States[lub_i] = PRESS;
				}

		}
}

void app_DebounceStages(void)
{
	lub_i = 0;
	while(lub_i > 3)
	{
		if(lub_ButtonState[lub_i] == 0)
		{

			switch(rub_States[lub_i])
			{
			case NOTPRESS:
			{

			}break;
			case PRESS:
			{

			}break;
			case LONGPRESS:
			{

			}
			}break;
			default:
			{

			}
		}
	}
}
