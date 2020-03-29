/*
 * app_TrackIndicator.h
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#ifndef APP_TRACKINDICATOR_H_
#define APP_TRACKINDICATOR_H_

#include "../source/typedef_macros.h"
#include "../board/pin_mux.h"
#include "../CMSIS/MKL25Z4.h"

extern void app_TrackIndicatorOutput(T_UBYTE OutputVAlue);
extern void app_TrackNumber(void);
/* Definiendo los puertos y pines para el indicador del Track */
#define TrackPORT 				PORTC
#define TrackGPORT				GPIOC
#define TrackPIN0				0u
#define TrackPIN1				1u

#endif /* APP_TRACKINDICATOR_H_ */
