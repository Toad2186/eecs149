/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	iRobot actuator type definitions.

	Revised:	2011-01-18
*/

#ifndef _IROBOTACTUATORTYPES_H
#define _IROBOTACTUATORTYPES_H

#include "irobotTypes.h"

typedef enum{
	DRIVE_STRAIGHT			= 0x8000,
	DRIVE_CLOCKWISE			= 0xFFFF,
	DRIVE_COUNTERCLOCKWISE	= 0x0001
} irobotDirection_t;

typedef enum{
	LED_NONE			= 0,
	LED_PLAY			= 2,
	LED_ADVANCE			= 8,
	LED_ADVANCE_PLAY	= 10
} irobotLED_t;

typedef struct{
	uint8_t midiNote;
	uint8_t duration;
} irobotSongNote_t;

/* max / min speeds */
#define ACTUATOR_WHEEL_SPEED_MAX			500
#define ACTUATOR_WHEEL_SPEED_MIN			-500

/* max / min drive radii */
#define ACTUATOR_DRIVE_RADIUS_MAX			2000
#define ACTUATOR_DRIVE_RADIUS_MIN			-2000

/* max / min pwm duty cycle (0, 100%) */
#define ACTUATOR_PWM_DUTY_MAX				128
#define ACTUATOR_PWM_DUTY_MIN				0

/* song definitions */
#define ACTUATOR_MAX_SONGS					16
#define ACTUATOR_MAX_NOTES_PER_SONG			16


#endif	/* _IROBOTTYPES_H */
