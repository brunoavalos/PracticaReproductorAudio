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
 * @file    Breath_LED_PWM.c
 * @brief   Application entry point.
 */
/*******************************************************************************
 * Include Files
 ******************************************************************************/
#include "stdtypedef.h"
#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_tpm.h"
#include "fsl_uart.h"
#include "fsl_adc16.h"
#include "fsl_pit.h"
#include "fsl_gpio.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "Macros.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
pit_config_t My_PIT;
volatile uint32_t flagPIT0;
volatile uint8_t counterFlag = 0;
volatile uint8_t updatedDutycycle = 0U;
volatile uint8_t counter = 0U;
volatile uint8_t TPM_clock = 0U;
uint8_t Output = 0;

 /* UART Variables */
uint8_t txbuff[] = "Ejemplo\r\n";

/******************************************
* Private Variables
******************************************/

static T_UWORD ruw_ADCValue = 0u;
static T_UBYTE rub_ConversionInProgressFlag = FALSE;


/******************************************
 * Private Prototypes
 ******************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/***********************************************
 * Function Name: app_ADC_Init
 * Description: TBD
 ***********************************************/
void app_UART_Init(void)
{
	    uart_config_t config;
	    UART_GetDefaultConfig(&config);
	    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	    config.enableTx = true;
	    config.enableRx = false;

	    UART_Init(UART_SELECTION, &config, UART_CLK_FREQ);

}
void app_ADC_Init(void)
{
	adc16_config_t ls_ADCConfig;

	//Initialize structure with default values
	ADC16_GetDefaultConfig(&ls_ADCConfig);

	//Init ADC Module
	ADC16_Init(ADC0, &ls_ADCConfig);

	//Disable Hardware Trigger
	ADC16_EnableHardwareTrigger(ADC0, FALSE); /* Make sure the software trigger is used. */

	//Perform Autocalibration
	(void)ADC16_DoAutoCalibration(ADC0);
}

/***********************************************
 * Function Name: app_ADC_Trigger
 * Description: TBD
 ***********************************************/
static void app_ADC_Trigger(void)
{
	adc16_channel_config_t ls_ChannelConfig;

	//Channel Selection
	ls_ChannelConfig.channelNumber = ADC_CHANNEL;

	//Disable Interrupt when Conversion is completed
	ls_ChannelConfig.enableInterruptOnConversionCompleted = FALSE;

	//Disable Differential Conversion
	ls_ChannelConfig.enableDifferentialConversion = FALSE;

	ADC16_SetChannelConfig(ADC0, ADC_CHANNEL_GROUP, &ls_ChannelConfig);
}

/***********************************************
 * Function Name: app_ADC_IsConversionCompleted
 * Description: TBD
 ***********************************************/
static T_UBYTE app_ADC_IsConversionCompleted(void)
{
	T_UBYTE lub_Return;

	lub_Return = FALSE;

	//Check if Conversion was completed
	if(kADC16_ChannelConversionDoneFlag &
			ADC16_GetChannelStatusFlags(ADC0, ADC_CHANNEL_GROUP))
	{
		//Conversion Completed
		lub_Return = TRUE;
	}
	else
	{
		//Conversion not completed
		lub_Return = FALSE;
	}

	return lub_Return;
}

/***********************************************
 * Function Name: app_ADC_GetValue
 * Description: TBD
 ***********************************************/
static T_UWORD app_ADC_GetValue(void)
{
	//Return Last Conversion Value
	return ADC16_GetChannelConversionValue(ADC0, ADC_CHANNEL_GROUP);
}

/***********************************************
 * Function Name: app_ADC_Task
 * Description: TBD
 ***********************************************/
void app_ADC_Task(void)
{
	//Check if a conversion is in progress
	if(TRUE == rub_ConversionInProgressFlag)
	{
		//Check if Conversion was completed
		if(TRUE == app_ADC_IsConversionCompleted())
		{
			//Store the ADC Value
			ruw_ADCValue = app_ADC_GetValue();

			//Clear conversion in progress flag
			rub_ConversionInProgressFlag = FALSE;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		//Trigger the ADC Conversion
		app_ADC_Trigger();

		//Set Conversion in progress flag
		rub_ConversionInProgressFlag = TRUE;
	}
}





void app_PWM_Init(void)
{
	/* PWM Default configuration */
	tpm_config_t tpmInfo;
	tpm_chnl_pwm_signal_param_t tpmParam;
	tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;

	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	tpmParam.level = pwmLevel;
	tpmParam.dutyCyclePercent = updatedDutycycle;

	/* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
	CLOCK_SetTpmClock(1U);

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);
	TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
	TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);
}

void app_PWM_Edge()
{
	/* Disable channel output before updating the dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

	/* Start channel output with updated dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_LowTrue);
}

void app_PWM_UpdateValue(void)
{
	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,updatedDutycycle);
}

void app_PIT_Init(void)
{
	PIT_GetDefaultConfig(&My_PIT);
	PIT_Init(PIT, &My_PIT);
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(1000, CLK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	PIT_StopTimer(PIT, kPIT_Chnl_0);
	Output = OUTPT_ON;
	EnableIRQ(PIT_IRQn);
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}

void PIT_DriverIRQHandler(void)
{
	static unsigned long ruw_TickCounter = 0U;
	flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(ruw_TickCounter > 9000)
	{
		ruw_TickCounter = 0U;
		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
	}
	else
	{
		ruw_TickCounter = ruw_TickCounter + 1;
	}
}




/*******************************************************************************
 * Code
 ******************************************************************************/


int main(void) {


	unsigned long uw_ADCCounter = 0U;
  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    app_UART_Init();
    app_PIT_Init();
    app_PWM_Init();
    app_PWM_Edge();
    app_ADC_Init();

    while(1)
    {

    	if(flagPIT0 == 1)
    	{

    			if(uw_ADCCounter > ruw_ADCValue/768U)
    			{
					if((counter <= 10U) && (counterFlag == 1U))
					{
						if(counter == 0U)
						{
							counterFlag = 0U;
							uw_ADCCounter = 0U;
						}
						else
						{
							counter = counter - 1;
							uw_ADCCounter = 0U;
							flagPIT0 = 0;
						}
					}
					if(counterFlag == 0U)
					{
						if(counter == 10U)
						{
							counterFlag = 1U;
							uw_ADCCounter = 0U;
						}
						else
						{
							counter = counter + 1;
							flagPIT0 = 0;
							uw_ADCCounter = 0U;
						}
					}
					else
					{
					}
    			}
    			else
    			{
    				uw_ADCCounter = uw_ADCCounter + 1;
    				app_PWM_UpdateValue();
    				app_ADC_Task();

    				flagPIT0 = 0;
    			}
    	}
    	else
    	{
    		updatedDutycycle = counter;
    		UART_WriteBlocking(UART_SELECTION, txbuff, sizeof(txbuff) - 1);
    	}


    }
    return 0 ;
}
