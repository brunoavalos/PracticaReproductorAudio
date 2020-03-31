/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

extern void BOARD_InitBootPins(void);
/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*! @name PORTE0
  @{ */
#define BOARD_INITPINS_FGPIOD 		FGPIOD /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_GPIOD 		GPIOD /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_PORTD 		PORTD /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_INPUT0_PIN 	0U     /*!<@brief PORTB pin index: 0 */
#define BOARD_INITPINS_INPUT2_PIN 	2U
#define BOARD_INITPINS_INPUT3_PIN 	3U /* @} */

/*! @name PORTB (number 43), J10[2]/A0 */
#define BOARD_INITPINS_FGPIOB 		FGPIOB /*!<@brief FGPIO device name: FGPIOB */
#define BOARD_INITPINS_GPIOB 		GPIOB  /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_PORTB 		PORTB  /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_BIT0_PIN 	0U     /*!<@brief PORTB pin index: 0 */
#define BOARD_INITPINS_BIT1_PIN 	1U                                       /* @} */
#define BOARD_INITPINS_BIT2_PIN 	2U
#define BOARD_INITPINS_BIT3_PIN 	3U

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
