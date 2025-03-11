/*
 * init_rgb.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Gabriel Valle
 */

#include "init_switch.h"

#define PORT_ONE 1
#define SW1 0
#define SW2 1
#define SW3 2
#define SW_PINS (1<<SW1|1<SW2|1<<SW3)


static GPIO_Type *rGpio = GPIO;

void vfnInitSwitch()
{
	SYSCON_Type *rClocks = SYSCON;
	IOCON_Type *rIocon = IOCON;

	//Enable Clocks
	/*Table 55. AHB Clock control 0 (AHBCLKCTRL0, offset = 0x200)*/
	rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK
									| SYSCON_AHBCLKCTRL0_GPIO1_MASK;

	/*Table 340. I/O control registers: FUNC values (FUNC = 0 to 4) and pin functions*/
	rIocon->PIO[PORT_ONE][SW1]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE(1);
	rIocon->PIO[PORT_ONE][SW2]	= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE(1);
	rIocon->PIO[PORT_ONE][SW3]  = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE(1);

	/*Table 347. GPIO direction port register (DIRa, a = 0…1, offset 2000h + (a × 4h))*/
	rGpio->DIR[PORT_ONE] &= ~(SW_PINS);

}

uint32_t wdfnReadSwitch()
{
	uint32_t swvalue = rGpio->PIN[PORT_ONE] & SW_PINS;
	return swvalue;
}

