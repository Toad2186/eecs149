/*
 * irobotNavigationStatechart.h
 *
 *  Created on: Mar 7, 2013
 *      Author: jjensen
 */

#ifndef IROBOTNAVIGATIONSTATECHART_H_
#define IROBOTNAVIGATIONSTATECHART_H_

#include "irobot/irobotSensorTypes.h"

/* accelerometer */
typedef struct{
	double	x;							/* x axis, in g */
	double	y;							/* y axis, in g */
	double	z;							/* z axis, in g */
} accelerometer_t;

void irobotNavigationStatechart(
	const int16_t 				maxWheelSpeed,						/* (in) maximum wheel speed, in mm/s */
	const int32_t 				netDistance,						/* (in) net distance, in mm */
	const int32_t 				netAngle,							/* (in) net angle, in deg */
	const irobotSensorGroup6_t 	sensors,							/* (in) irobot sensors */
	const accelerometer_t 		accel,								/* (in) filtered accelerometer, in g */
	const bool					isSimulator,						/* (in) statechart is executing within a simulator */
	int16_t * const 			pRightWheelSpeed,					/*(out) right wheel speed */
	int16_t * const 			pLeftWheelSpeed,					/*(out) left wheel speed */
	int32_t * const				pState								/*(out) current state */
);

#endif /* IROBOTNAVIGATIONSTATECHART_H_ */
