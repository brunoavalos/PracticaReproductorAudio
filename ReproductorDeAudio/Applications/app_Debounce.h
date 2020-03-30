/*
 * app_Debounce.h
 *
 *  Created on: Mar 26, 2020
 *      Author: dario
 */


#include "../source/typedef_macros.h"
#include "app_RotabitCounter.h"
#include "app_TrackIndicator.h"


#ifndef APP_DEBOUNCE_H_
#define APP_DEBOUNCE_H_

/******************************************
 * Macros
 ******************************************/

#define NUMBERS_BUTTON 					((T_UBYTE)3)
#define APP_BTNDBNC_DBNC_VALID_COUNT	((T_UWORD)3000U)
#define NORMAL_BUTTON_COUNT				((T_UBYTE)400U)
#define NUMBER_COUNTER					((T_UBYTE)2U)
#define MAX_NUMBER_COUNTER				((T_UBYTE)5U)
#define MIN_NUMBER_COUNTER				((T_UBYTE)3U)


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
	BUTTON_PRESSED,
	BUTTON_LONGPRESSED
}T_BUTTON_STATES;


typedef enum
{
	BUTTON0,
	BUTTON1,
	BUTTON2
}Final_Button_State;




#endif /* APP_DEBOUNCE_H_ */
