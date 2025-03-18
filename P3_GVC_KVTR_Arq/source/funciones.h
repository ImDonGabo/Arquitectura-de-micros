/*
 * funciones.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Gabriel Valle  y Katya Torres
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H

#include "board.h"

//PROTIPOS FUNCIONES
uint8_t bfnToUpperCase (uint8_t  bChar);
uint8_t bfnToLowerCase (uint8_t bChar);
uint8_t bfnIsPrint (uint8_t bChar);
uint8_t bfnIsHex (uint8_t bChar);
uint16_t wfnStrLen (uint8_t *bpString);
uint8_t bfnShiftLeft (uint8_t  bData, uint8_t bShift);
uint8_t bfnShiftRight (uint8_t bData, uint8_t bShift);
void vfnMemCpy (uint8_t *bpSource, uint8_t  *bpDest, uint16_t wSize);
void vfnMemSet(uint8_t *bpDest, uint8_t bByteToFill, uint16_t  wSize);
uint8_t bfnFindMax(uint8_t *bpDest, uint16_t wSize);
uint8_t bfnFindMin(uint8_t *bpDest, uint16_t  wSize);
uint8_t bfnStrCmp(uint8_t *bpSource, uint8_t *bpDest, uint16_t wSize);
uint8_t *bpfnByteAddress(uint8_t *bpString, uint8_t bCharToFind, uint16_t wSize);
uint16_t  wfnSum (uint8_t *bpSrc, uint8_t bSize);
uint8_t bfnAvg (uint8_t *bpSrc, uint8_t bN);
void vfnReverseArray(uint8_t *bpArray, uint16_t wSize);

#endif /* INIT_RGB_H_ */
