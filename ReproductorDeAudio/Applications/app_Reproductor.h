/*
 * app_Reproductor.h
 *
 *  Created on: 31 mar. 2020
 *      Author: Darío
 */

#ifndef APP_REPRODUCTOR_H_
#define APP_REPRODUCTOR_H_

#include "app_TrackIndicator.h"
#include "app_RotabitCounter.h"

/******************************************
 * Type definitions
 ******************************************/
typedef enum
{
	PRESSED,
	LONG_PRESSED
}T_STATES;

typedef enum{
	STOP,
	PLAY,
	PAUSE
}T_STATIC_STATES;

#endif /* APP_REPRODUCTOR_H_ */
