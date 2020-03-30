/*
 * app_TrackIndicatior.c
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#include "app_TrackIndicator.h"
#include "app_ReadInput.h"

static T_UBYTE lub_ActualTrack = 0u;

extern T_UBYTE lub_ButtonState[NUMBERS_BUTTON];

	void app_NextTrack(void) {
		if (lub_ActualTrack > 3) {
			lub_ActualTrack = 0;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		if (lub_ButtonState[1] == FALSE) { //NEXT

			lub_ActualTrack++;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		else {
			/*Do nothing*/
		}

	}

	void app_PreviousTrack(void) {
		if (lub_ButtonState[0] == FALSE) {
			lub_ActualTrack = lub_ActualTrack - 1;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		if (lub_ActualTrack < 0) {
			lub_ActualTrack = 3;
			app_TrackIndicatorOutput(lub_ActualTrack);
		} else {
			/* Do nothing */
		}

	}

void app_TrackIndicatorOutput(T_UBYTE OutputVAlue)
{
	TrackGPORT->PDOR=OutputVAlue;

}
