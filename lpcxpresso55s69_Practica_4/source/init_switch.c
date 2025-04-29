/*
 * init_switch.c
 *
 *  Created on: Mar 12, 2025
 *      Author: Mario Castaneda
 */

#include "init_switch.h"

#define BTN0_PORT 0
#define BTN9_PORT 1
#define BTN13 13
#define BTN14 14
#define BTN15 15
#define BTN16 16

#define SWITCH 0x1E000

static GPIO_Type *rGpio = GPIO;

void vfnInitSwith()
{
	SYSCON_Type *rClocks = SYSCON;
	IOCON_Type *rIocon = IOCON;

	//Enable Clocks
	/*Table 55. AHB Clock control 0 (AHBCLKCTRL0, offset = 0x200)*/
	rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK
									| SYSCON_AHBCLKCTRL0_GPIO0_MASK;

	/*Table 340. I/O control registers: FUNC values (FUNC = 0 to 4) and pin functions*/
	rIocon->PIO[BTN0_PORT][BTN13]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
	rIocon->PIO[BTN0_PORT][BTN14]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
	rIocon->PIO[BTN0_PORT][BTN15]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
	rIocon->PIO[BTN0_PORT][BTN16]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;

	/*Table 347. GPIO direction port register (DIRa, a = 0…1, offset 2000h + (a × 4h))*/
	rGpio->DIR[BTN0_PORT] &= ~(SWITCH);

}


uint8_t wSwitchValue()
{
	uint32_t wValue = (rGpio->PIN[0]&(SWITCH));

	wValue = wValue >> 13;
	return wValue;
}










