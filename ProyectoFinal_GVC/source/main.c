#include "board.h"
#include "ctimer_driver.h"
#include "btn_debounce.h"
#include "sensor_gpio.h"
#include "SwTimers.h"
#include "utick_timer.h"
#include "gpio4Displays.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PWM_FREQ 5000
#define CH1 1
#define CH2 2
#define ARRAY_SIZE2 16
#define PULSO_POR_REVOLUCION 1

// Intervalo de detección del sensor Hall en microsegundos (1 ms = 1000 us)
#define HALL_SENSOR_INTERVAL_US 500
#define ONESECOND 1000000
#define PID_INTERVAL_US 10000  // 10 ms = 0.01 s


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void vfnHallSensorTimerAssignAndInit(void);
void vfnRpmTimerAssignAndInit(void);
void vfnPidTimerAssignAndInit(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
// Variables para el sensor Hall
volatile uint32_t g_pulses_in_period = 0;
volatile uint32_t g_rpm = 0;
uint8_t bPrev_sensor_state = 0;

static uint8_t gbHallSensorTimerID;
static uint8_t gbRpmTimerID;
static uint8_t gbPidTimerID;

// Variables para PWM y botones
uint16_t dutyArray[] = {60, 62, 65, 67, 70, 72, 75, 77, 80, 82, 85, 87, 90, 92, 95, 99};
volatile uint8_t currentSpeedIndex = 0;
uint16_t gCurrentState = (1 << BTN0);
uint16_t gLastState = (1 << BTN0);
uint8_t bBotonFlag = 0x00;

//Variables para PID
float setpoint = 100.0;      // Ej: velocidad deseada (ajustable)
float medida = 0.0;          // Velocidad actual del encoder

float error = 0.0;
float errorAnterior = 0.0;
float integral = 0.0;
float salidaPID = 0.0;

// Parámetros del controlador PID
float Kp = 1.532e-5;
float Ki = 5e-11;
float Ts = 0.01;

// PWM
uint8_t pwmSalida = 0;
uint8_t pwmMax = 100;
uint8_t pwmMin = 0;


void vfnRpmTimerAssignAndInit(void) {
    gbRpmTimerID = bfnSwTimers_RequestTimer();
    vfnSwTimers_StartTimer(gbRpmTimerID, ONESECOND);
}

void vfnHallSensorTimerAssignAndInit(void)
{
    gbHallSensorTimerID = bfnSwTimers_RequestTimer();
    vfnSwTimers_StartTimer(gbHallSensorTimerID, HALL_SENSOR_INTERVAL_US);
}

void vfnPidTimerAssignAndInit(void) {
    gbPidTimerID = bfnSwTimers_RequestTimer();
    vfnSwTimers_StartTimer(gbPidTimerID, PID_INTERVAL_US);
}

void setPWM(uint8_t dutyCycle) {
    if (dutyCycle > 100) dutyCycle = 100;
    vfnUpdate_PWM(dutyCycle, CH2);  // CH2 = canal donde está el motor
}


int main(void)
{
	/* Init hardware */
	vfnInitCTimerAndPins();
	CTIMER_StartTimer();
	vfnSwTimers_Init();

    vfnInit_Btn();
    vfnInitHallSensor();
    vfnInitGpios();
	vfnSetUpPWM_Freq(PWM_FREQ,CH2);

	bPrev_sensor_state = wfnReadHallSensorState();
	vfnHallSensorTimerAssignAndInit();
	vfnRpmTimerAssignAndInit();
	vfnPidTimerAssignAndInit();

	while(1)
	{

		vfnSwTimers_Task();
		if (!bfnSwTimers_GetStatus(gbRpmTimerID))
		{
		    vfnSwTimers_StartTimer(gbRpmTimerID, 1000000); // Reiniciar el timer de 1 segundo

		    // Calcular RPM
		    g_rpm = (g_pulses_in_period * 60) / PULSO_POR_REVOLUCION;

		    // Reiniciar el contador de pulsos para el siguiente período
		    g_pulses_in_period = 0;
		}

		if(!bfnSwTimers_GetStatus(gbHallSensorTimerID))
		{
			vfnSwTimers_StartTimer(gbHallSensorTimerID, HALL_SENSOR_INTERVAL_US);
			uint8_t bcurrent_sensor_state = wfnReadHallSensorState();
			if (bcurrent_sensor_state != bPrev_sensor_state)
				{
					if (bcurrent_sensor_state == 1)
					{
						g_pulses_in_period++;
					}
					bPrev_sensor_state = bcurrent_sensor_state;
				}
			gCurrentState = bfnReturn();
		}
		uint16_t buttonStateChange = gCurrentState ^ gLastState;
		if (buttonStateChange) {
			if ((buttonStateChange & (1 << BTN0)) && (!(gCurrentState & (1 << BTN0)))) {
				bBotonFlag = 1;
				// BTN0 pressed
				if (currentSpeedIndex < (ARRAY_SIZE2 - 1))
				{
					currentSpeedIndex++;;
				}
				else
				{
					currentSpeedIndex = 0;
				}
			}
			if ((buttonStateChange & (1 << BTN1)) && (!(gCurrentState & (1 << BTN1)))) {
				// BTN1 pressed
				if (currentSpeedIndex > 0)
				{
					currentSpeedIndex--;
				}
				else
				{
					currentSpeedIndex = (ARRAY_SIZE2 - 1);
				}
			}
			vfnUpdate_PWM(dutyArray[currentSpeedIndex],CH2);
		}
		gLastState = gCurrentState;

		if (!bfnSwTimers_GetStatus(gbPidTimerID))
		{
			vfnSwTimers_StartTimer(gbPidTimerID, PID_INTERVAL_US);

			medida = (float)g_rpm;  // ⬅️ Usamos la RPM como feedback

			error = setpoint - medida;
			integral += error * Ts;

			salidaPID = Kp * error + Ki * integral;

			// Limitar el valor de salida
			if (salidaPID > pwmMax) salidaPID = pwmMax;
			else if (salidaPID < pwmMin) salidaPID = pwmMin;

			pwmSalida = (uint8_t)salidaPID;
			setPWM(pwmSalida);
		}

		vfnDisplayRPM(g_rpm);
		vfnColumns_Driver(0); // Asegurarse de que el multiplexado del display se siga ejecutando constantemente
	}

}
