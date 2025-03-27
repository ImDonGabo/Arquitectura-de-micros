/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "ctimer_driver.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY 0x300000
#define PWM_FREQ 5000
#define CH1 1
#define CH2 2
#define ARRAY_SIZE2 4
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t dutyArray[] = {10, 25, 50, 70, 90};
uint8_t counter = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/


/*!
 * @brief Main function
 */
int main(void)
{
	volatile uint32_t dwDelay = 0;

	vfnInitCTimerAndPins();
	vfnSetUpPWM_Freq(PWM_FREQ,CH1);
	vfnSetUpPWM_Freq(PWM_FREQ,CH2);

	CTIMER_StartTimer();
    while (1)
    {
    	if(dwDelay==0)
		{
			dwDelay = DELAY;
			vfnUpdate_PWM(dutyArray[counter],CH1);
			vfnUpdate_PWM(dutyArray[counter],CH2);
			counter++;

		}
		dwDelay--;
		if (counter == ARRAY_SIZE2){
			counter = 0;
		}

    }
}
