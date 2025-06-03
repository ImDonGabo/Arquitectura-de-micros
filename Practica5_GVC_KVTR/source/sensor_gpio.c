#include "sensor_gpio.h"

#define SENSOR_PORT 0
#define SENSOR_PIN 13
#define SENSOR_MASK 0x2000

static GPIO_Type *rGpio = GPIO;

void vfnInitHallSensor() {
    SYSCON_Type *rClocks = SYSCON;
    IOCON_Type *rIocon = IOCON;

    /* Enable clocks */
    rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK | SYSCON_AHBCLKCTRL0_GPIO0_MASK;

    /* Configure pins */
    rIocon->PIO[SENSOR_PORT][SENSOR_PIN] = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;

    /* Set pin directions (input) */
    rGpio->DIR[SENSOR_PORT] &= ~SENSOR_MASK;
}

uint8_t wfnReadHallSensorState() {
	uint32_t rawValue = (rGpio->PIN[SENSOR_PORT] & SENSOR_MASK);
	return (uint8_t)(rawValue >> 13);
}
