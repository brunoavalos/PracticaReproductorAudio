/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Practica2_UDG.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
pit_config_t My_PIT;
volatile uint32_t flagPIT0;
#define PIT_CLK_SRC_HZ_HP ((uint64_t)24000000)
#define OUTPT_OFF 0x01u
#define OUTPT_ON 0x00u
uint8_t Output = 0;
/*
 * @brief   Application entry point.
 */
//Declarando uniones


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    PIT_GetDefaultConfig(&My_PIT);

    PIT_Init(PIT, &My_PIT);

    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(1000, PIT_CLK_SRC_HZ_HP));

    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

    PIT_StopTimer(PIT, kPIT_Chnl_0);

    Output = OUTPT_ON;

    EnableIRQ(PIT_IRQn);

    PIT_StartTimer(PIT, kPIT_Chnl_0);
    /* Force the counter to be placed into memory. */
    //volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	if(flagPIT0 == 1)
    	{
    		if(Output == 0)
    		{
    			Output = 1;
    		}
    		else
    		{
    			Output = Output << 1;
    		}
    		flagPIT0 = 0;
    	}
    	if(Output > 8)
    	{
    		Output = 0;
    	}
    	else
    	{
    	GPIOB->PDOR=Output;
    	}
    }
    return 0 ;
}

void PIT_DriverIRQHandler(void)
{
	flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(flagPIT0)
	{
		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
	}
}
