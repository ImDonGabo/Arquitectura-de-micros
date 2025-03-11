/*
 * init_rgb.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Mario Castaneda
 */

#include "init_rgb.h"

#define RGB_PORT 1
#define RED 4
#define BLUE 6
#define GREEN 7
#define RGB_PINS (1<<RED|1<<BLUE|1<<GREEN)

static GPIO_Type *rGpio = GPIO;

void vfnInitRGB()
{
	SYSCON_Type *rClocks = SYSCON;
	IOCON_Type *rIocon = IOCON;

	//Enable Clocks
	/*Table 55. AHB Clock control 0 (AHBCLKCTRL0, offset = 0x200)*/
	rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK
									| SYSCON_AHBCLKCTRL0_GPIO1_MASK;

	/*Table 340. I/O control registers: FUNC values (FUNC = 0 to 4) and pin functions*/
	rIocon->PIO[RGB_PORT][RED]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][BLUE]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][GREEN]= IOCON_PIO_FUNC(0);

	/*Table 347. GPIO direction port register (DIRa, a = 0…1, offset 2000h + (a × 4h))*/
	rGpio->DIR[RGB_PORT] |= RGB_PINS;

	rGpio->SET[RGB_PORT] = RGB_PINS;
}

void vfnRedOn()
{
	rGpio->CLR[RGB_PORT] = 1<<RED;
}

void vfnGreenOn()
{
	rGpio->CLR[RGB_PORT] = 1<<GREEN;
}

void vfnBlueOn()
{
	rGpio->CLR[RGB_PORT] = 1<<BLUE;
}
void vfnPinkOn()
{
	rGpio->SET[RGB_PORT] = 1<<GREEN;
	rGpio->CLR[RGB_PORT]=1<<RED|1<<BLUE;
}

void vfnYellowOn()
{
	rGpio->SET[RGB_PORT] = 1<<BLUE;
	rGpio->CLR[RGB_PORT]=1<<RED|1<<GREEN;
}

void vfnLightBlueOn()
{
	rGpio->SET[RGB_PORT] = 1<<RED;
	rGpio->CLR[RGB_PORT]=1<<GREEN|1<<BLUE;
}

void vfnWhiteOn()
{
	rGpio->CLR[RGB_PORT]=1<<RED|1<<BLUE|1<<RED;
}

void vfnBlackOn()
{
	rGpio->SET[RGB_PORT]=1<<RED|1<<BLUE|1<<RED;
}
