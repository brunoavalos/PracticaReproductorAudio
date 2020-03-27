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

void PIT_DriverIRQHandler(void)
{
	rub_flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);
	rub_flagPIT1 = PIT_GetStatusFlags(PIT, kPIT_Chnl_1);

	if(rub_flagPIT1)
	{
		PIT_ClearStatusFlags(PIT, 1, kPIT_TimerFlag);
	}
	if(rub_flagPIT0)
	{

		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
	}
	else
	{ /* Nothing else */}
}

#endif /* APP_PITFLAG_C_ */
