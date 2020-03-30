/*
 * Macros.h
 *
 *  Created on: Mar 21, 2020
 *      Author: dario
 */

#ifndef MACROS_H_
#define MACROS_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_TPM_BASEADDR 											TPM2
#define BOARD_TPM_CHANNEL 											1U

/* Interrupt to enable and flag to read; depends on the TPM channel used */
#define TPM_CHANNEL_INTERRUPT_ENABLE 								kTPM_Chnl1InterruptEnable
#define TPM_CHANNEL_FLAG 											kTPM_Chnl1Flag

/* Interrupt number and interrupt handler for the TPM instance used */
#define TPM_INTERRUPT_NUMBER 										TPM2_IRQn
#define TPM_LED_HANDLER 											TPM2_IRQHandler

/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK 											CLOCK_GetFreq(kCLOCK_PllFllSelClk)

/* Select ADC */
#define ADC16_USER_CHANNEL 											0U /*PTE20, ADC0_SE0 */
#define ADC16_IRQn 													ADC0_IRQn
#define ADC16_IRQ_HANDLER_FUNC 										ADC0_IRQHandler
#define APP_ADC_CHANNEL 		0u
#define APP_ADC_CHANNEL_GROUP 	0u

/* PIT */
#define PIT_CLK_SRC_HZ_HP 											((uint64_t)24000000)
#define CLK_500ms 													500U
#define CLK															5U
#define CLK_10ms													10U
#define CLK_100ms													100U
#define OUTPT_OFF 													0x01u
#define OUTPT_ON 													0x00u

/* LPSCI */

#define LPSCI 														UART0
#define LPSCI_CLKSRC 												kCLOCK_CoreSysClk
#define LPSCI_CLK_FREQ 												CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define BAUDRATE													115200

#endif /* MACROS_H_ */
