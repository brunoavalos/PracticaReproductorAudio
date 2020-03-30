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
static void app_Debounce_IncreaseDbncCounter(void);
static void app_Debounce_ClearDbncCounter(void);
static void app_Debounce_Actions();

/******************************************
 * Variables
 ******************************************/
T_BUTTON_STATES rae_ButtonsState[NUMBERS_BUTTON];
T_UWORD	raub_ButtonDebounceCounters[NUMBERS_BUTTON];
T_UBYTE lub_i;
T_UBYTE rub_Play;
T_UBYTE rub_ButtonPlay;
T_UBYTE rub_PlayRotabit;
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

	/* Check the buttons state */
	for(lub_i = 0; lub_i < NUMBERS_BUTTON;lub_i++)
	{//Check for each button
		if(lub_ButtonState[lub_i] == FALSE)
		{//Button pressed in HW
			app_Debounce_IncreaseDbncCounter();
		}
		else
		{//Button unpressed in SW
			app_Debounce_ClearDbncCounter();
		}
	}
}

/***********************************************
 * Function Name: app_Debounce_IncreaseDbncCounter
 * Description: TBD
 ***********************************************/
static void app_Debounce_IncreaseDbncCounter(void) {
	if (rub_flagPIT0 == TRUE) {
		/* Check if the counter hasn't reached its max limit */
		if ((raub_ButtonDebounceCounters[lub_i] > MIN_NUMBER_COUNTER)
				&& (raub_ButtonDebounceCounters[lub_i] < MAX_NUMBER_COUNTER)) {
			if (raub_ButtonDebounceCounters[2] == FALSE) {
				rub_ButtonPlay = TRUE;
				rae_ButtonsState[lub_i] = BUTTON_LONGPRESSED;
				raub_ButtonDebounceCounters[lub_i] = 0u;
			} else {
				rae_ButtonsState[lub_i] = BUTTON_LONGPRESSED;
				raub_ButtonDebounceCounters[lub_i] = 0u;
			}
		}
		if (raub_ButtonDebounceCounters[lub_i] > NUMBER_COUNTER) { //Counter is in the limit
			/* Valid State */
			if (raub_ButtonDebounceCounters[2] == FALSE) {
				rub_ButtonPlay = TRUE;
				rae_ButtonsState[lub_i] = BUTTON_PRESSED;
				raub_ButtonDebounceCounters[lub_i] = 0u;
			} else {
				rae_ButtonsState[lub_i] = BUTTON_PRESSED;
				raub_ButtonDebounceCounters[lub_i] = 0u;
			}
		} else { //Counter has not reached a valid value
			raub_ButtonDebounceCounters[lub_i]++;
		}
		rub_flagPIT0 = FALSE;
	}
}

/***********************************************
 * Function Name: app_Debounce_ClearDbncCounter
 * Description: TBD
 ***********************************************/
static void app_Debounce_ClearDbncCounter(void)
{
	/* Clear debounce counter */
	raub_ButtonDebounceCounters[lub_i] = 0U;
	/* Clear button state */
	rae_ButtonsState[lub_i] = BUTTON_UNPRESSED;
}

/***********************************************
 * Function Name: app_Debounce_Actions
 * Description: TBD
 ***********************************************/
static void app_Debounce_Actions(void) {
	T_UBYTE lub_x = 0;

	/* Check internal button states */
	while (lub_x < NUMBERS_BUTTON) {

		/* If button has a valid press, then perform the corresponding actions*/
		if (rae_ButtonsState[lub_x] == BUTTON_PRESSED) {
			switch (lub_x) {
			/*Actions for BUTTON 0*/
			case 0: {
				if ((rub_flagPIT1 == TRUE) && (rub_Play == TRUE)) {
					app_PreviousTrack();
					rub_flagPIT1 = FALSE;
				}
			}
				break;
				/*Actions for BUTTON 1*/
			case 1: {
				if ((rub_flagPIT1 == TRUE) && (rub_Play == TRUE)) {
					app_NextTrack();
					rub_flagPIT1 = FALSE;
				}

			}
				break;
			case 2: {
				if ((rub_PlayRotabit == TRUE) && (rub_Play == TRUE)
						&& (rub_ButtonPlay = TRUE)) {
					rub_Play = FALSE;
				} else {
					rub_Play = TRUE;
				}
			}
				break;
				/*Actions for not valid BUTTON*/
			default: {
				/* Do Nothing */
			}
				break;

			}
			if (rae_ButtonsState[lub_x] == BUTTON_LONGPRESSED) {
				switch (lub_x) {
				/*Actions for BUTTON 0*/
				case 0: {
					if ((rub_flagPIT2 == TRUE) && (rub_Play == TRUE)) {
						app_RotabitCounterBackward();
						rub_flagPIT2 = FALSE;
					}
				}
					break;
					/*Actions for BUTTON 1*/
				case 1: {
					if ((rub_flagPIT2 == TRUE) && (rub_Play == TRUE)) {

						app_RotabitCounterFoward();
						rub_flagPIT2 = FALSE;
					}

				}
					break;
				case 2: {

				}
					break;
					/*Actions for not valid BUTTON*/
				default: {
					/* Do Nothing */
				}
					break;

				}
			}
		} else { //Button is not pressed, perform the corresponding action
			switch (lub_x) {
			/*Actions for BUTTON 0*/
			case BUTTON0: {

			}
				break;
				/*Actions for BUTTON 1*/
			case BUTTON1: {
				if ((rub_flagPIT1 == TRUE) && (rub_Play == TRUE)) {
					app_RotabitCounterFoward();
					rub_PlayRotabit = TRUE;
					rub_flagPIT1 = FALSE;
				} else {
					/* Do nothing */
				}

			}
				break;
			case BUTTON2: {

			}
				break;
				/*Actions for not valid BUTTON*/
			default: {

			}
				break;
			}
		}
		lub_x++;
	}
}




