/*
 * main.c
 *
 *  Created on: Mar 21, 2020
 *      Author: dario
 */

/* Librerias */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
#include "typedef_macros.h"
#include "Macros.h"
#include "Applications/app_RotabitCounter.h"
#include "Applications/app_ReadInput.h"
#include "Applications/app_PITFlag.h"
#include "Applications/app_TrackIndicator.h"
#include "Applications/app_Debounce.h"

/* Variables Globales */

T_UBYTE lub_counterFlag = 0u;

/* Declaración de funciones */

int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	BOARD_BootClockRUN();

	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	app_PWM_Init();

	while (1) {
		app_ADC_Task();
		app_PWMProcentValue();
		app_PWM_Value();
		if(rub_flagPIT0 == TRUE)
		{
			app_InterruptFlag();
			app_DebounceTask();
			rub_flagPIT0 = FALSE;
		}
	}
	return 0;

}

