/*
 * sensor_gpio.h
 *
 *  Created on: Mar 12, 2025
 *      Author: Gabriel Valle y Katya Torres
 */

#ifndef SENSOR_GPIO_H_
#define SENSOR_GPIO_H_

#include "board.h"

void vfnInitHallSensor();
uint8_t wfnReadHallSensorState();

#endif
