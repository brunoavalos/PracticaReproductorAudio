/*
 * Macros.h
 *
 *  Created on: 10 mar. 2020
 *      Author: Dario
 */

#ifndef MACROS_H_
#define MACROS_H_

	#define BOARD_TPM_BASEADDR 					TPM2
	#define BOARD_TPM_CHANNEL 					1U

	/* Interrupt to enable and flag to read; depends on the TPM channel used */
	#define TPM_CHANNEL_INTERRUPT_ENABLE 		kTPM_Chnl1InterruptEnable
	#define TPM_CHANNEL_FLAG 					kTPM_Chnl1Flag

	/* Interrupt number and interrupt handler for the TPM instance used */
	#define TPM_INTERRUPT_NUMBER 				TPM2_IRQn
	#define TPM_LED_HANDLER 					TPM2_IRQHandler

	/* Get source clock for TPM driver */
	#define TPM_SOURCE_CLOCK 					CLOCK_GetFreq(kCLOCK_PllFllSelClk)

	/* Select ADC */
	#define ADC_CHANNEL							0U
	#define ADC_CHANNEL_GROUP					0U

	/* PIT */
	#define PIT_CLK_SRC_HZ_HP 					((uint64_t)24000000)
	#define CLK 								((uint64_t)100000)
	#define OUTPT_OFF 							0x01u
	#define OUTPT_ON 							0x00u

	/* UART */
	#define UART_SELECTION UART1
	#define UART_CLKSRC BUS_CLK
	#define UART_CLK_FREQ CLOCK_GetFreq(BUS_CLK)


#endif /* MACROS_H_ */
