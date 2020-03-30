/*
 * app_PITFlag.h
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#ifndef APP_PITFLAG_H_
#define APP_PITFLAG_H_

#include "../source/typedef_macros.h"
#include "../drivers/fsl_pit.h"

extern volatile T_UBYTE rub_flagPIT0;
extern volatile T_UBYTE rub_flagPIT1;
extern volatile T_UBYTE rub_flagPIT2;
extern void app_InterruptFlag(void);

#endif /* APP_PITFLAG_H_ */
