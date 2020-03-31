/*
 * app_Reproductor.c
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */

/* Archivo de cabecera del reproductor */

/******************************************
 * Header
 ******************************************/

#include "app_Reproductor.h"

/******************************************
 * Code
 ******************************************/
void app_ReproductorTasks(void)
{
	app_Debounce();
	app_ReproductioFuntion();
}

void app_ReproductorFuntion(void)
{
	T_STATIC_STATES BUTTON_STATIC_STATE;
	switch(BUTTON_STATIC_STATE)
	{
		case STOP:
		{
			lub_ActualTrack = 0u;
			app_TrackIndicatorOutput(lub_ActualTrack);
		}
		break;
		case PLAY:
		{
			app_FOWARD();
		}break;
		case PAUSE:
		{

		}break;
		default:
		{

		}
	}
}

void app_Debounce(void)
{

}
/***********************************************
 * Function Name:
 * Description:
 ***********************************************/
