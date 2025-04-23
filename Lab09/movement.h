#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "open_interface.h"

//Moves the bot forward by the desired distance
int move_forward(oi_t *sensor, float centimeters);

//Turns the bot clockwise by the desired angle
void turn_clockwise(oi_t *sensor, double degrees);
void turn_counterclockwise(oi_t *sensor, double degrees);
void reverse(oi_t *sensor, float centimeters);


#endif /* MOVEMENT_H_ */
