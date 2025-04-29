/*
 * init_switch.h
 *
 *  Created on: Mar 12, 2025
 *      Author: Mario Castaneda
 */

#ifndef INIT_SWITCH_H_
#define INIT_SWITCH_H_

#include "board.h"

#define BTN5_PORT 0
#define BTN9_PORT 1
#define BTN5 5
#define BTN9 9

void vfnInitSwith();
uint8_t wSwitchValue();

#endif /* INIT_SWITCH_H_ */
