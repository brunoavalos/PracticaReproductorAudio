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


/* Variables Globales */

volatile T_UBYTE rub_flagPIT0;

T_UBYTE lub_counterFlag = 0u;

/* Declaración de funciones */


int main(void)
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_BootClockRUN();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    app_PWM_Init();
    while(1)
    {

    		if(rub_flagPIT0 == 1)
    		    	{
//    					app_RotabitCounterForward();
    					app_RotabitCounterBackward();
						rub_flagPIT0 = 0;
    		    	}
    		else
    		{
    		app_ADC_Task();
    		app_PWMProcentValue();
        	app_PWM_Value();
    		}


    }
    return 0;

}

void PIT_DriverIRQHandler(void)
{
	rub_flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(rub_flagPIT0)
	{
		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
	}
	else
	{ /* Nothing else */}
}
