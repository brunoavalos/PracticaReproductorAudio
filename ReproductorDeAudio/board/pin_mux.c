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

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MKL25Z128xxx4'
- !!package 'MKL25Z128VLK4'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.1.0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "Applications/app_TrackIndicator.h"

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define SOPT5_UART0RXSRC_UART_RX      0x00u   /*!< UART0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART0 transmit data source select: UART0_TX pin */
#define PIN20_IDX                       20u
#define PORT_LED_GREEN 				  PORTB
#define PIN_LED_GREEN 					19U

/* Define GPIO Input Buttons */
#define INPUT_PORT					  GPIOD
#define INPUT_BUTTON1					 0u
#define INPUT_BUTTIN2					 1u
#define INPUT_BUTTON3					 2u
/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: '28', peripheral: UART0, signal: TX, pin_signal: TSI0_CH3/PTA2/UART0_TX/TPM2_CH1}
  - {pin_num: '27', peripheral: UART0, signal: RX, pin_signal: TSI0_CH2/PTA1/UART0_RX/TPM2_CH0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortB);
  /* Port E Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);
  /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);
  /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);


  PORT_SetPinMux(PORT_LED_GREEN, PIN_LED_GREEN, kPORT_MuxAlt3);

  	  gpio_pin_config_t BIT0_config = {
         .pinDirection = kGPIO_DigitalOutput,
         .outputLogic = 0U
     };
     /* Initialize GPIO functionality on pin PTB0 (pin 43)  */
     GPIO_PinInit(BOARD_INITPINS_GPIOB, BOARD_INITPINS_BIT0_PIN, &BIT0_config);

     gpio_pin_config_t BIT1_config = {
         .pinDirection = kGPIO_DigitalOutput,
         .outputLogic = 0U
     };
     /* Initialize GPIO functionality on pin PTB1 (pin 44)  */
     GPIO_PinInit(BOARD_INITPINS_GPIOB, BOARD_INITPINS_BIT1_PIN, &BIT1_config);

     gpio_pin_config_t BIT2_config = {
         .pinDirection = kGPIO_DigitalOutput,
         .outputLogic = 0U
     };
     /* Initialize GPIO functionality on pin PTB2 (pin 45)  */
     GPIO_PinInit(BOARD_INITPINS_GPIOB, BOARD_INITPINS_BIT2_PIN, &BIT2_config);

     /* Inicialización de los pines del puerto C */
     gpio_pin_config_t Track0_config = {
              .pinDirection = kGPIO_DigitalOutput,
              .outputLogic = 0U
          };
          /* Initialize GPIO functionality on pin PTB2 (pin 45)  */
     GPIO_PinInit(TrackGPORT, TrackPIN0, &Track0_config);

     gpio_pin_config_t Track1_config = {
                  .pinDirection = kGPIO_DigitalOutput,
                  .outputLogic = 0U
              };
              /* Initialize GPIO functionality on pin PTB2 (pin 45)  */
         GPIO_PinInit(TrackGPORT, TrackPIN1, &Track1_config);

       PORT_SetPinMux(TrackPORT, TrackPIN0, kPORT_MuxAsGpio);

       PORT_SetPinMux(TrackPORT, TrackPIN1, kPORT_MuxAsGpio);
     /* Finalización de declaración de puerto C como salida */

     gpio_pin_config_t BIT3_config = {
         .pinDirection = kGPIO_DigitalOutput,
         .outputLogic = 0U
     };
     /* Initialize GPIO functionality on pin PTB2 (pin 45)  */
     GPIO_PinInit(BOARD_INITPINS_GPIOB, BOARD_INITPINS_BIT3_PIN, &BIT3_config);


     gpio_pin_config_t BUTTON1_config = {
         .pinDirection = kGPIO_DigitalInput
     };

     /* Initialize GPIO functionality on pin PTD0 (pin 45)  */
     GPIO_PinInit(INPUT_PORT, BOARD_INITPINS_INPUT0_PIN, &BUTTON1_config);

     gpio_pin_config_t BUTTON2_config = {
               .pinDirection = kGPIO_DigitalInput
           };

     /* Initialize GPIO functionality on pin PTD2 ()  */
     GPIO_PinInit(INPUT_PORT, BOARD_INITPINS_INPUT2_PIN, &BUTTON2_config);

     gpio_pin_config_t BUTTON3_config = {
               .pinDirection = kGPIO_DigitalInput
          };

     /* Initialize GPIO functionality on pin PTD3 ()  */
     GPIO_PinInit(INPUT_PORT, BOARD_INITPINS_INPUT3_PIN, &BUTTON3_config);



     /* PORTE0 () is configured as PTD0 */
     PORT_SetPinMux(BOARD_INITPINS_PORTD, BOARD_INITPINS_INPUT0_PIN, kPORT_MuxAsGpio);

     /* PORTE0 () is configured as PTD1 */
     PORT_SetPinMux(BOARD_INITPINS_PORTD, BOARD_INITPINS_INPUT2_PIN, kPORT_MuxAsGpio);

     /* PORTE0 () is configured as PTD2 */
     PORT_SetPinMux(BOARD_INITPINS_PORTD, BOARD_INITPINS_INPUT3_PIN, kPORT_MuxAsGpio);

     /* PORTB0 (pin 43) is configured as PTB0 */
     PORT_SetPinMux(BOARD_INITPINS_PORTB, BOARD_INITPINS_BIT0_PIN, kPORT_MuxAsGpio);

     /* PORTB1 (pin 44) is configured as PTB1 */
     PORT_SetPinMux(BOARD_INITPINS_PORTB, BOARD_INITPINS_BIT1_PIN, kPORT_MuxAsGpio);

     /* PORTB2 (pin 45) is configured as PTB2 */
     PORT_SetPinMux(BOARD_INITPINS_PORTB, BOARD_INITPINS_BIT2_PIN, kPORT_MuxAsGpio);

     /* PORTB3 (pin 46) is configured as PTB3 */
     PORT_SetPinMux(BOARD_INITPINS_PORTB, BOARD_INITPINS_BIT3_PIN, kPORT_MuxAsGpio);

  /* PORTE20 (pin 13) is configured as ADC0_DP0 */
  PORT_SetPinMux(PORTE, PIN20_IDX, kPORT_PinDisabledOrAnalog);
  PORT_SetPinMux(PORTA, PIN1_IDX, kPORT_MuxAlt2);            /* PORTA1 (pin 27) is configured as UART0_RX */
  PORT_SetPinMux(PORTA, PIN2_IDX, kPORT_MuxAlt2);            /* PORTA2 (pin 28) is configured as UART0_TX */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)       /* UART0 transmit data source select: UART0_TX pin */
      | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX)       /* UART0 receive data source select: UART0_RX pin */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
