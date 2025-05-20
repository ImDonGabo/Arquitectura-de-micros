/*
 * xxxx.c
 *
 *  Created on:
 *      Author: 
 */
/******************************************************************************/
/***        Include files                                                   ***/
/******************************************************************************/
#include "gpio_driver.h"
#include "utick_timer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
SYSCON_Type *rSyscon = SYSCON;
NVIC_Type *rInterrupt = NVIC;
UTICK_Type *rUtick = UTICK0;

static volatile uint8_t gbUTICKStatus = 0;

/*******************************************************************************
* Code
******************************************************************************/

/*******************************************************************************
 * vfn
 * DESCRIPTION: 
 *
 * RETURNS:
 * void
 ******************************************************************************/
void vfnUTICKinit(void)
{
    rSyscon->FCCLKSEL.FCCLKSEL0 = SYSCON_FCCLKSEL0_SEL(2);

    rSyscon->CLOCK_CTRL |=  SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK;         /*!< Ensure fro_1m is on */

    rSyscon->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_FRO1MHZ_UTICK_ENA_MASK;        /* The FRO 1 MHz clock to UTICK is enabled. */

	rSyscon->AHBCLKCTRL.AHBCLKCTRL1 |= SYSCON_AHBCLKCTRL1_UTICK_MASK;		/* Enable Utick clock */

    rInterrupt->ISER[0] |= 1 << 8;                                      	/* Enable Utick interrupt */

    rUtick->CTRL = UTICK_VALUE | UTICK_CTRL_REPEAT(1);                      /*! REPEAT - Repeat delay.  0 = One-time delay. 
                                                                                                        1 = Delay repeats continuously.*/
}

/*******************************************************************************
 * UTICK0_IRQHandler
 * DESCRIPTION: UTICK IRQ handler
 *
 * RETURNS:
 * void
 ******************************************************************************/
void UTICK0_IRQHandler(void)
{
	gbUTICKStatus = 1;	
	/* Clear the FLAG */
	rUtick->STAT = UTICK_STAT_INTR_MASK;
	//vfnBLUE_Toggle();
}

/*******************************************************************************
 * vfn
 * DESCRIPTION: 
 *
 * RETURNS:
 * void
 ******************************************************************************/
uint8_t bfnUTICKGetStatus(void)
{	
	/*UTICK Status*/
	return gbUTICKStatus;
}

/*******************************************************************************
 * vfn 
 * DESCRIPTION: 
 *
 * RETURNS:
 * void
 ******************************************************************************/
void vfnUTICKClearStatus(void)
{
	/*Clear UTICK Flag	 */
	gbUTICKStatus = 0;
}
