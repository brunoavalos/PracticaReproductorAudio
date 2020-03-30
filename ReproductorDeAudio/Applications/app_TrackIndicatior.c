/*
 * app_TrackIndicatior.c
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#include "app_TrackIndicator.h"
#include "app_ReadInput.h"

void app_TrackNumber(void){

extern T_UBYTE lub_ButtonState[NUMBERS_BUTTON];
/*T_UBYTE rub_2ndBtn_flag = 0;*/
T_UBYTE lub_TrackNumber;
/*T_UBYTE lub_PrevTrack = 0u;*/
T_UBYTE lub_ActualTrack = 0u;
//STOP
//PLAY

		lub_TrackNumber = lub_ActualTrack;

		if(lub_ActualTrack < 0)
		{
			lub_ActualTrack = 3;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		if(lub_ActualTrack > 3)
		{
			lub_ActualTrack = 0;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		if(lub_ButtonState[1] == FALSE)
		{//NEXT

			lub_ActualTrack++;
			app_TrackIndicatorOutput(lub_ActualTrack);

		}
		if(lub_ButtonState[2] == FALSE)
		{
			lub_ActualTrack = lub_ActualTrack- 1;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		else
		{
			/*Do nothing*/
		}

}

void app_TrackIndicatorOutput(T_UBYTE OutputVAlue)
{
	TrackGPORT->PDOR=OutputVAlue;

}
