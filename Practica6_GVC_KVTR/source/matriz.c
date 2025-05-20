#include "Matriz.h"

uint32_t wMatrixCols [] = { // Definition
    COL0,
    COL1,
    COL2,
    COL3,
    COL4,
    COL5,
    COL6,
    COL7
};

#define TOTAL_MATRIX (sizeof(wMatrixCols)/sizeof(wMatrixCols[0]))

static GPIO_Type *rgGpio1 = GPIO;

static uint8_t bDisplayIdx = 0;
uint8_t gbaDisplayData[TOTAL_MATRIX] = {0};

uint8_t Flag=0;

// Filas
uint8_t bMatrixRows[] = {
	ROW0,
	ROW1,
	ROW2,
	ROW3,
	ROW4,
	ROW5,
	ROW6,
	ROW7
};

/*******************************************************************************
 * vfnInitGpios
 * DESCRIPTION:Init The PORT 1 for the Display
 * RETURNS: void
 ******************************************************************************/
void vfnInitGpios()
{
	/*Init SYSCOM IOCON clock*/
	SYSCON_Type *rSyscon = SYSCON;
	IOCON_Type *rPinSetup = IOCON;

	/*Enable IOCON clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK;

	/*Enable GPIO1 or PORT 1 Clock*/
	rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_PRESETCTRL0_GPIO1_RST_MASK | SYSCON_PRESETCTRL0_GPIO0_RST_MASK;

	/*Set Up Pin 15.5.1 Type D IOCON registers*/
	rPinSetup->PIO[PORT1][ROW0_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW1_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW2_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW3_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW4_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW5_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW6_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][ROW7_PIN] |= IOCON_PIO_FUNC(0);

	rPinSetup->PIO[PORT1][COL0_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL1_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL2_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL3_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL4_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL5_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL6_PIN] |= IOCON_PIO_FUNC(0);
	rPinSetup->PIO[PORT1][COL7_PIN] |= IOCON_PIO_FUNC(0);

	/*16.5.3 GPIO port direction registers*/
	rgGpio1->DIR[PORT1] |= ALL_PORT1 | COL0 | COL1 | COL2 | COL3 | COL4 | COL5 | COL6 | COL7;
	rgGpio1->CLR[PORT1] |= ALL_PORT1 | COL0 | COL1 | COL2 | COL3 | COL4 | COL5 | COL6 | COL7;
}

/*******************************************************************************
 * vfnColumns_Driver
 * DESCRIPTION: Actualiza un display a la vez para multiplexar los 4 dígitos
 * RETURNS: void
 * No se modifica
 ******************************************************************************/
void vfnColumns_Driver()
{
	/*Columns and Lines Turn off*/
	rgGpio1->SET[PORT1] |= ALL_PORT1;
	rgGpio1->CLR[PORT1] |= COL0 | COL1 | COL2 | COL3 | COL4 | COL5 | COL6 | COL7;

	rgGpio1->CLR[PORT1] = (bMatrixRows[gbaDisplayData[bDisplayIdx]]); // Current Display Data
	rgGpio1->SET[PORT1] = (wMatrixCols[bDisplayIdx]);	//Turn on Current Column;
	if ( ++bDisplayIdx > TOTAL_MATRIX)
	{
		bDisplayIdx = 0;
	}
}

void vfnMatrix_Value()
{
	gbaDisplayData[0] = 0;
	gbaDisplayData[1] = 1;
	gbaDisplayData[2] = 2;
	gbaDisplayData[3] = 3;
	gbaDisplayData[4] = 4;
	gbaDisplayData[5] = 5;
	gbaDisplayData[6] = 6;
	gbaDisplayData[7] = 7;
}
