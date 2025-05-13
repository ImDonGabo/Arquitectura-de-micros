#include "gpio4Displays.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SEGMENT_A    (0)
#define SEGMENT_B    (1)
#define SEGMENT_C    (2)
#define SEGMENT_D    (3)
#define SEGMENT_E    (4)
#define SEGMENT_F    (5)
#define SEGMENT_G    (6)
#define SEG_DP       (7)

#define D1_PIN       (8)
#define D2_PIN       (10)
#define D3_PIN       (20)
#define D4_PIN       (21)

#define SEGA (1 << SEGMENT_A)
#define SEGB (1 << SEGMENT_B)
#define SEGC (1 << SEGMENT_C)
#define SEGD (1 << SEGMENT_D)
#define SEGE (1 << SEGMENT_E)
#define SEGF (1 << SEGMENT_F)
#define SEGG (1 << SEGMENT_G)

#define SEVEN_SEGS_ZERO     (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF)
#define SEVEN_SEGS_ONE      (SEGB | SEGC)
#define SEVEN_SEGS_TWO      (SEGA | SEGB | SEGD | SEGE | SEGG)
#define SEVEN_SEGS_THREE    (SEGA | SEGB | SEGC | SEGD | SEGG)
#define SEVEN_SEGS_FOUR     (SEGB | SEGC | SEGF | SEGG)
#define SEVEN_SEGS_FIVE     (SEGA | SEGC | SEGD | SEGF | SEGG)
#define SEVEN_SEGS_SIX      (SEGA | SEGC | SEGD | SEGE | SEGF | SEGG)
#define SEVEN_SEGS_SEVEN    (SEGA | SEGB | SEGC | SEGG)
#define SEVEN_SEGS_EIGHT    (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG)
#define SEVEN_SEGS_NINE     (SEGA | SEGB | SEGC | SEGD | SEGF | SEGG)

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static GPIO_Type *rgGpio1 = GPIO;
static const uint32_t bDisplayDriver[] = {
    DISPLAY1,
    DISPLAY2,
    DISPLAY3,
    DISPLAY4,
};

#define TOTAL_DISPLAYS (sizeof(bDisplayDriver) / sizeof(bDisplayDriver[0]))

static const uint8_t bBCD7Segs[] = {
    SEVEN_SEGS_ZERO,
    SEVEN_SEGS_ONE,
    SEVEN_SEGS_TWO,
    SEVEN_SEGS_THREE,
    SEVEN_SEGS_FOUR,
    SEVEN_SEGS_FIVE,
    SEVEN_SEGS_SIX,
    SEVEN_SEGS_SEVEN,
    SEVEN_SEGS_EIGHT,
    SEVEN_SEGS_NINE
};

static uint8_t bDisplayIdx = 0;
uint8_t gbaDisplayData[TOTAL_DISPLAYS] = {0};

/*******************************************************************************
 * Code
 ******************************************************************************/

void vfnInitGpios() {
    SYSCON_Type *rSyscon = SYSCON;
    IOCON_Type *rPinSetup = IOCON;

    /* Enable clocks */
    rSyscon->AHBCLKCTRL.AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_IOCON_MASK | SYSCON_PRESETCTRL0_GPIO1_RST_MASK | SYSCON_PRESETCTRL0_GPIO0_RST_MASK;

    /* Configure pins */
    rPinSetup->PIO[PORT1_LED][SEGMENT_A] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_B] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_C] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_D] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_E] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_F] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEGMENT_G] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][SEG_DP] |= IOCON_PIO_FUNC(0);

    rPinSetup->PIO[PORT1_LED][D1_PIN] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][D2_PIN] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][D3_PIN] |= IOCON_PIO_FUNC(0);
    rPinSetup->PIO[PORT1_LED][D4_PIN] |= IOCON_PIO_FUNC(0);

    /* Set pin directions */
    rgGpio1->DIR[PORT1_LED] |= ALL_PORT1 | DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;

    /* Turn off all */
    rgGpio1->CLR[PORT1_LED] |= ALL_PORT1 | DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;
}

void vfnColumns_Driver(uint8_t bSeconds) {
    /* Turn off all displays */
    rgGpio1->CLR[PORT1_LED] |= ALL_PORT1;
    rgGpio1->SET[PORT1_LED] |= DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4;

    vfnToggleDotPoint(0); // Default: DP off

    /* Display data */
    rgGpio1->SET[PORT1_LED] = (bBCD7Segs[gbaDisplayData[bDisplayIdx]]);

    /* Select the display */
    rgGpio1->CLR[PORT1_LED] = (bDisplayDriver[bDisplayIdx]);

    /* Update display index */
    if (++bDisplayIdx >= TOTAL_DISPLAYS) {
        bDisplayIdx = 0;
    }

    // Toggle decimal point every half second (adjust as needed)
    if (bSeconds % 2 == 0) {
        vfnToggleDotPoint(1);
    } else {
        vfnToggleDotPoint(0);
    }
}

void vfnDisplay_Value(uint8_t bMin, uint8_t bMajor, uint8_t bMode, uint8_t bMinor) {
    if (bMode == 0) { // Clock
        gbaDisplayData[3] = bMin % 10;
        gbaDisplayData[2] = bMin / 10;
        gbaDisplayData[1] = bMajor % 10;
        gbaDisplayData[0] = bMajor / 10;
    } else if (bMode == 1) { // Stopwatch
        gbaDisplayData[3] = bMinor % 10;
        gbaDisplayData[2] = bMinor / 10;
        gbaDisplayData[1] = bMin % 10;
        gbaDisplayData[0] = bMin / 10;
    } else if (bMode == 2 || bMode == 3) { // Timer
        gbaDisplayData[3] = bMinor % 10;
        gbaDisplayData[2] = bMinor / 10;
        gbaDisplayData[1] = bMin % 10;
        gbaDisplayData[0] = bMin / 10;
    }
}

void vfnToggleDotPoint(uint8_t bState) {
    if (bState) {
        rgGpio1->CLR[PORT1_LED] = (1 << SEG_DP);
    } else {
        rgGpio1->SET[PORT1_LED] = (1 << SEG_DP);
    }
}


