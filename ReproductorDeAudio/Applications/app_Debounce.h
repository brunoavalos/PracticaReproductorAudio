/*
 * app_Debounce.h
 *
 *  Created on: Mar 26, 2020
 *      Author: dario
 */


#include "../source/typedef_macros.h"
#include "app_RotabitCounter.h"


#ifndef APP_DEBOUNCE_H_
#define APP_DEBOUNCE_H_

/******************************************
 * Macros
 ******************************************/

#define NUMBERS_BUTTON 					((T_UBYTE)2)
#define APP_BTNDBNC_DBNC_VALID_COUNT	((T_UWORD)3000U)


/******************************************
 * Prototypes
 ******************************************/


extern void app_Debounce_Init(void);
extern void app_Debounce_TaskMngr(void);

/******************************************
 * Type definitions
 ******************************************/
typedef enum
{
	BUTTON_UNPRESSED,
	BUTTON_PRESSED
}T_BUTTON_STATES;

enum
{
	BUTTON0,
	BUTTON1,
	N_BUTTONS
};




#endif /* APP_DEBOUNCE_H_ */
