/*
 * funciones.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Gabriel Valle y Katya Torres
 */

 #include "funciones.h"
 #include "init_rgb.h"

 //DEFINE'S
 #define difference_lower_upper 0x20
 #define last_printable_char 0x20
 #define DEL_char 0x7F
 #define cero_hexa 0x30
 #define nueve_hexa 0x39

 uint8_t bfnToUpperCase (uint8_t  bChar)
 {
     if (bChar >= 'a' && bChar <= 'z') {
             vfnGreenOn();
             return bChar - (difference_lower_upper); // Convert to UPCASE
         }
        vfnRedOn();
         return bChar; // Returns the same character if not a lowercase
 }

 uint8_t bfnToLowerCase (uint8_t bChar)
 {
     if (bChar >= 'A' && bChar <= 'Z') {
            vfnGreenOn();
             return bChar + (difference_lower_upper); // Convert to lowcase
         }
        vfnRedOn();
         return bChar; // Returns the same character if not a UPPERCASE

 }

 uint8_t bfnIsPrint (uint8_t bChar)
 {
     if (!(bChar >= 0 && bChar <= last_printable_char) || !(bChar == DEL_char))
     {
        vfnGreenOn();
         return 1;
     }
    vfnRedOn();
     return 0;
 }

 uint8_t bfnIsHex (uint8_t bChar)
 {
     if((bChar >= cero_hexa && bChar <= nueve_hexa) || (bChar >= 'A' && bChar <= 'F'))
     {
        vfnGreenOn();
         return 1;
     }
    vfnRedOn();
     return 0;
 }

 uint16_t wfnStrLen(uint8_t *bpString)
 {
     uint16_t length = 0;
     while (bpString[length] != 0) {
         length++;
     }
    vfnGreenOn();
     return length;
 }

 uint8_t bfnShiftLeft (uint8_t  bData, uint8_t bShift)
 {
     if (bShift > 8) {
        vfnRedOn();
             return bData; // If bShift is bigger than 8, returns the same value
     }
    vfnGreenOn();
     return bData << bShift; // Moves bData to the left bShift positions
 }

 uint8_t bfnShiftRight (uint8_t bData, uint8_t bShift)
 {
     if (bShift > 8) {
        vfnRedOn();
             return bData; // If bShift is bigger than 8, returns the same value
     }
    vfnGreenOn();
     return bData >> bShift; // Moves bData to the left bShift positions
 }

 void vfnMemCpy (uint8_t *bpSource, uint8_t  *bpDest, uint16_t wSize)
 {
     for (uint16_t i = 0; i < wSize; i++) {
             bpDest[i] = bpSource[i]; // Copy each byte from source to destiny
     }
     vfnGreenOn();
 }

 void vfnMemSet(uint8_t *bpDest, uint8_t bByteToFill, uint16_t wSize)
 {
     for (uint16_t i = 0; i < wSize; i++) {
         bpDest[i] = bByteToFill; // Fills each byte with the destiny
     }
    vfnGreenOn();
 }

 uint8_t bfnFindMax(uint8_t *bpDest, uint16_t wSize)
 {
     uint8_t maxVal = 0;
     for (uint16_t i = 0; i < wSize; i++) {
         if (bpDest[i] > maxVal) {
             maxVal = bpDest[i]; // Updates max value
         }
     }
    vfnGreenOn();
     return maxVal;
 }

 uint8_t bfnFindMin(uint8_t *bpDest, uint16_t wSize)
 {
     if (wSize == 0)
     {
        vfnRedOn();
         return 0; // Empty case
     }

     uint8_t minVal = 255;
     for (uint16_t i = 0; i < wSize; i++) {
         if (bpDest[i] < minVal) {
             minVal = bpDest[i]; // Updates min value
         }
     }
    vfnGreenOn();
     return minVal;
 }

 uint8_t bfnStrCmp(uint8_t *bpSource, uint8_t *bpDest, uint16_t wSize)
 {
     for (uint16_t i = 0; i < wSize; i++) {
         if (bpSource[i] != bpDest[i]) {
            vfnRedOn();
             return 0; // Return 0 if the contents are different
         }
     }
    vfnGreenOn();
     return 1; // Return 1 if the contents are equal
 }

 uint8_t *bpfnByteAddress(uint8_t *bpString, uint8_t bCharToFind, uint16_t wSize)
 {
     for (uint16_t i = 0; i < wSize; i++) {
         if (bpString[i] == bCharToFind) {
            vfnGreenOn();
             return &bpString[i]; // Return the address where the char is
         }
     }
    vfnRedOn();
     return NULL; // Return NULL if the char is not in the string
 }

 uint16_t wfnSum(uint8_t *bpSrc, uint8_t bSize)
 {
     uint16_t sum = 0;
     for (uint8_t i = 0; i < bSize; i++) {
         sum += bpSrc[i]; // Sums each number of the Src
     }
    vfnGreenOn();
     return sum;
 }

 uint8_t bfnAvg(uint8_t *bpSrc, uint8_t bN)
 {
     if (bN == 0){
        vfnRedOn();
         return 0; // empty Src case
     }
    vfnGreenOn();
     return wfnSum(bpSrc, bN) / bN; // Calculates the Average
 }

 void vfnReverseArray(uint8_t *bpArray, uint16_t wSize)
 {
     uint16_t left = 0, right = wSize - 1;
     while (left < right) {
         uint8_t temp = bpArray[left];
         bpArray[left] = bpArray[right];
         bpArray[right] = temp;
         left++;
         right--;
     }
     vfnGreenOn();
 }
