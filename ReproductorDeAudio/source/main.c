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



/* Variables Globales */

volatile T_UBYTE rub_flagPIT0;
T_UBYTE lub_counter = 0u;
T_UBYTE lub_Output = 0u;
T_UBYTE lub_counterFlag = 0u;

/* Declaración de funciones */



/* Contador de anillo */


void Breath_LED(void)
{
	    	if(rub_flagPIT0 == 1)
	    	{
	    			if((lub_counter <= 10U) && (lub_counterFlag == 1U))
	    			{
	    				if(lub_counter == 0U)
	    				{
	    					lub_counterFlag = 0U;
	    				}
	    				else
	    				{
	    					lub_counter = lub_counter - 1;
	    					rub_flagPIT0 = 0;
	    				}
	    			}
	    			if(lub_counterFlag == 0U)
	    			{
	    				if(lub_counter == 10U)
	    				{
	    					lub_counterFlag = 1U;
	    				}
	    				else
	    				{
	    					lub_counter = lub_counter + 1;
	    					rub_flagPIT0 = 0;
	    				}
	    			}
	    			else
	    			{}
	    	}
	    	else
	    	{}
//	    	app_PWM_Value(lub_counter);

}

void Counter_Foward(void)
{

	GPIOB->PDOR=lub_Output;
	if(lub_Output == 0)
	{
	   lub_Output = 1;

	}
	else
	{
	   if(lub_Output == 8)
	   {
		   lub_Output = 0;
	   }
	   else
	   {
	   lub_Output = lub_Output << 1;
	   }
	}
}
void Counter_Backward(void)
{
	GPIOB->PDOR=lub_Output;
		if(lub_Output == 0)
		{
		   lub_Output = 8;

		}
		else
		{
		   if(lub_Output == 2)
		   {
			   lub_Output = 1;
		   }
		   else
		   {
		   lub_Output = lub_Output >> 1;
		   }
		}
}


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
    	app_ADC_Task();
    		if(rub_flagPIT0 == 1)
    		    	{
    					Breath_LED();
//    					Counter_Foward();
    					Counter_Backward();
    					rub_flagPIT0 = 0;


    		    	}
    		else
    		{/* Nothing to do */}


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
