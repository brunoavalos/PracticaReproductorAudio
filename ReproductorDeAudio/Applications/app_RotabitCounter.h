/*
 * app_RotabitCounter.h
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#ifndef APP_ROTABITCOUNTER_H_
#define APP_ROTABITCOUNTER_H_

#include "fsl_gpio.h"
#include "typedef_macros.h"

extern T_UBYTE lub_Output;

extern void app_RotabitCounterFoward(void);
extern void app_RotabitCounterBackward(void);

#endif /* APP_ROTABITCOUNTER_H_ */
