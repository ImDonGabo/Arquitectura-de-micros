#include "btn_debounce.h"
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
* *******************************************************************************/

static uint16_t gbLastState 	= ( 1<<BTN0)|( 1<<BTN1);
static uint16_t gCurrentState 	= (1 <<BTN0)|( 1<<BTN1);

uint8_t gCountBtn0 = 0;
uint8_t gCountBtn1 = 0;
uint8_t gCountBtn2 = 0;


void vfnInit_Btn()
{
	SYSCON_Type *rClocks = SYSCON;
	IOCON_Type *rPinSetup = IOCON;

	/*Init Clocks IOCON 4.5.17 AHB clock control 0*/
	rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK | SYSCON_PRESETCTRL0_GPIO1_RST_MASK;

	/*Set Up Pin 15.5.1 Type D IOCON registers*/
	rPinSetup->PIO[BTN_PORT][BTN0] |= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
	rPinSetup->PIO[BTN_PORT1][BTN1] |= IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;

	/*GPIO as output 16.5.3 GPIO port direction registers*/
	rgGpio1->DIR[BTN_PORT] &= ~(( 1<<BTN0));
	rgGpio1->DIR[BTN_PORT1] &= ~(( 1<<BTN1));

}

/*******************************************************************************
 * bfnReturn
 * DESCRIPTION:
 *
 * RETURNS:
 * uint8_t Estado del Botón
 ******************************************************************************/
uint16_t bfnReturn()
{
	uint16_t bBtnState = (rgGpio1->PIN[BTN_PORT] & (1<<BTN0)) | (rgGpio1->PIN[BTN_PORT1] & (1<<BTN1)); 	//Input Status
	uint16_t bChange = bBtnState ^ gbLastState;		//XOR Current Value with last value



	if(bChange & (1<<BTN0))
	{
		gCountBtn0 = 3;	//Count equal to 3
	}
	else
	{
		if(gCountBtn0)
		{
			gCountBtn0--;
		}
		else	//Count is 0 at this point
		{
			gCurrentState &=  ~(1<<BTN0);
			gCurrentState |=  (bBtnState & (1<<BTN0)); //0001 0000
		}
	}
	if(bChange & (1<<BTN1))
	{
		gCountBtn1 = 3;	//Count equal to 3
	}
	else
	{
		if(gCountBtn1)
		{
			gCountBtn1--;
		}
		else	//Count is 0 at this point
		{
			gCurrentState &=  ~(1<<BTN1);
			gCurrentState |=  (bBtnState & (1<<BTN1));
		}
	}
	gbLastState = bBtnState;

	return gCurrentState;
}



