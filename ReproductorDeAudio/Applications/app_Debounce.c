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
T_UBYTE rub_Button[NUMBERS_BUTTON];
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

		if(lub_o[lub_i] > 1)
		{
			lub_ButtonState[lub_i] = 0u;
			lub_i = lub_i + 1;
		}
		if(lub_o[lub_i] == 1)
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
					lub_o[lub_i] = 0u;
					rub_States[lub_i] = LONGPRESS;
				}
				else if((rub_Button[lub_i] == 0) && (lub_o[lub_i] > 50) && (lub_o[lub_i] < 200))
				{
					lub_o[lub_i] = 0u;
					rub_States[lub_i] = PRESS;
				}
				else if(rub_Button[lub_i] == 1)
				{
					lub_o[lub_i] = 0u;
					rub_States[lub_i] = NOTPRESS;
				}
				lub_i = lub_i + 1;
		}
}

void app_DebounceStages(void)
{
	lub_i = 0;
	while(lub_i < 3)
	{
		if(lub_ButtonState[lub_i] == 0)
		{

			switch(rub_States[lub_i])
			{
			case NOTPRESS:
			{
//				if(rub_StopRotabit == FALSE)
//				{
					if(rub_flagPIT2 == TRUE)
					{
						app_FOWARD();
						rub_flagPIT2 = FALSE;
					}
//				}

			}break;
			case PRESS:
			{
				/* Previous Buttom PTD0*/
				if(lub_ButtonState[0] == 0)
				{
						app_BACK();
				}
				/* Next Button PTD2*/
				if(lub_ButtonState[1] == 0)
				{
						app_NEXT();
				}
				/* Play Buttom PTD3*/
				if(lub_ButtonState[2] == 0)
				{
					rub_PausePlay = FALSE;
					rub_StopRotabit = FALSE;
				}
			}break;
			case LONGPRESS:
			{
				/* Previous Buttom PTD0*/
				if(lub_ButtonState[0] == 0)
				{
					if(rub_flagPIT1 == TRUE)
					{
						app_REWIND();
						rub_flagPIT1 = FALSE;
					}
				}
				/* Next Button PTD2*/
				if(lub_ButtonState[1] == 0)
				{
					if(rub_flagPIT1 == TRUE)
					{
						app_FOWARD();
						rub_flagPIT1 = FALSE;
					}
				}
				if(lub_ButtonState[2] == 0)
				{
					lub_Output = 0u;
					lub_ActualTrack = 0u;
					rub_StopRotabit = TRUE;
				}

			}
			}break;
		}
		lub_i = lub_i + 1;
	}
}


