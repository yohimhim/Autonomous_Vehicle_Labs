#include "movement.h"
#include "open_interface.h"
#include "lcd.h"
#include <math.h>
//Moves the bot forward by the desired distance
int move_forward(oi_t *sensor, float centimeters) {
    double distance = 0;
    int bumped = 0; // flag to return if we hit an obstacle

    oi_setWheels(200, 200);

    while (distance < centimeters) {
        oi_update(sensor);

        // Left bump
        if (sensor->bumpLeft) {
            oi_setWheels(0, 0);
            reverse(sensor, 100);
            distance -= 100;

            turn_clockwise(sensor, 81);
            // Potentially keep traveling after avoiding
            move_forward(sensor, 128);
            turn_counterclockwise(sensor, 81);

            // We bumped, so set bumped=1 and leave the loop
            bumped = 1;
            break;
        }

        // Right bump
        if (sensor->bumpRight) {
            oi_setWheels(0, 0);
            reverse(sensor, 100);
            distance -= 100;

            turn_counterclockwise(sensor, 81);
            move_forward(sensor, 128);
            turn_clockwise(sensor, 81);

            // We bumped, so set bumped=1 and leave the loop
            bumped = 1;
            break;
        }

        distance += sensor->distance;
    }

    oi_setWheels(0, 0);
    return bumped;
}

void reverse(oi_t *sensor, float centimeters){
    double distance = 0;
    oi_setWheels(-200, -200);
    while(distance < centimeters){

        oi_update(sensor);
        distance -= sensor->distance;
    }
    oi_setWheels(0, 0);

}

//Turns the bot clockwise by the desired angle
void turn_clockwise(oi_t *sensor, double degrees){
    lcd_init();
    oi_setWheels(-50, 50);
    oi_update(sensor);
    double angle = 0;
    degrees *= -1;
    while(angle > degrees){

        oi_update(sensor);
        angle += sensor->angle;
        }
    oi_setWheels(0, 0);
}

void turn_counterclockwise(oi_t *sensor, double degrees){
    oi_setWheels(50, -50);
    oi_update(sensor);
    double angle = 0;
    while(angle < degrees){

        oi_update(sensor);
        angle += sensor->angle;
        }
    oi_setWheels(0, 0);
}
