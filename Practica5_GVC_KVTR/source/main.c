#include "board.h"
#include "btn_debounce.h"
#include "gpio4Displays.h"
#include "init_switch.h"
#include "SwTimers.h"
#include "utick_timer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY 0x2710
#define MAX_SEC 60
#define MAX_MIN 60
#define MAX_HRS 24
#define RESTART 0
#define ONESECOND 1000000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void updateClock();
void updateStopwatch();
void updateTimer();
void vfnTimerAssignAndInit();

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint8_t gbTimerStatus;
static uint8_t gbTimer;

uint16_t gCurrentState = (1 << BTN0);
uint16_t gLastState = (1 << BTN0);
uint8_t bBotonFlag = 0x00;

uint8_t bHours = 0;
uint8_t bMinutes = 0;
uint8_t bSeconds = 0;

uint8_t bStopwatchSeconds = 0;
uint8_t bStopwatchMinutes = 0;
uint8_t bStopwatchRunning = 0;

uint8_t bTimerMinutes = 0;
uint8_t bTimerSeconds = 0;
uint8_t bTimerRunning = 0;
uint8_t bTimerBlink = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void) {
    volatile uint32_t wDelay = DELAY;
    uint8_t switchValue;

    /* Init hardware */
    vfnInitGpios();
    vfnInit_Btn();
    vfnInitSwith();
    vfnSwTimers_Init();
    vfnTimerAssignAndInit();

    /* Main loop */
    while (1) {
    	vfnSwTimers_Task();
    	gbTimerStatus = bfnSwTimers_GetStatus(gbTimer);
        switchValue = wSwitchValue();

        if (!gbTimerStatus) {

            if (switchValue == 0x1) { // Clock running
                updateClock();
            } else if (switchValue == 0x2) { // Stopwatch running
                updateStopwatch();
            } else if (switchValue == 0x4) { // Timer running
            	bTimerRunning = 1;
            	bTimerBlink = 0;
            	updateTimer();
            } else if (switchValue == 0xA) { // Stopwatch reset
                bStopwatchSeconds = RESTART;
                bStopwatchMinutes = RESTART;
            }
            vfnSwTimers_StartTimer(gbTimer, ONESECOND);
        }

        /* Button logic */
        gCurrentState = bfnReturn();
        uint16_t buttonStateChange = gCurrentState ^ gLastState;
        if (buttonStateChange) {
            if ((buttonStateChange & (1 << BTN0)) && (!(gCurrentState & (1 << BTN0)))) {
            	bBotonFlag = 1;
                // BTN0 pressed
                if (switchValue == 0x9) { // Clock setup - increment hours
					bHours++;
					if (bHours >= MAX_HRS) {
						bHours = RESTART;
					}
                } else if (switchValue == 0xC) { // Timer setup - increment minutes
                    bTimerMinutes = (bTimerMinutes + 1) % MAX_MIN;
                } else if (switchValue == 0x2) { //Start/Resume Stopwatch
                    bStopwatchRunning = 1;
                }
            }
            if ((buttonStateChange & (1 << BTN1)) && (!(gCurrentState & (1 << BTN1)))) {
                // BTN1 pressed
                if (switchValue == 0x9) { // Clock setup - increment minutes
                	bMinutes++;
					if (bMinutes >= MAX_MIN) {
						bMinutes = RESTART;
					}
                } else if (switchValue == 0xC) { // Timer setup - increment seconds
                    bTimerSeconds = (bTimerSeconds + 1) % MAX_SEC;
                } else if (switchValue == 0x2) { // Stop Stopwatch
                    bStopwatchRunning = 0;
                }
            }
        }
        gLastState = gCurrentState;

        /* Display update */
        vfnColumns_Driver(bSeconds); // Always update seconds
        if (switchValue == 0x1 || switchValue == 0x9) {
            vfnDisplay_Value(bMinutes, bHours, 0, 0); // Clock
        } else if (switchValue == 0x2) {
            vfnDisplay_Value(bStopwatchMinutes, 0, 1, bStopwatchSeconds); // Stopwatch
        } else if (switchValue == 0x4 || switchValue == 0xC) {
            vfnDisplay_Value(bTimerMinutes, bTimerSeconds / 10, 2, bTimerSeconds); // Timer
        }
    }
}

/*******************************************************************************
 * Functions Implementation
 ******************************************************************************/

void updateClock() {
    bSeconds++;
    if (bSeconds >= MAX_SEC) {
        bSeconds = RESTART;
        bMinutes++;
        if (bMinutes >= MAX_MIN) {
            bMinutes = RESTART;
            bHours++;
            if (bHours >= MAX_HRS) {
                bHours = RESTART;
            }
        }
    }
}

void updateStopwatch() {
    if (bStopwatchRunning) {
        bStopwatchSeconds++;
        if (bStopwatchSeconds >= MAX_SEC) {
            bStopwatchSeconds = RESTART;
            bStopwatchMinutes++;
            if (bStopwatchMinutes >= MAX_MIN) {
                bStopwatchMinutes = RESTART;
            }
        }
    }
}

void updateTimer() {
    if (bTimerRunning) {
        if (bTimerMinutes == 0 && bTimerSeconds == 0) {
            bTimerRunning = 0; // Stop timer
        } else {
            if (bTimerSeconds == 0) {
                bTimerSeconds = MAX_SEC - 1;
                bTimerMinutes--;
            } else {
                bTimerSeconds--;
            }
        }
    }
}

void vfnTimerAssignAndInit(void)
{
	gbTimer = bfnSwTimers_RequestTimer();
	vfnSwTimers_StartTimer(gbTimer,ONESECOND);
}

