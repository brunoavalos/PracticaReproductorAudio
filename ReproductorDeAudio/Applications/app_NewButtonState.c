/*
 * app_NewButtonState.c
 *
 *  Created on: 28 mar. 2020
 *      Author: dario
 */

#include "app_NewButtonState.h"
#include "app_Debounce.h"


/* Valor de los botones */

extern T_UBYTE lub_ButtonState[2]; /* 0 1 2 Guarda los estado logicos de los botones*/
T_UBYTE lub_i = 0u;
T_UBYTE rub_Back_Btn_Flag = 0u;
T_UBYTE rub_Next_Btn_Flag = 0u;

T_UBYTE TimeState = 0u;
T_UBYTE rub_NormalPressFlag = 0u;
T_UBYTE rub_LongPressFlag = 0u;

typedef enum{
	LongPress, /*0 */
	NormalPress /* 1*/
}E_NewButtonState;

E_NewButtonState StateButton;

typedef enum
{
	Btn_Unpressed,
	Btn_Pressed

}T_ButtonState;

T_ButtonState BtnState = Btn_Unpressed;



void app_NewButtonInputValue(void)
{
	for(lub_o = 0u; o <= NUMBERS_BUTTON; lub_o++)
	{
		if(lub_ButtonState[lub_o] == FALSE)
		{
			if(TimeState >= 50u && TimeState <= 1000u)
			{
				rub_NormalPressFlag = TRUE;
			}
		else if(TimeState > 1000u)
			{
				rub_LongPressFlag = TRUE;
			}
		else
			{
				TimeState++;
			}
		}
		else
		{

		}
	}
}
//lub_ButtonState[0] = GPIO_ReadPinInput(GPIOD, 0);
//lub_ButtonState[1] = GPIO_ReadPinInput(GPIOD, 2);
//lub_ButtonState[2] = GPIO_ReadPinInput(GPIOD, 3);

	//lub_ButtonState[0] -> Play/Pause/Stop
	//lub_ButtonState[1] -> Next/Fordward
	//lub_ButtonState[2] -> Back/Rewind


for(lub_i = 0; lub_i < NUMBERS_BUTTON; lub_i++)
{
	/* If button has a valid press, then perform the corresponding actions*/
	if(BtnState == Btn_Pressed)
	{
		switch(StateButton)
		{
		/*Actions for BUTTON 0*/
		case LongPress:
		{

				/* > 1000ms*/
				if((rub_flagPIT1 == TRUE) && (rub_Back_Btn_Flag == FALSE) && (rub_Next_Btn_Flag == FALSE))
							{
								/*Btn [0] -> Funcion Stop Rotabit*/

							}else if((rub_flagPIT1 == FALSE) && (rub_Back_Btn_Flag == TRUE) && (rub_Next_Btn_Flag == FALSE))
							{
								/*Btn [1] -> Funcion Fordward*/

							}else if((rub_flagPIT1 == FALSE) && (rub_Back_Btn_Flag == FALSE) && (rub_Next_Btn_Flag == TRUE))
							{
								/*Btn [2] -> Funcion Backward*/

							}else{/*Do nothing*/}

		}break;
		/*Actions for BUTTON 1*/
		case NormalPress:
		{
			/* > 50ms* && < 1000ms*/
			if((rub_flagPIT1 == TRUE) && (rub_Back_Btn_Flag == FALSE) && (rub_Next_Btn_Flag == FALSE))
						{
						/*Btn [0] -> Funcion Play/Pause Rotabit*/;
						app_RotabitCounterFoward();
						rub_flagPIT1 = FALSE;
						}else if((rub_flagPIT1 == FALSE) && (rub_Back_Btn_Flag == TRUE) && (rub_Next_Btn_Flag == FALSE))
						{
						/*Btn [1] -> Funcion Next*/

						}else if((rub_flagPIT1 == FALSE) && (rub_Back_Btn_Flag == FALSE) && (rub_Next_Btn_Flag == TRUE))
						{
							/*Btn [2] -> Funcion Back*/

						}else{/*Do nothing*/}

						}break;
						/*Actions for not valid BUTTON*/
						default:
						{
							/* Do Nothing */
							}break;
						}
	}
	else
	{//Button is not pressed, perform the corresponding action
		switch(lub_i)
		{
		/*Actions for BUTTON 0*/
		case BUTTON0:
		{

		}break;
		/*Actions for BUTTON 1*/
		case BUTTON1:
		{

		}break;
		/*Actions for not valid BUTTON*/
		default:
		{
			/* Do Nothing */
		}break;
		}
	}
}


}


void app_NewButtonState_Task(void)
{
	app_NewButtonInputValue();
	/*app_NewButtonCounter();*/

}

