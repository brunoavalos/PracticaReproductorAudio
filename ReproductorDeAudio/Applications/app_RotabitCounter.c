/*
 * app_RotabitCounter.c
 *
 *  Created on: Mar 27, 2020
 *      Author: dario
 */

#include "Applications/app_RotabitCounter.h"

/* Local Variables */

T_UBYTE lub_Output = 0u;

void app_RotabitCounterFoward(void)
{

	GPIOB->PDOR=lub_Output;
	if(lub_Output == 0)
	{
	   lub_Output = 1;

	}
	else
	{
	   if(lub_Output == 8)
	   {
		   lub_Output = 0;
	   }
	   else
	   {
	   lub_Output = lub_Output << 1;
	   }
	}
}
void app_RotabitCounterBackward(void)
{
	GPIOB->PDOR=lub_Output;
		if(lub_Output == 0)
		{
		   lub_Output = 8;

		}
		else
		{
		   if(lub_Output == 2)
		   {
			   lub_Output = 1;
		   }
		   else
		   {
		   lub_Output = lub_Output >> 1;
		   }
		}
}
