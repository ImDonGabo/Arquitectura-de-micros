#include "board.h"
#include "Matriz.h"
#include "btn_debounce.h"
#include "SwTimers.h"
#include "utick_timer.h"
#include "gpio_driver.h"

#define BLUE_LED_TOGGLE_RATE		1000000
#define SECOND_RATE 		1000000
#define DISPLAY_RATE		1000
#define BUTTON_RATE			20000
#define DELAY 	0x3000

#define BTN1FLAG        2
#define BTN2FLAG        1

void vfnMemCpy(uint8_t *bpSource, uint8_t *bpDest, uint16_t wSize);
void vfnTimerAssignAndInit(void);

static uint8_t gbDisplayTimerStatus;
static uint8_t gbDisplayTimer;
static uint8_t gbButtonTimerStatus;
static uint8_t gbButtonTimer;
static uint8_t gbCronometroTimerStatus;
static uint8_t gbCronometroTimer;
static uint8_t gbBlueLedTimerStatus;
static uint8_t gbBlueLedTimer;

volatile uint32_t dwDelay = DELAY;

uint16_t gCurrentState = (1 << BTN0)|(1 << BTN1);
uint16_t gLastState = (1 << BTN0)|(1 << BTN1);
uint8_t bBotonFlag	= 0;
uint16_t bChange;

uint8_t counter = 0;
extern  uint8_t bMatrixRows[16][8];

/*PID variables*/
// Variables para PID
float setpoint = 100.0;      // Ej: velocidad deseada (ajustable)
float medida = 0.0;          // Velocidad actual del encoder

float error = 0.0;
float errorAnterior = 0.0;
float integral = 0.0;
float salidaPID = 0.0;

// Parámetros del controlador PID
float Kp = 1.532e-5;
float Ki = 5e-11;
float Ts = 0.01;  // 10 ms (ajustar según frecuencia real de muestreo)

// PWM
uint8_t pwmSalida = 0;
uint8_t pwmMax = 100;
uint8_t pwmMin = 0;


int main(void)
{
	vfnInitGpios();
//	vfnGpioInitRGB();
	vfnSwTimers_Init();
	vfnTimerAssignAndInit();
	vfnInit_Btn();

	vfnMatrix_Value();

    while (1)
    {
    	vfnSwTimers_Task();

    	gbDisplayTimerStatus = bfnSwTimers_GetStatus(gbDisplayTimer);
    	if (!gbDisplayTimerStatus)
        {
            vfnColumns_Driver();
			vfnSwTimers_StartTimer(gbDisplayTimer,DISPLAY_RATE);
			gbDisplayTimerStatus = 0;
        }

		gbButtonTimerStatus = bfnSwTimers_GetStatus(gbButtonTimer);
		if(!gbButtonTimerStatus)
		{
			gCurrentState = bfnReturn();
			bChange = gCurrentState ^ gLastState;
			if(bChange)
			{
				// Detección de flanco de bajada (botón presionado)
				if((bChange & (1 << BTN0)) && (!(gCurrentState & (1<<BTN0))))
				{
					// Se presionó BTN0
					// No hacemos nada aquí para evitar el incremento/decremento continuo
				}
				if((bChange & (1 << BTN1)) && (!(gCurrentState & (1<<BTN1))))
				{
					// Se presionó BTN1
					// No hacemos nada aquí para evitar el incremento/decremento continuo
				}
				// Detección de flanco de subida (botón liberado)
				if((bChange & (1 << BTN0)) && ((gCurrentState & (1<<BTN0))))
				{
					// Se liberó BTN0, decrementamos el contador
					bBotonFlag = BTN2FLAG;
				}
				if((bChange & (1 << BTN1)) && ((gCurrentState & (1<<BTN1))))
				{
					// Se liberó BTN1, incrementamos el contador
					bBotonFlag = BTN1FLAG;
				}
			}
			dwDelay = DELAY;
			vfnSwTimers_StartTimer(gbButtonTimer,BUTTON_RATE);
			gbButtonTimerStatus = 0;
			gLastState = gCurrentState;
		}

		if(bBotonFlag == BTN1FLAG)
		{
			bBotonFlag = 0;
			vfnMemCpy(&matrixHexDigits[counter][0],bMatrixRows[0],8);
			counter++;
    		if(counter >= 16){
    			counter = 0;
    		}
		}

		if(bBotonFlag == BTN2FLAG)
		{
			bBotonFlag = 0;
			vfnMemCpy(&matrixHexDigits[counter][0],bMatrixRows[0],8);
			if (counter > 0) {
				counter--;
			} else {
				counter = 15;
			}
		}

		gbBlueLedTimerStatus = bfnSwTimers_GetStatus(gbBlueLedTimer);
		if(!gbBlueLedTimerStatus)
		{
			vfnBLUE_Toggle();
			vfnSwTimers_StartTimer(gbBlueLedTimer, BLUE_LED_TOGGLE_RATE);
			gbBlueLedTimerStatus = 0;
		}
    }
}

void vfnMemCpy(uint8_t *bpSource, uint8_t *bpDest, uint16_t wSize)
{
    while (wSize--)
    {
        *bpDest++ = *bpSource++;
    }
}

void vfnTimerAssignAndInit(void)
{
	gbDisplayTimer = bfnSwTimers_RequestTimer();
	vfnSwTimers_StartTimer(gbDisplayTimer,DISPLAY_RATE);

	gbButtonTimer = bfnSwTimers_RequestTimer();
	vfnSwTimers_StartTimer(gbButtonTimer,BUTTON_RATE);

	gbBlueLedTimer =  bfnSwTimers_RequestTimer();
	vfnSwTimers_StartTimer(gbBlueLedTimer,BLUE_LED_TOGGLE_RATE);
}
