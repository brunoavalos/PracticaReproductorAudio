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
T_UBYTE rub_Button[NUMBERS_BUTTON] = {0,0,0};
T_UBYTE rub_States[4];
T_UBYTE rub_lub_o = 0u;
T_UBYTE lub_i = 0u;
T_UBYTE lub_o = 0u;
T_UBYTE rub_StatesFalse[4];
T_UBYTE rub_PausePlay = FALSE;
T_UBYTE rub_StopRotabit = TRUE;

void app_DebounceTask(void)
{
	app_DebounceValues();
	app_DebounceCondition();
	app_DebounceSelecction();
}

void app_DebounceValues(void)
{
	lub_i = 0u;
	app_ReadInputValue();
	while(lub_i < NUMBERS_BUTTON)
	{
		while((lub_ButtonState[lub_i] != 1) && (lub_o > 1))
		{
			lub_ButtonState[lub_i] = GPIO_ReadPinInput(GPIOD, lub_i);
			lub_o = lub_o + 1;
		}
		if(lub_o > 0)
		{
			lub_ButtonState[lub_i] = 0u;
		}
		else
		{
			rub_Button[lub_i] = lub_ButtonState[lub_i];
			lub_i = lub_i + 1;
		}
	}

}

void app_DebounceCondition(void)
{
	lub_i = 0;
	while(lub_i > NUMBERS_BUTTON)
	{
		if(rub_Button[lub_i] == 0)
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
		while(lub_i > NUMBERS_BUTTON)
		{
				if((rub_Button[lub_i] == 0) && (lub_o > 200))
				{
					lub_o = 0u;
					rub_States[lub_i] = LONGPRESS;
					app_DebounceStages();
				}
				else if((rub_Button[lub_i] == 0) && (lub_o > 50) && (lub_o < 200))
				{
					lub_o = 0u;
					rub_States[lub_i] = PRESS;
					app_DebounceStages();
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
				if(rub_StopRotabit == FALSE)
				{
					if(rub_flagPIT2 == TRUE)
					{
						app_FOWARD();
						rub_flagPIT2 = FALSE;
					}
				}

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


