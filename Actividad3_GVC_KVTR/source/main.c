/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "app.h"
#include "board.h"
#include "init_rgb.h"
#include "init_switch.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY 0xAA000
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t swValue;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	volatile uint32_t dwDelay = DELAY;

    /* Init board hardware. */
	BOARD_InitHardware();
    vfnInitRGB();
    vfnInitSwitch();
    while (1)
    {
    swValue = wdfnReadSwitch();
    if(dwDelay==0)
        	{
        		dwDelay = DELAY;
        		PRINTF("Valor: 0x%x\r\n", swValue);
        	}
        	dwDelay--;
    	/*switch(swValue){
    	case 0:
			vfnBlackOn();
			break;
		case 1:
			vfnRedOn();
			break;
		case 2:
			vfnBlueOn();
			break;
		case 3:
			vfnGreenOn();
			break;
		case 4:
			vfnPinkOn();
			break;
		case 5:
			vfnYellowOn();
			 break;
		case 6:
			vfnLightBlueOn();
			 break;
		case 7:
			vfnWhiteOn();
			 break;
		default:
			vfnBlackOn();
			break;
		}*/


    	}
    }
