/*
 * app_TrackIndicatior.c
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#include "app_TrackIndicator.h"
#include "app_ReadInput.h"

void app_TrackNumber(void){

extern T_UBYTE lub_ButtonState[2];
/*T_UBYTE rub_2ndBtn_flag = 0;*/
T_UBYTE lub_TrackNumber;
/*T_UBYTE lub_PrevTrack = 0u;*/
T_UBYTE lub_ActualTrack = 0u;
//STOP
//PLAY

	while(lub_TrackNumber <= 3)
	{

		if(lub_ActualTrack < 0)
		{
			lub_ActualTrack = 3;
		}

		lub_TrackNumber = lub_ActualTrack;
		app_TrackIndicatorOutput(lub_TrackNumber);

		if(lub_ButtonState[1] == FALSE)
		{//NEXT

			lub_ActualTrack++;

		}else if(lub_ButtonState[2] == FALSE)
		{

			lub_ActualTrack = lub_ActualTrack-1;

		}else{/*Do nothing*/}

	}

}

void app_TrackIndicatorOutput(T_UBYTE OutputVAlue)
{
	TrackGPORT->PDOR=OutputVAlue;

}
