/*
 * app_Debounce.c
 *
 *  Created on: Mar 26, 2020
 *      Author: dario
 */

#include "app_Debounce.h"
#include "app_ReadInput.h"
#include "app_PITFlag.h"

/******************************************
 * Prototypes
 ******************************************/
static void app_Debounce_CheckButtonsState(void);
static void app_Debounce_IncreaseDbncCounter(T_UBYTE lub_ButtonNumber);
static void app_Debounce_ClearDbncCounter(T_UBYTE lub_ButtonNumber);
static void app_Debounce_Actions();

/******************************************
 * Variables
 ******************************************/
T_BUTTON_STATES rae_ButtonsState[NUMBERS_BUTTON];
T_UWORD	raub_ButtonDebounceCounters[NUMBERS_BUTTON];


/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_BtnDbnc_Init
 * Description: Manda mediante un arreglo de botones rae_ButtonsState
 * el estado inicial de BUTTON_UNPRESSED.
 ***********************************************/
void app_Debounce_Init(void)
{
	T_UBYTE lub_i;
	/* Clear all the counters and states*/
	for(lub_i = 0U; lub_i < NUMBERS_BUTTON; lub_i++)
	{
		raub_ButtonDebounceCounters[lub_i] = 0U; //Clear counter
		rae_ButtonsState[lub_i] = BUTTON_UNPRESSED; //Clear press state
	}
}

/***********************************************
 * Function Name: app_Debounce_TaskMngr
 * Description: TBD
 ***********************************************/
void app_Debounce_TaskMngr(void)
{
	/* Check the state for all buttons */
	app_Debounce_CheckButtonsState();
	/* Perform the corresponding action depending the buttons state */
	app_Debounce_Actions();
}

/***********************************************
 * Function Name: app_Debounce_CheckButtonsState
 * Description: TBD
 ***********************************************/
void app_Debounce_CheckButtonsState(void)
{
	T_UBYTE lub_i;
	/* Check the buttons state */
	for(lub_i = 0; lub_i < NUMBERS_BUTTON;lub_i++)
	{//Check for each button
		if(lub_ButtonState[lub_i] == FALSE)
		{//Button pressed in HW
			app_Debounce_IncreaseDbncCounter(lub_i);
		}
		else
		{//Button unpressed in SW
			app_Debounce_ClearDbncCounter(lub_i);
		}
	}
}

/***********************************************
 * Function Name: app_Debounce_IncreaseDbncCounter
 * Description: TBD
 ***********************************************/
static void app_Debounce_IncreaseDbncCounter(T_UBYTE lub_ButtonNumber)
{
	/* Check if the counter hasn't reached its max limit */
	if(raub_ButtonDebounceCounters[lub_ButtonNumber] >= APP_BTNDBNC_DBNC_VALID_COUNT)
	{//Counter is in the limit
		/* Valid State */
		rae_ButtonsState[lub_ButtonNumber] = BUTTON_PRESSED;
	}
	else
	{//Counter has not reached a valid value
		raub_ButtonDebounceCounters[lub_ButtonNumber]++;
	}
}

/***********************************************
 * Function Name: app_Debounce_ClearDbncCounter
 * Description: TBD
 ***********************************************/
static void app_Debounce_ClearDbncCounter(T_UBYTE lub_ButtonNumber)
{
	/* Clear debounce counter */
	raub_ButtonDebounceCounters[lub_ButtonNumber] = 0U;
	/* Clear button state */
	rae_ButtonsState[lub_ButtonNumber] = BUTTON_UNPRESSED;
}

/***********************************************
 * Function Name: app_Debounce_Actions
 * Description: TBD
 ***********************************************/
static void app_Debounce_Actions()
{
	T_UBYTE lub_i;
	/* Check internal button states */
	for(lub_i = 0; lub_i < NUMBERS_BUTTON; lub_i++)
	{
		/* If button has a valid press, then perform the corresponding actions*/
		if(rae_ButtonsState[lub_i] == BUTTON_PRESSED)
		{
			switch(lub_i)
			{
			/*Actions for BUTTON 0*/
			case BUTTON0:
			{
				if(rub_flagPIT0 == TRUE)
				{
					app_RotabitCounterBackward();
					PIT_ClearStatusFlags(PIT, 1, kPIT_TimerFlag);
					rub_flagPIT0 = FALSE;
				}
			}break;
			/*Actions for BUTTON 1*/
			case BUTTON1:
			{
				if(rub_flagPIT0 == TRUE)
				{
					app_RotabitCounterFoward();
					PIT_ClearStatusFlags(PIT, 1, kPIT_TimerFlag);
					rub_flagPIT0 = FALSE;
				}
			}break;
			/*Actions for not valid BUTTON*/
			default:
			{
				/* Do Nothing */
			}break;
			}
		}
		else
		{//Button is not pressed, perform the corresponding action
			switch(lub_i)
			{
			/*Actions for BUTTON 0*/
			case BUTTON0:
			{

			}break;
			/*Actions for BUTTON 1*/
			case BUTTON1:
			{

			}break;
			/*Actions for not valid BUTTON*/
			default:
			{
				/* Do Nothing */
			}break;
			}
		}
	}
}


