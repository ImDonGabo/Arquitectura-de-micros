/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "board.h"
#include "init_rgb.h"
#include "init_switch.h"
#include "DisplaysDriver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY 0xA0000
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	uint32_t dwDelay = DELAY;
	uint8_t dipSwitch=0x00;

	uint8_t Array [3]={1,2,9};

	uint8_t *pArray;

	pArray = &Array[0];

	dwDelay = *pArray;

	vfnInitSwith();
	vfnInitRGB();

    while (1)
    {
    	dipSwitch = wSwitchValue();

    	if(!dwDelay--)
    	{
    		dwDelay = DELAY;

    		if(dipSwitch==0)
    		{
    			vfn2Leds();
    		}
    		else if(dipSwitch==1)
    		{
    			vfn8BitsCounter();
    		}
    		else if(dipSwitch==2)
    		{
    			vfnCorrimientoIzq();
    		}
    		else if(dipSwitch==3)
    		{
    			vfnJohnsonLED();
    		}
    		else if(dipSwitch==4)
    		{
    			vfnDualWalkWCrash();
    		}
    		else if(dipSwitch==5)
    		{
    			vfnDualWalk();
    		}
    		else if(dipSwitch==6)
    		{
    			vfnCorrimientoDer();
    		}
    		else if(dipSwitch==7)
    		{
    			vfnDisplayCounter();
    		}
    		else if(dipSwitch==8)
    		{
    			vfnDisplayInitials();
    		}

    	}

    }
}
