/*
 * app_Debounce.c
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */
#include "app_Debounce.h"

void app_DebounceValues(void);
void app_DebounceCondition(void);
void app_DebounceSelecction(void);
void app_DebounceStages(void);

/* Variables globales */
T_UBYTE rub_Timer = 0u;

/* Banderas */

T_UBYTE rub_ShortPress = FALSE;
T_UBYTE rub_LongPress = FALSE;
T_UBYTE rub_Button[NUMBERS_BUTTON] = {1,1,1};
T_UBYTE rub_ButtonsStates[NUMBERS_BUTTON];
T_UBYTE rub_States[4];
T_UBYTE rub_lub_o = 0u;
T_UBYTE lub_i = 0u;
T_UBYTE lub_o[NUMBERS_BUTTON] = {0,0,0};
T_UBYTE rub_StatesFalse[4];
T_UBYTE rub_PausePlay = FALSE;
T_UBYTE rub_StopRotabit = TRUE;

void app_DebounceTask(void)
{
	app_DebounceValues();
	app_DebounceSelecction();
	app_DebounceStages();
}

void app_DebounceValues(void)
{
	lub_i = 0u;
	app_ReadInputValue();
	while(lub_i < NUMBERS_BUTTON)
	{

		if((lub_o[lub_i] > 50) && ((lub_ButtonState[lub_i] == 1)))
		{
			rub_Button[lub_i] = 0u;
			lub_i = lub_i + 1;
		}
		if(lub_ButtonState[lub_i] == 1)
		{
			rub_Button[lub_i] = lub_ButtonState[lub_i];
			lub_i = lub_i + 1;
		}
		else
		{
			do{
				lub_o[lub_i] = lub_o[lub_i] + 1;
				app_ReadInputValue();
			}while(lub_ButtonState[lub_i] == 0);
		}
	}

}

void app_DebounceSelecction(void)
{
	lub_i = 0;
		while(lub_i < NUMBERS_BUTTON)
		{
				if((rub_Button[lub_i] == 0) && (lub_o[lub_i] >= 200))
				{
//					lub_o[lub_i] = 0u;
					rub_States[lub_i] = LONGPRESS;
				}
				if((rub_Button[lub_i] == 0) && (lub_o[lub_i] > 50) && (lub_o[lub_i] < 200))
				{
//					lub_o[lub_i] = 0u;
					rub_States[lub_i] = PRESS;
				}
				else if(rub_Button[lub_i] == 1)
				{
//					lub_o[lub_i] = 0u;
					rub_States[lub_i] = NOTPRESS;
				}
				lub_i = lub_i + 1;
				rub_ButtonsStates[lub_i] = lub_i;
		}
}

void app_DebounceStages(void)
{
	lub_i = 0;
	while(lub_i < 3)
	{
			if(rub_States[lub_i] == NOTPRESS)
			{
				if (rub_flagPIT2 == TRUE) {
					app_FOWARD();
					rub_flagPIT2 = FALSE;
				}

			}
			if(rub_States[lub_i] == PRESS)
			{
				switch (rub_ButtonsStates[lub_i]) {
					case 0: {
						lub_o[lub_i] = 0;
						app_BACK();
					}
						break;
					case 1: {
						lub_o[lub_i] = 0;
						app_NEXT();
					}
						break;
					case 2: {
					rub_PausePlay = FALSE;
					rub_StopRotabit = FALSE;
					}
					break;
				}
			}
			if(rub_States[lub_i] == LONGPRESS)
			{
				switch (rub_ButtonsStates[lub_i])
				{
					case 0: {
					if (rub_flagPIT1 == TRUE) {
						app_REWIND();
						rub_flagPIT1 = FALSE;
					}
					}
						break;
					case 1: {
					if (rub_flagPIT1 == TRUE) {
						app_FOWARD();
						rub_flagPIT1 = FALSE;
					}

					}
						break;
					case 2: {
						lub_Output = 0u;
						lub_ActualTrack = 0u;
						rub_StopRotabit = TRUE;

					}
						break;
				}
			}
			else
			{
				/* Do nothing */
			}
			lub_i = lub_i + 1;
		}

}


