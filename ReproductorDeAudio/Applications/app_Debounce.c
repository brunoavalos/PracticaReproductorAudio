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
T_UBYTE rub_States[3];
T_UBYTE rub_lub_o = 0u;
T_UBYTE lub_i = 0u;
T_UBYTE lub_o[NUMBERS_BUTTON] = {0,0,0};
T_UBYTE rub_PausePlay;
T_UBYTE rub_StopRotabit = FALSE;

void app_DebounceTask(void)
{
	app_DebounceValues();
	app_DebounceSelecction();
	app_DebounceStages();
}

void app_DebounceValues(void)
{
	lub_i = 0u;
	T_UBYTE lub_UpDown = FALSE;
	app_ReadInputValue();
	while(lub_i < NUMBERS_BUTTON)
	{

		if((lub_o[lub_i] > 200) && (lub_ButtonState[lub_i] == 1))
		{
			rub_Button[lub_i] = 0u;
			lub_i = lub_i + 1;
			lub_UpDown = TRUE;
		}
		if((lub_o[lub_i] > 50) && (lub_o[lub_i] < 200) && (lub_ButtonState[lub_i] == 1))
				{
					rub_Button[lub_i] = 0u;
					lub_i = lub_i + 1;
					lub_UpDown = TRUE;
				}
		if(lub_ButtonState[lub_i] == 1)
				{
					rub_Button[lub_i] = lub_ButtonState[lub_i];
					lub_i = lub_i + 1;
				}
		else
		{
			for(lub_o[lub_i]=0u;(lub_ButtonState[lub_i] == 0) && (lub_UpDown == FALSE); lub_o[lub_i]++)
			{

			if((rub_flagPIT1 == TRUE) && (lub_i == 1) && (lub_o[1] > 200) && (rub_PausePlay == TRUE))
			{

				app_FOWARD();
				lub_o[lub_i] = lub_o[lub_i] + 1;
				rub_flagPIT1 = FALSE;
			}
			if((rub_flagPIT1 == TRUE) && (lub_i == 0) && (lub_o[0] > 200) && (rub_PausePlay == TRUE))
			{

				app_REWIND();
				lub_o[lub_i] = lub_o[lub_i] + 1;
				rub_flagPIT1 = FALSE;


			}
				else
				{
				lub_o[lub_i] = lub_o[lub_i] + 1;
				app_ReadInputValue();
				}
			}

		}
	}

}

void app_DebounceSelecction(void)
{
	lub_i = 0;
		while(lub_i < NUMBERS_BUTTON)
		{
				if((rub_Button[lub_i] == 0) && (lub_o[lub_i] > 200))
				{
					rub_States[lub_i] = LONGPRESS;
				}
				if((rub_Button[lub_i] == 0) && (lub_o[lub_i] > 50) && (lub_o[lub_i] < 199))
				{
					rub_States[lub_i] = PRESS;
				}
				else if(rub_Button[lub_i] == 1)
				{
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
				/* Not Used */
			}
			if(rub_States[lub_i] == PRESS)
			{
				switch (rub_ButtonsStates[lub_i]) {
					case 0: {
						if(rub_PausePlay == TRUE)
						{
						lub_ActualTrack--;
						app_TrackIndicatorOutput(lub_ActualTrack);
						lub_o[lub_i] = 0u;
						}
					}
						break;
					case 1: {
						if(rub_PausePlay == TRUE)
						{
						lub_ActualTrack++;
						app_TrackIndicatorOutput(lub_ActualTrack);
						lub_o[lub_i] = 0u;
						}
					}
						break;
					case 2: {
						if(rub_StopRotabit == FALSE)
						{
						lub_o[1] = 0u;
						lub_o[0] = 0u;
						lub_o[2] = 0u;
						rub_PausePlay = TRUE;

						}
						else if(rub_PausePlay == TRUE)
						{
							rub_PausePlay = FALSE;
							rub_StopRotabit = FALSE;
							lub_o[lub_i] = 0u;

						}
					}
					break;
				}
			}
		if (rub_States[lub_i] == LONGPRESS) {
			if(rub_Button[2] == 0)
			{
				GPIOB->PDOR = 0u;
				app_TrackIndicatorOutput(0u);
				lub_o[lub_i] = 0u;
				rub_PausePlay = FALSE;
			}

			}
			else
			{
			if (rub_flagPIT2 == TRUE) {
				if(rub_PausePlay == TRUE)
				{
					app_FOWARD();
					rub_StopRotabit = TRUE;
				}
				rub_flagPIT2 = FALSE;
			}
			}
			lub_i = lub_i + 1;
		}

}


