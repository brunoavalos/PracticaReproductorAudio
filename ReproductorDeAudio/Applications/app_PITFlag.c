/*
 * app_PITFlag.c
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#ifndef APP_PITFLAG_C_
#define APP_PITFLAG_C_


#include "app_PITFlag.h"

volatile T_UBYTE rub_flagPIT0 = 0u;
volatile T_UBYTE rub_flagPIT1 = 0u;
volatile T_UBYTE rub_flagPIT2 = 0u;
volatile T_UBYTE rub_InterruptFlag = 0u;
T_UBYTE rub_100msCounter=0u;

void PIT_DriverIRQHandler(void) {
	rub_flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);
	rub_flagPIT1 = PIT_GetStatusFlags(PIT, kPIT_Chnl_1);

	if (rub_flagPIT1) {
				PIT_ClearStatusFlags(PIT, 1, kPIT_TimerFlag);
				app_InterruptFlag();
				rub_InterruptFlag = TRUE;
			}
			if (rub_flagPIT0) {

				PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
			}
			else
			{
				/* Do nothing*/
			}

}

void app_InterruptFlag(void) {

	if (rub_InterruptFlag == TRUE) {
		if (rub_100msCounter >= 5) {
			rub_flagPIT2 = TRUE;
			rub_100msCounter = 0u;
			rub_InterruptFlag = FALSE;
		} else {
			rub_100msCounter = rub_100msCounter + 1;

		}
	}
}


#endif /* APP_PITFLAG_C_ */
