/*
 * gpio_driver.c
 *
 *  Created on: 26-Dec-2023
 *      Author: Mario Castaneda
 */
/******************************************************************************/
/***        Include files                                                   ***/
/******************************************************************************/
#include "gpio_driver.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static GPIO_Type *rgGpio1 = GPIO;
/*******************************************************************************
* Code
******************************************************************************/

/*******************************************************************************
 * vfnInitRGB
 * DESCRIPTION:Init The PORT 1 for the OKDO RGB Led
 * RETURNS:
 * void
 ******************************************************************************/
void vfnGpioInitRGB()
{
	/*Init SYSCOM IOCON clock*/
	SYSCON_Type *rSyscon = SYSCON;
	IOCON_Type *rPinSetup = IOCON;

	/*Enable IOCON clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK;

	/*Enable GPIO1 or PORT 1 Clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_PRESETCTRL0_GPIO1_RST_MASK;

	/*Set Up Pin 15.5.1 Type D IOCON registers*/
	rPinSetup->PIO[RED_LED_PORT][RED_LED_PIN]	|= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[RED_LED_PORT][BLUE_LED_PIN] 	|= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[RED_LED_PORT][GREN_LED_PIN] |= IOCON_PIO_FUNC(0);

	/*16.5.3 GPIO port direction registers*/
	rgGpio1->DIR[RED_LED_PORT] |= (1 << RED_LED_PIN) | (1 << BLUE_LED_PIN) | ( 1 << GREN_LED_PIN);

	/*Turn off all leds*/
	rgGpio1->SET[RED_LED_PORT] = (1<<RED_LED_PIN) | (1<<BLUE_LED_PIN) | (1<<GREN_LED_PIN);
}
/*******************************************************************************
 * vfnTurnOff
 * DESCRIPTION: Power Off RGB Leds
 * RETURNS:
 * void
 ******************************************************************************/
void vfnTurnOff()
{
	/*Turn off all leds*/
	rgGpio1->SET[RED_LED_PORT] = (1<<RED_LED_PIN) | (1<<BLUE_LED_PIN) | (1<<GREN_LED_PIN);
}
/*******************************************************************************
 * vfnRED_Toggle
 * DESCRIPTION: Toggle Red Led
 * RETURNS:
 * void
 ******************************************************************************/
void vfnRED_Toggle()
{
	/*16.5.9 GPIO port toggle register*/
	/* 0 = no operation.
	 * 1 = Toggle outputbit. */
	rgGpio1->NOT[RED_LED_PORT] = (1<<RED_LED_PIN);
}
/*******************************************************************************
 * vfnRED_Toggle
 * DESCRIPTION: Toggle Red Led
 * RETURNS:
 * void
 ******************************************************************************/
void vfnGREEN_Toggle()
{
	/*16.5.9 GPIO port toggle register*/
	/* 0 = no operation.
	 * 1 = Toggle outputbit. */
	rgGpio1->NOT[RED_LED_PORT] = (1<<GREN_LED_PIN);
}
/*******************************************************************************
 * vfnBlue_Toggle
 * DESCRIPTION: Tog
 * RETURNS:
 * void
 ******************************************************************************/
void vfnBLUE_Toggle()
{
	/*16.5.9 GPIO port toggle register*/
	/* 0 = no operation.
	 * 1 = Toggle outputbit. */
	rgGpio1->NOT[RED_LED_PORT] = (1<<BLUE_LED_PIN);
}
/*******************************************************************************
 * vfnRED_On
 * DESCRIPTION: Turn on Only the Led Red, Power off Green and Blue
 * RETURNS:
 * void
 ******************************************************************************/
void vfnRED_On()
{
	/*16.5.7 GPIO port set register*/
	/* 0 = Read: output bit: write: no operation.
	 * 1 = Read: output bit, write: set output bit.*/
	rgGpio1->SET[RED_LED_PORT] = (1<<BLUE_LED_PIN) | (1<<GREN_LED_PIN);
	/*16.5.8 GPIO port clear register*/
	/* 0 = No operation.
	 * 1 = Clear output bit*/
	rgGpio1->CLR[RED_LED_PORT] = (1<<RED_LED_PIN);
}
/*******************************************************************************
 * vfnGREEN_On
 * DESCRIPTION: Turn on Only the Led Green, Power off Red and Blue
 * RETURNS:
 * void
 ******************************************************************************/
void vfnGREEN_On()
{
	/*16.5.7 GPIO port set register*/
	/* 0 = Read: output bit: write: no operation.
	 * 1 = Read: output bit, write: set output bit.*/
	rgGpio1->SET[RED_LED_PORT] = (1<<RED_LED_PIN) | (1<<BLUE_LED_PIN);
	/*16.5.8 GPIO port clear register*/
	/* 0 = No operation.
	 * 1 = Clear output bit*/
	rgGpio1->CLR[RED_LED_PORT] = (1<<GREN_LED_PIN);
}
/*******************************************************************************
 * vfnBLUE_On
 * DESCRIPTION: Turn on Only the Led Blue, Power off Red and Green
 * RETURNS:
 * void
 ******************************************************************************/
void vfnBLUE_On()
{
	/*16.5.7 GPIO port set register*/
	/* 0 = Read: output bit: write: no operation.
	 * 1 = Read: output bit, write: set output bit.*/
	rgGpio1->SET[RED_LED_PORT] = (1<<RED_LED_PIN) | (1<<GREN_LED_PIN);
	/*16.5.8 GPIO port clear register*/
	/* 0 = No operation.
	 * 1 = Clear output bit*/
	rgGpio1->CLR[RED_LED_PORT] = (1<<BLUE_LED_PIN);
}

