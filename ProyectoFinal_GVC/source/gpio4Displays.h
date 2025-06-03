/*
 * gpio_matriz8x8.h
 *
 * Created on: Jan 27, 2024
 * Author: Mario Castaneda
 */
#ifndef GPIO4DISPLAYS_H_
#define GPIO4DISPLAYS_H_
/******************************************************************************/
/*Include files                                                             ***/
/******************************************************************************/
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RED_LED_PIN		0x04
#define BLUE_LED_PIN	0x06
#define GREN_LED_PIN	0x07
#define PORT1_LED		0x01
#define ALL_PORT1		0x7F // Note: Should be 0xFF if DP is included (P1.0 to P1.7)

#define DISPLAY1			( 1 << 8 )
#define DISPLAY2			( 1 << 10 )
#define DISPLAY3			( 1 << 20 )
#define DISPLAY4			( 1 << 21 )

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/
void vfnInitGpios();
// Functions for the 7-segment displays
void vfnColumns_Driver(uint8_t bSeconds);
void vfnDisplay_Value(uint8_t bMin, uint8_t bRelojH, uint8_t bMode, uint8_t bSec);
void vfnToggleDotPoint(uint8_t bState);
void vfnDisplayRPM(uint32_t rpm_value);
/*******************************************************************************
 * Local Variables
 ******************************************************************************/

 /******************************************************************************
 * Extern Variables Section
 ******************************************************************************/
extern uint8_t bClockSetupMode;
extern uint8_t bDisplayMode;
extern uint8_t bTimerMinutes;
extern uint8_t bTimerSeconds;
extern uint8_t bTimerBlink;
extern uint8_t bTimerRunning;
 /******************************************************************************
 * Extern Constants Section
 ******************************************************************************/

/*******************************************************************************
 * Function Prototypes Section
 ******************************************************************************/

/******************************************************************************/


/*******************************************************************************
 * End of File
 ******************************************************************************/



#endif /* GPIO4DISPLAYS_H_ */
