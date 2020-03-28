/*
 * Copyright 2017-2020 NXP
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

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v1.0
* BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/**
 * @file    peripherals.c
 * @brief   Peripherals initialization file.
 */



/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/
#include <stdio.h>
#include "peripherals.h"
#include "Macros.h"
#include "fsl_pit.h"
#include "board.h"
#include "fsl_adc16.h"
#include "fsl_tpm.h"
#include "fsl_lpsci.h"
#include "clock_config.h"
#include "fsl_device_registers.h"
#include "typedef_macros.h"
#include "pin_mux.h"
/**
 * @brief Set up and initialize all required blocks and functions related to the peripherals hardware.
 */

 /******************************************
 * Private Variables
 ******************************************/

static T_UBYTE rub_ConversionInProgressFlag = FALSE;
T_UWORD ruw_ADCValue = 0u;
T_UBYTE lub_PWMPorcentValue = 0;

 /******************************************
 * Private Prototypes
 ******************************************/
static void app_ADC_Trigger(void);
static T_UBYTE app_ADC_IsConversionCompleted(void);
static T_UWORD app_ADC_GetValue(void);
void app_PIT_Init(void);
void app_ADC_Init(void);
void app_PWM_Init(void);
static void app_ADC_Trigger(void);
T_UBYTE app_PWMProcentValue(void);

void BOARD_InitBootPeripherals(void) {
	app_PIT_Init();
	app_ADC_Init();
	app_ADC_Trigger();

	/* The user initialization should be placed here */
}

/***********************************************
 * Function Name: app_PIT_init
 * Description: TBD
 ***********************************************/

void app_PIT_Init(void)
{

	/* Inicialización del PIT */
	/* Declaracion del primer canal PIT*/
	pit_config_t PIT_Config;
    PIT_GetDefaultConfig(&PIT_Config);
    PIT_Init(PIT, &PIT_Config);
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(CLK_100ms, PIT_CLK_SRC_HZ_HP));
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_StopTimer(PIT, kPIT_Chnl_0);
    EnableIRQ(PIT_IRQn);
    PIT_StartTimer(PIT, kPIT_Chnl_0);

    /* Declaracion del segundo canal PIT*/
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_1, MSEC_TO_COUNT(CLK_500ms, PIT_CLK_SRC_HZ_HP));
    PIT_EnableInterrupts(PIT, kPIT_Chnl_1, kPIT_TimerInterruptEnable);
    PIT_StopTimer(PIT, kPIT_Chnl_1);
    EnableIRQ(PIT_IRQn);
    PIT_StartTimer(PIT, kPIT_Chnl_1);


}

/***********************************************
 * Function Name: app_PWM_init
 * Description: TBD
 ***********************************************/

void app_PWM_Init(void)
{
	/* PWM Default configuration */
	tpm_config_t tpmInfo;

	tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;
	tpm_chnl_pwm_signal_param_t tpmParam;
	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	tpmParam.level = pwmLevel;
	tpmParam.dutyCyclePercent = 0u; /* Inizial Value PWM */


	/* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
	CLOCK_SetTpmClock(1U);

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);
	TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
	TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);


	/* Disable channel output before updating the dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

	/* Start channel output with updated dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_LowTrue);

}

/***********************************************
 * Function Name: app_PWM_Value
 * Description: TBD
 ***********************************************/

void app_PWM_Value(void)
{

	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm, lub_PWMPorcentValue);
}

/***********************************************
 * Function Name: app_ADC_init
 * Description: TBD
 ***********************************************/

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
	ls_ChannelConfig.channelNumber = APP_ADC_CHANNEL;

	//Disable Interrupt when Conversion is completed
	ls_ChannelConfig.enableInterruptOnConversionCompleted = FALSE;

	//Disable Differential Conversion
	ls_ChannelConfig.enableDifferentialConversion = FALSE;

	ADC16_SetChannelConfig(ADC0, APP_ADC_CHANNEL_GROUP, &ls_ChannelConfig);
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
			ADC16_GetChannelStatusFlags(ADC0, APP_ADC_CHANNEL_GROUP))
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
	return ADC16_GetChannelConversionValue(ADC0, APP_ADC_CHANNEL_GROUP);
}


/***********************************************
 * Function Name: app_PWMProcentValue
 * Description: Valor de PWM expresado en
 * porcentaje con una resolucion de 10% en cada
 * uno de los pasos
 ***********************************************/

T_UBYTE app_PWMProcentValue(void)
{


		if(ruw_ADCValue <= 410)
		{
			lub_PWMPorcentValue = 0u;
		}
		else if((ruw_ADCValue > 410) && (ruw_ADCValue < 820))
		{
			lub_PWMPorcentValue = 10u;
		}
		else if((ruw_ADCValue > 820) && (ruw_ADCValue < 1230))
		{
			lub_PWMPorcentValue = 20u;
		}
		else if((ruw_ADCValue > 1230) && (ruw_ADCValue < 1640))
		{
			lub_PWMPorcentValue = 30u;
		}
		else if((ruw_ADCValue > 1640) && (ruw_ADCValue < 2050))
		{
			lub_PWMPorcentValue = 40u;
		}
		else if((ruw_ADCValue > 2050) && (ruw_ADCValue < 2460))
		{
			lub_PWMPorcentValue = 50u;
		}
		else if((ruw_ADCValue > 2460) && (ruw_ADCValue < 2870))
		{
			lub_PWMPorcentValue = 60u;
		}
		else if((ruw_ADCValue > 2870) && (ruw_ADCValue < 3280))
		{
			lub_PWMPorcentValue = 70u;
		}
		else if((ruw_ADCValue > 3280) && (ruw_ADCValue < 3690))
		{
			lub_PWMPorcentValue = 80u;
		}
		else if((ruw_ADCValue > 3690) && (ruw_ADCValue < 4100))
		{
			lub_PWMPorcentValue = 90u;
		}
		else
		{
			lub_PWMPorcentValue = 100u;
		}
		return lub_PWMPorcentValue;
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
