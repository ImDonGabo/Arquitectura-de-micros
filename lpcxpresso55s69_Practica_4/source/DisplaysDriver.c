//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
	\file	DisplaysDriver.c
	\author	Mario Castañeda
	\date	10-October-2023
	\brief	C file that creates a const array for the 7 Segments Define
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "DisplaysDriver.h"
#include "init_rgb.h"
//------------------------------------------------------------------------------
// Defines
#define RGB_PORT 1
//------------------------------------------------------------------------------


#define SEGA (1<<SEGMENT_A)
#define SEGB (1<<SEGMENT_B)
#define SEGC (1<<SEGMENT_C)
#define SEGD (1<<SEGMENT_D)
#define SEGE (1<<SEGMENT_E)
#define SEGF (1<<SEGMENT_F)
#define SEGG (1<<SEGMENT_G)

#define SEVEN_SEGS_ZERO		(~SEGA & ~SEGB & ~SEGC & ~SEGD & ~SEGE & ~SEGF)
#define SEVEN_SEGS_ONE		(~SEGB & ~SEGC)
#define	SEVEN_SEGS_TWO		(~SEGA & ~SEGB & ~SEGD & ~SEGE & ~SEGG)	
#define	SEVEN_SEGS_THREE	(~SEGA & ~SEGB & ~SEGC & ~SEGD & ~SEGG)	
#define	SEVEN_SEGS_FOUR		(~SEGB & ~SEGC & ~SEGF & ~SEGG)	
#define	SEVEN_SEGS_FIVE		(~SEGA & ~SEGC & ~SEGD & ~SEGF & ~SEGG)	
#define	SEVEN_SEGS_SIX		(~SEGA & ~SEGC & ~SEGD & ~SEGE & ~SEGF & ~SEGG)	
#define	SEVEN_SEGS_SEVEN	(~SEGA & ~SEGB & ~SEGC & ~SEGG)	
#define	SEVEN_SEGS_EIGHT	(~SEGA & ~SEGB & ~SEGC & ~SEGD & ~SEGE & ~SEGF & ~SEGG)	
#define	SEVEN_SEGS_NINE		(~SEGA & ~SEGB & ~SEGC & ~SEGD & ~SEGF & ~SEGG)	

#define SEVEN_SEGS_G		(~SEGA & ~SEGF & ~SEGE & ~SEGD & ~SEGC)
#define SEVEN_SEGS_V		(~SEGF & ~SEGE & ~SEGD & ~SEGC & ~SEGB)
#define SEVEN_SEGS_C		(~SEGA & ~SEGF & ~SEGE & ~SEGD)
#define SEVEN_SEGS_SPACE	(~SEGG)
#define SEVEN_SEGS_K		(~SEGG & ~SEGF & ~SEGE & ~SEGB & ~SEGC)
#define SEVEN_SEGS_T		(~SEGA & ~SEGF & ~SEGE)
#define SEVEN_SEGS_R		(~SEGA & ~SEGB & ~SEGC & ~SEGE & ~SEGF & ~SEGG)



static GPIO_Type *rGpio = GPIO;

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

static const uint8_t bBCD7Segs[] =
{
	SEVEN_SEGS_ZERO,	// 0
	SEVEN_SEGS_ONE,		// 1
	SEVEN_SEGS_TWO,		// 2
	SEVEN_SEGS_THREE,	// 3
	SEVEN_SEGS_FOUR,	// 4
	SEVEN_SEGS_FIVE,	// 5
	SEVEN_SEGS_SIX,		// 6
	SEVEN_SEGS_SEVEN,	// 7
	SEVEN_SEGS_EIGHT,	// 8
	SEVEN_SEGS_NINE,	// 9
	
};

static const uint8_t initials[] =
{
	SEVEN_SEGS_G,
	SEVEN_SEGS_V,
	SEVEN_SEGS_C,
	SEVEN_SEGS_SPACE,
	SEVEN_SEGS_K,
	SEVEN_SEGS_V,
	SEVEN_SEGS_T,
	SEVEN_SEGS_R,

};
//------------------------------------------------------------------------------
/*!
    \fn			vfnInitPortsDisplay
    \param		none
    \return		none
    \brief  	Init ports pins for the 7 segments display
*/
//------------------------------------------------------------------------------
void vfnInitPortsDisplay(void)
{

}
//------------------------------------------------------------------------------
void vfnDisplayCounter()
{
	static uint8_t counter = 0;
	rGpio->SET[RGB_PORT] = 0xFF;
	rGpio->CLR[RGB_PORT] = ~bBCD7Segs[counter];
	counter++;

	if (counter == 10)
	{
		counter = 0;
	}
}

void vfnDisplayInitials()
{
	static uint8_t counter = 0;
	rGpio->SET[RGB_PORT] = 0xFF;
	rGpio->CLR[RGB_PORT] = ~initials[counter];
	counter++;

	if (counter == 8)
	{
		counter = 0;
	}
}


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
