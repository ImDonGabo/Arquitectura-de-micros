///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section                        
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include "utick_timer.h"
#include "gpio_driver.h"
#include "SwTimers.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////

#define SWTIMERS_MAX_TIMERS		(8)

#define ENABLE_TIMER(Channel)			(gbTimersEnabled |= (1<<Channel))

#define DISABLE_TIMER(Channel)			(gbTimersEnabled &= ~(1<<Channel))

#define CHECK_TIMER(Channel)			(gbTimersEnabled & (1<<Channel))
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section                        
///////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Function Prototypes Section                 
///////////////////////////////////////////////////////////////////////////////////////////////////

static void vfnSwTimer_InitHwTimer (void);

static uint8_t bfnSwTimer_GetHwTimerStatus (void);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section                   
///////////////////////////////////////////////////////////////////////////////////////////////////


static uint16_t gwCounters[SWTIMERS_MAX_TIMERS];

static uint8_t gbTimersEnabled = 0;

static uint8_t gbTimersAllocated = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section                       
///////////////////////////////////////////////////////////////////////////////////////////////////

void vfnSwTimers_Init(void)
{
	gbTimersEnabled = 0;
	gbTimersAllocated = 0;
	/* Init HW timer */
	vfnSwTimer_InitHwTimer();
}

void vfnSwTimers_Task(void)
{
	uint8_t TimerOffset = 0;
	uint8_t HwTimerStatus = 0;
	
	/* check if a timeout has passed */
	HwTimerStatus = bfnSwTimer_GetHwTimerStatus();
	
	if(HwTimerStatus)
	{
		while(TimerOffset < SWTIMERS_MAX_TIMERS)
		{
			if(CHECK_TIMER(TimerOffset))
			{
				/* decrement timer only when not zero */
				if(gwCounters[TimerOffset])
				{
					gwCounters[TimerOffset]--;
				}
			}
			
			TimerOffset++;
		}
	}
}

uint8_t bfnSwTimers_RequestTimer(void)
{
	uint8_t TimerOffset = 0;
	
	while(TimerOffset < SWTIMERS_MAX_TIMERS)
	{
		/* If the bit is 0, means the timer is free */
		/* if is 1, means the timer is allocated and must move to the next*/
		if(!(gbTimersAllocated & 1<<TimerOffset))
		{
			gbTimersAllocated |= (1<<TimerOffset);
			/* exit the cycle*/
			break;
		}
		else
		{
			TimerOffset++;
		}
	}
	
	/* send error in case there wasn't any timer available*/
	if(TimerOffset > SWTIMERS_MAX_TIMERS)
	{
		TimerOffset = 0xFF;
	}
	
	return(TimerOffset);
}

void vfnSwTimers_StartTimer(uint8_t Channel, uint32_t Timeout)
{
	if(Channel < SWTIMERS_MAX_TIMERS)
	{
		/* get the timeout in time base counts */
		Timeout = Timeout/SWTIMERS_TIME_BASE;
		gwCounters[Channel] = Timeout;
		ENABLE_TIMER(Channel);
		
	}
} 

uint8_t bfnSwTimers_GetStatus(uint8_t Channel)
{
	uint8_t TimerStatus = 1;
	
	/* first confirm the timer is active*/
	if(CHECK_TIMER(Channel))
	{
		/* when the timer is 0 means is done*/
		if(!gwCounters[Channel])
		{
			TimerStatus = 0;
		}		
	}
	
	return(TimerStatus);
}

static void vfnSwTimer_InitHwTimer (void)
{
	/* place here your HW Timer init functions*/
	vfnUTICKinit();
}

static uint8_t bfnSwTimer_GetHwTimerStatus (void)
{
	uint8_t bStatus;
	/* place here your getstatus function from HW timer */
	bStatus = bfnUTICKGetStatus();
	
	if(bStatus)
	{
		vfnUTICKClearStatus();
	}
	
	return (bStatus);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////
