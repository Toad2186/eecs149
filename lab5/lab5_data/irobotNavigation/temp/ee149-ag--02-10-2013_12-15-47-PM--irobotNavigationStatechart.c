/*
 * irobotNavigationStatechart.c
 *
 *  Created on: Mar 7, 2013
 *      Author:
 */

#include "irobotNavigationStatechart.h"
#include <math.h>
#include <stdlib.h>

/* Program States */
typedef enum{
	INITIAL = 0,						/* Initial state */
	PAUSE_WAIT_BUTTON_RELEASE,			/* Paused; pause button pressed down, wait until released before detecting next press */
	UNPAUSE_WAIT_BUTTON_PRESS,			/* Paused; wait for pause button to be pressed */
	UNPAUSE_WAIT_BUTTON_RELEASE,		/* Paused; pause button pressed down, wait until released before returning to previous state */
	DRIVE,								/* Drive straight */
	TURN,								/* Turn Left*/
	TURNRIGHT,							/* Turn Right*/
	BACK,
	CORRECT								/* Correct for obstacles */
} robotState_t;

#define DEG_PER_RAD			(180.0 / M_PI)		/* degrees per radian */
#define RAD_PER_DEG			(M_PI / 180.0)		/* radians per degree */

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
){
	/* local state */
	static robotState_t 		state = INITIAL;				/* current program state */
	static robotState_t			unpausedState = DRIVE;			/* state history for pause region */
	static uint32_t				obstacles = 0;					/* how many times we turned to avoid obstacles */
	static int32_t 				avoid = 0;						/* If we are in avoid mode, this prevents overflow */
	static int32_t				turnAngle = 73;					/* Angle to turn (73 appears to be much closer to 90 than 90 */
	static int32_t				orient = 0;						/* if robot is trying to orient itself */
	static int32_t				distanceAtManeuverStart = 0;	/* distance robot had travelled when a maneuver begins, in mm */
	static int32_t				angleAtManeuverStart = 0;		/* angle through which the robot had turned when a maneuver begins, in deg */
	static double				prev_z = 1, prev_x = 0, prev_y = 0;	/* Previous z reading */
	static double				filtered_z = 1, filtered_x = 0, filtered_y = 0; /* Filtered accelerometer reading */
	static const double			a = 0.9;						/* Filter constant */

	/* outputs */
	int16_t						leftWheelSpeed = 0;				/* speed of the left wheel, in mm/s */
	int16_t						rightWheelSpeed = 0;			/* speed of the right wheel, in mm/s */

	/******************************************************/
	/* state data - process inputs                        */
	/******************************************************/

	filtered_z = (1 - a) * accel.z + a * prev_z;
	prev_z = filtered_z;
	filtered_x = (1 - a) * accel.x + a * prev_x;
	prev_x = filtered_x;
	filtered_y = (1 - a) * accel.y + a * prev_y;
	prev_y = filtered_y;
	printf("\nInside StateChart: \nx=%+.2f y=%+.2f z=%+.2f\n",
		   filtered_x,
		   filtered_y,
		   filtered_z);

	/******************************************************/
	/* state transition - pause region (highest priority) */
	/******************************************************/
	if(   state == INITIAL
	   || state == PAUSE_WAIT_BUTTON_RELEASE
	   || state == UNPAUSE_WAIT_BUTTON_PRESS
	   || state == UNPAUSE_WAIT_BUTTON_RELEASE
	   || sensors.buttons.play				/* pause button */
	){
		switch(state){
		case INITIAL:
			/* set state data that may change between simulation and real-world */
			if(isSimulator){
			}
			else{
			}
			state = UNPAUSE_WAIT_BUTTON_PRESS; /* place into pause state */
			break;
		case PAUSE_WAIT_BUTTON_RELEASE:
			/* remain in this state until released before detecting next press */
			if(!sensors.buttons.play){
				state = UNPAUSE_WAIT_BUTTON_PRESS;
			}
			break;
		case UNPAUSE_WAIT_BUTTON_RELEASE:
			/* user pressed 'pause' button to return to previous state */
			if(!sensors.buttons.play){
				state = unpausedState;
			}
			break;
		case UNPAUSE_WAIT_BUTTON_PRESS:
			/* remain in this state until user presses 'pause' button */
			if(sensors.buttons.play){
				state = UNPAUSE_WAIT_BUTTON_RELEASE;
			}
			break;
		default:
			/* must be in run region, and pause button has been pressed */
			unpausedState = state;
			state = PAUSE_WAIT_BUTTON_RELEASE;
			break;
		}
	}
	/**************************************/
	/* state transition - run region      */
	/**************************************/
	else if(state == DRIVE){
		if (sensors.bumps_wheelDrops.bumpLeft
							   || sensors.bumps_wheelDrops.bumpRight
							   || sensors.cliffFrontLeft
							   || sensors.cliffFrontRight
							   || sensors.cliffLeft
							   || sensors.cliffRight) {
			avoid = 1;
			obstacles++;
			state = BACK;
		} else if (!avoid && (abs(netDistance - distanceAtManeuverStart) >= 50)) {
			if (filtered_z < 0.83) {
				orient = 1;
				state = TURN;
			}
			angleAtManeuverStart = netAngle;
			distanceAtManeuverStart = netDistance;
		}  else if (avoid && (abs(netDistance - distanceAtManeuverStart) >= 250)) {
			state = TURNRIGHT;
			angleAtManeuverStart = netAngle;
			distanceAtManeuverStart = netDistance;
		}
	}

	else if (state == BACK && abs(distanceAtManeuverStart - netDistance) >= 50) {
		angleAtManeuverStart = netAngle;
		distanceAtManeuverStart = netDistance;
		state = TURN;
	}

	else if (state == TURN) {
		if (abs(netAngle - angleAtManeuverStart) >= turnAngle) {
			if (orient) {
				if (abs(filtered_y) < 0.08 && filtered_x > -0.05) {
					orient = 0;
					angleAtManeuverStart = netAngle;
					distanceAtManeuverStart = netDistance;
					state = DRIVE;
				}
			} else {
					angleAtManeuverStart = netAngle;
					distanceAtManeuverStart = netDistance;
					state = DRIVE;
			}
		}
	}

	else if((state == TURNRIGHT) && abs(netAngle - angleAtManeuverStart) >= turnAngle){
		angleAtManeuverStart = netAngle;
		distanceAtManeuverStart = netDistance;
		obstacles--;
		if (obstacles == 0) {
			avoid = 0;
		}
		state = DRIVE;
	}

	/* else, no transitions are taken */

	/*****************/
	/* state actions */

	/*****************/
	switch(state){
	case INITIAL:
	case PAUSE_WAIT_BUTTON_RELEASE:
	case UNPAUSE_WAIT_BUTTON_PRESS:
	case UNPAUSE_WAIT_BUTTON_RELEASE:
		/* in pause mode, robot should be stopped */
		leftWheelSpeed = rightWheelSpeed = 0;
		break;

	case DRIVE:
		/* full speed ahead! */
		leftWheelSpeed = rightWheelSpeed = maxWheelSpeed;
		break;

	case BACK:
		leftWheelSpeed = -maxWheelSpeed;
		rightWheelSpeed = -maxWheelSpeed;
		break;

	case TURN:
		leftWheelSpeed = maxWheelSpeed;
		rightWheelSpeed = -leftWheelSpeed;
		break;

	case TURNRIGHT:
		leftWheelSpeed = -maxWheelSpeed;
		rightWheelSpeed = -leftWheelSpeed;
		break;

	default:
		/* Unknown state */
		leftWheelSpeed = rightWheelSpeed = 0;
		break;
	}

	/* write outputs */
	*pLeftWheelSpeed = leftWheelSpeed;
	*pRightWheelSpeed = rightWheelSpeed;
	*pState = state;
}
