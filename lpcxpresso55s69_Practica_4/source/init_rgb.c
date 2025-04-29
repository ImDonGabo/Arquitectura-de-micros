/*
 * init_rgb.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Gabriel Valle Carrasco
 */

#include "init_rgb.h"
#include "DisplaysDriver.h"

#define RGB_PORT 1

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
	rIocon->PIO[RGB_PORT][0]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][1]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][2]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][3]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][4]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][5]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][6]	= IOCON_PIO_FUNC(0);
	rIocon->PIO[RGB_PORT][7]	= IOCON_PIO_FUNC(0);

	/*Table 347. GPIO direction port register (DIRa, a = 0…1, offset 2000h + (a × 4h))*/
	rGpio->DIR[RGB_PORT] |= 0xFF;

	rGpio->SET[RGB_PORT] = 0xFF;
}


void vfn2Leds()
{
	rGpio->SET[RGB_PORT] = 0x7F; //Turns off other led if on
 	rGpio->NOT[RGB_PORT] = 0x80;
}

void vfn8BitsCounter()
{
	static uint8_t bCounter = 0x00;
	rGpio->SET[RGB_PORT] = 0xFF;
	rGpio->CLR[RGB_PORT] = bCounter++;
}

void vfnCorrimientoIzq()
{
	static uint8_t bCorri = 0;

	rGpio->SET[RGB_PORT] = 0xFF;
	rGpio->CLR[RGB_PORT] = 1<<bCorri++;

	if(bCorri==8)
	{
		//rGpio->SET[RGB_PORT] = 0xFF;
		bCorri = 0;
	}
}

void vfnCorrimientoDer()
{
	static uint8_t bCorri = 7;

	rGpio->SET[RGB_PORT] = 0xFF;
	rGpio->CLR[RGB_PORT] = 1<<bCorri--;

	if(bCorri==0)
	{
		//rGpio->SET[RGB_PORT] = 0xFF;
		bCorri = 7;
	}
}

void vfnJohnsonLED()
{
	static uint8_t bCorri = 0;

	rGpio->NOT[RGB_PORT] = 1<<bCorri++;

	if(bCorri==8)
	{
		bCorri = 0;
	}
}

void vfnDualWalkWCrash()
{
	static uint8_t bCorriR = 0;
	static uint8_t bCorriL = 7;

	rGpio->NOT[RGB_PORT] = 1<<bCorriR++;
	rGpio->NOT[RGB_PORT] = 1<<bCorriL--;

	if(bCorriR==8 || bCorriL < 0)
	{
		bCorriR = 0;
		bCorriL = 7;
	}
}

void vfnDualWalk(void)
{
    static uint8_t fase = 0;   // 0: secuencia de izquierda a derecha, 1: secuencia de derecha a izquierda
    static int8_t index;


    if(fase == 0 && index < 0)
    {
        index = 7;
    }
    else if(fase == 1 && index > 7)
    {
        index = 0;
    }

    rGpio->SET[RGB_PORT] = 0xFF;

    if(fase == 0)
    {
        rGpio->CLR[RGB_PORT] = (1 << index);
        index--;

        if(index < 0)
        {
            fase = 1;
            index = 0;
        }
    }
    else
    {
        rGpio->CLR[RGB_PORT] = (1 << index);
        index++;

        if(index > 7)
        {
            fase = 0;
            index = 7;
        }
    }
}


