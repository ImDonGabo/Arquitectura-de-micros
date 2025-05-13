#include "init_switch.h"

#define BTN0_PORT 0
#define BTN13 13
#define BTN14 14
#define BTN15 15
#define BTN16 16

#define SWITCH_MASK 0x1E000

static GPIO_Type *rGpio = GPIO;

void vfnInitSwith() {
    SYSCON_Type *rClocks = SYSCON;
    IOCON_Type *rIocon = IOCON;

    /* Enable clocks */
    rClocks->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK | SYSCON_AHBCLKCTRL0_GPIO0_MASK;

    /* Configure pins */
    rIocon->PIO[BTN0_PORT][BTN13] = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
    rIocon->PIO[BTN0_PORT][BTN14] = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
    rIocon->PIO[BTN0_PORT][BTN15] = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;
    rIocon->PIO[BTN0_PORT][BTN16] = IOCON_PIO_FUNC(0) | IOCON_PIO_DIGIMODE_MASK;

    /* Set pin directions (input) */
    rGpio->DIR[BTN0_PORT] &= ~SWITCH_MASK;
}

uint8_t wSwitchValue() {
    uint32_t rawValue = (rGpio->PIN[0] & SWITCH_MASK);
    return (uint8_t)(rawValue >> 13);
}
