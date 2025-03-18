/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"

#include "funciones.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DELAY 0xAA000
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t testChar = 'a';
uint8_t testArray[] = {10, 20, 30, 40, 50};
uint8_t testDest[5];
uint16_t size = 5;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	BOARD_InitHardware();
	vfnInitRGB();
    // Fn 1
    PRINTF("The letter before the function bfnToUpperCase: %c\r\n", testChar);
    uint8_t bUpperCase = bfnToUpperCase(testChar);
    PRINTF("The letter after the function: %c\r\n", bUpperCase);

    // Fn 2
    PRINTF("The letter before the function bfnToLowerCase: %c\r\n", bUpperCase);
    uint8_t bLowerCase = bfnToLowerCase(bUpperCase);
    PRINTF("The letter after the function: %c\r\n", bLowerCase);

    // Fn 3
    PRINTF("Is the letter printable? : 1 = Yes, 0 = No \r\n");
    uint8_t bResult = bfnIsPrint(testChar);
    PRINTF("The result is %d\r\n", bResult);

    // Fn 4
    PRINTF("Is the character a hexadecimal value? : 1 = Yes, 0 = No \r\n");
    bResult = bfnIsHex(testChar);
    PRINTF("The result is %d\r\n", bResult);

    // Fn 5
    uint16_t length = wfnStrLen(testArray);
    PRINTF("String length: %d\r\n", length);

    // Fn 6
    uint8_t shiftedLeft = bfnShiftLeft(5, 1);
    PRINTF("Shift Left result: %d\r\n", shiftedLeft);

    // Fn 7
    uint8_t shiftedRight = bfnShiftRight(5, 1);
    PRINTF("Shift Right result: %d\r\n", shiftedRight);

    // Fn 8
    vfnMemCpy(testArray, testDest, size);
    PRINTF("Memory Copy completed.\r\n");

    // Fn 9
    vfnMemSet(testDest, 0, size);
    PRINTF("Memory Set completed.\r\n");

    // Fn 10
    uint8_t maxVal = bfnFindMax(testArray, size);
    PRINTF("Max Value: %d\r\n", maxVal);

    // Fn 11
    uint8_t minVal = bfnFindMin(testArray, size);
    PRINTF("Min Value: %d\r\n", minVal);

    // Fn 12
    bResult = bfnStrCmp(testArray, testDest, size);
    PRINTF("String Compare result: %d\r\n", bResult);

    // Fn 13
    uint8_t *byteAddr = bpfnByteAddress(testArray, 30, size);
    PRINTF("Byte Address: %p\r\n", byteAddr);

    // Fn 14
    uint16_t sum = wfnSum(testArray, size);
    PRINTF("Sum: %d\r\n", sum);

    // Fn 15
    uint8_t avg = bfnAvg(testArray, size);
    PRINTF("Average: %d\r\n", avg);

    // Fn 16
    vfnReverseArray(testArray, size);
    PRINTF("Array reversed.\r\n");

}
