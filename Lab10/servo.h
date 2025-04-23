/*
 * servo.h
 *
 *  Created on: Apr 15, 2025
 *      Author: yohimhim
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "button.h"
#include "lcd.h"
#include "timer.h"

void servo_calibrate(void);
void servo_init(void);
void servo_move(int16_t degrees);

#endif /* SERVO_H_ */
