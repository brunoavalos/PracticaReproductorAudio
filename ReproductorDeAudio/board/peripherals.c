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

void app_PIT_Init(void);
void app_ADC_Init(void);
void app_PWM_Init(T_UBYTE updatedDutycycle);

void BOARD_InitBootPeripherals(void) {
	app_PIT_Init();

	/* The user initialization should be placed here */
}

void app_PIT_Init(void)
{

	/* Inicialización del PIT */
	pit_config_t PIT_Config;
    PIT_GetDefaultConfig(&PIT_Config);
    PIT_Init(PIT, &PIT_Config);
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(1000, PIT_CLK_SRC_HZ_HP));
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_StopTimer(PIT, kPIT_Chnl_0);
    EnableIRQ(PIT_IRQn);
    PIT_StartTimer(PIT, kPIT_Chnl_0);
}

void app_ADC_Init(void)
{
	/* ADC default configuration */
	adc16_config_t adc16ConfigStruct;
	adc16_channel_config_t adc16ChannelConfigStruct;
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
	/* Autocalibration */
	adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
	ADC16_Init(ADC16_BASE, &adc16ConfigStruct);
	adc16ChannelConfigStruct.channelNumber = ADC16_USER_CHANNEL;

}

T_UWORD app_ADC_Value(void)
{
	T_UWORD luw_ADCValue = 0u;
	luw_ADCValue = ADC16_GetChannelConversionValue(ADC16_BASE, ADC16_CHANNEL_GROUP);

	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC16_BASE, ADC16_CHANNEL_GROUP)))
	        {
	        }
	return luw_ADCValue;
}

void app_PWM_Init(T_UBYTE updatedDutycycle)
{
	/* PWM Default configuration */
	tpm_config_t tpmInfo;

	tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;
	tpm_chnl_pwm_signal_param_t tpmParam;
		/* Configure tpm params with frequency 24kHZ */
			tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
			tpmParam.level = kTPM_LowTrue;
			tpmParam.dutyCyclePercent = updatedDutycycle;


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

void app_PWM_Value(T_UBYTE updatedDutycycle)
{

	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,updatedDutycycle);
}
