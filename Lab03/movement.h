/*
 * movement.h
 *
 *  Created on: Feb 7, 2025
 *      Author: cjhoy
 */

#ifndef MOVEMENT_H_

double move_backward(oi_t*sensor_data, double distance_mm, int speed);
void turn_Clockwise(oi_t*sensor_data, double degrees);
void turn_CntrClockwise(oi_t*sensor_data, double degrees);
double move_forward(oi_t*sensor_data, double distance_mm, int speed);
void superman_Drive(oi_t*sensor_data, double distance_mm, int speed);


#define MOVEMENT_H_
#ifndef HEADER_FILE
#define HEADER_FILE




#endif /* MOVEMENT_H_ */
#endif
