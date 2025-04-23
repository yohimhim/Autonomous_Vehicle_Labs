/*
 * movement.c
 *
 *  Created on: Feb 11, 2025
 *      Author: yohimhim
 */
#include "lcd.h"
#include "open_interface.h"
#include "timer.h"


double move_forward(oi_t *sensor_data, double distance_mm)
{
    oi_setWheels(60, 60);
    double sum = 0;

    while (sum < distance_mm) //keep going until sum is greater than distance wanted
    {
        oi_update(sensor_data);
        sum += sensor_data ->distance;
    }

    oi_setWheels(0,0);
    return sum;
}

