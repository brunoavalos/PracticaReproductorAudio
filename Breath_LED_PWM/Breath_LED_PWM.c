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

#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_tpm.h"
#include "fsl_adc16.h"
#include "fsl_pit.h"
#include "fsl_gpio.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_TPM_BASEADDR TPM2
#define BOARD_TPM_CHANNEL 1U

/* Interrupt to enable and flag to read; depends on the TPM channel used */
#define TPM_CHANNEL_INTERRUPT_ENABLE kTPM_Chnl1InterruptEnable
#define TPM_CHANNEL_FLAG kTPM_Chnl1Flag

/* Interrupt number and interrupt handler for the TPM instance used */
#define TPM_INTERRUPT_NUMBER TPM2_IRQn
#define TPM_LED_HANDLER TPM2_IRQHandler

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)

/* Select ADC */
#define DEMO_ADC16_BASE ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U /*PTE20, ADC0_SE0 */
#define DEMO_ADC16_IRQn ADC0_IRQn
#define DEMO_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler

/* PIT */
#define PIT_CLK_SRC_HZ_HP ((uint64_t)24000000)
#define CLK ((uint64_t)1000000)
#define OUTPT_OFF 0x01u
#define OUTPT_ON 0x00u
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
uint8_t ADCValue = 0U;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void app_ADC_init(void)
{
	/* ADC default configuration */
	adc16_config_t adc16ConfigStruct;
	adc16_channel_config_t adc16ChannelConfigStruct;
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
	/* Autocalibration */
	   #ifdef BOARD_ADC_USE_ALT_VREF
	       adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
	   #endif
	       ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);
	       ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false); /* Make sure the software trigger is used. */
	   #if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
	       if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASE))
	       {
	           PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
	       }
	       else
	       {
	           PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
	       }
	   #endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
	       adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
	       adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	   #if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	       adc16ChannelConfigStruct.enableDifferentialConversion = false;
	   #endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

void app_ADC_Value(void)
{
	ADCValue = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);

	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
	        {
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
	flagPIT0 = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(flagPIT0)
	{
		PIT_ClearStatusFlags(PIT, 0, kPIT_TimerFlag);
	}
}

/*******************************************************************************
 * Code
 ******************************************************************************/


int main(void) {

  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    app_PIT_Init();
    app_PWM_Init();
    app_PWM_Edge();

    while(1)
    {
    	app_PWM_UpdateValue();
    	if(flagPIT0 == 1)
    	{
    			if((counter <= 10U) && (counterFlag == 1U))
    			{
    				if(counter == 0U)
    				{
    					counterFlag = 0U;
    				}
    				else
    				{
    					counter = counter - 1;
    					flagPIT0 = 0;
    				}
    			}
    			if(counterFlag == 0U)
    			{
    				if(counter == 10U)
    				{
    					counterFlag = 1U;
    				}
    				else
    				{
    					counter = counter + 1;
    					flagPIT0 = 0;
    				}
    			}
    			else
    			{}
    	}
    	else
    	{}
    	updatedDutycycle = counter;

    }
    return 0 ;
}
