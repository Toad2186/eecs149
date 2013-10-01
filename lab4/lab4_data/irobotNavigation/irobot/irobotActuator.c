/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	iRobot actuator commands.

	Revised:	2011-01-18
*/

#include "irobotActuator.h"
#include <stdlib.h>
#include <math.h>

#ifndef coerce
	#define coerce(xMin, x, xMax)	(fmin(fmax(xMin, x), xMax))
#endif

/* Write to the digital output bank of the cargo bay on iRobot. */
extern int32_t irobotDigitalOutputs(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const uint8_t			output		/* (in)		Pins  0-7 */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_DIGITAL_OUTPUTS_SIZE];
	
	packet[0] = OP_DIGITAL_OUTPUTS;
	packet[1] = output;

	return irobotUARTWriteRaw(port, packet, OP_DIGITAL_OUTPUTS_SIZE);
}

/* Directly actuate left and right wheels. */
extern int32_t irobotDriveDirect(
	const irobotUARTPort_t	port,			/* (in)		UART port */
	int16_t					leftWheelSpeed,	/* (in)		Left wheels speed, in mm/s */
	int16_t					rightWheelSpeed /* (in)		Right wheel speed, in mm/s */
){											/* (ret)	Error / success code */
	uint8_t packet[OP_DRIVE_DIRECT_SIZE];
	
	leftWheelSpeed = coerce(ACTUATOR_WHEEL_SPEED_MIN, leftWheelSpeed, ACTUATOR_WHEEL_SPEED_MAX);
	rightWheelSpeed = coerce(ACTUATOR_WHEEL_SPEED_MIN, rightWheelSpeed, ACTUATOR_WHEEL_SPEED_MAX);

	packet[0] = OP_DRIVE_DIRECT;
	packet[1] = HO(rightWheelSpeed);
	packet[2] = LO(rightWheelSpeed);
	packet[3] = HO(leftWheelSpeed);
	packet[4] = LO(leftWheelSpeed);

	return irobotUARTWriteRaw(port, packet, OP_DRIVE_DIRECT_SIZE);
}

/* Drives in a fixed direction  */
extern int32_t irobotDriveDirection(
	const irobotUARTPort_t		port,		/* (in)		UART port */
	int16_t						velocity,	/* (in)		Velocity, in mm/s */
	const irobotDirection_t		direction	/* (in)		direction */
){											/* (ret)	Error / success code */
	uint8_t packet[OP_DRIVE_SIZE];
	
	velocity = coerce(ACTUATOR_WHEEL_SPEED_MIN, velocity, ACTUATOR_WHEEL_SPEED_MAX);

	packet[0] = OP_DRIVE;
	packet[1] = HO(velocity);
	packet[2] = LO(velocity);
	packet[3] = HO((uint16_t)direction);
	packet[4] = LO((uint16_t)direction);

	return irobotUARTWriteRaw(port, packet, OP_DRIVE_SIZE);
}

/* Drive the robot with a fixed linear speed, and turning through a fixed radius.
  Do not call this function for the special cases of driving straight, or clockwise
  and counter-clockwise turning; this function instructs the robot to drive only nonzero radii.  */
extern int32_t irobotDriveRadius(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	int16_t					velocity,	/* (in)		Velocity, in mm/s */
	int16_t					radius		/* (in)		Radius, in mm */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_DRIVE_SIZE];

	velocity = coerce(ACTUATOR_WHEEL_SPEED_MIN, velocity, ACTUATOR_WHEEL_SPEED_MAX);
	radius = coerce(ACTUATOR_DRIVE_RADIUS_MIN, radius, ACTUATOR_DRIVE_RADIUS_MAX);

	/* Special case: radius = 1mm is interpreted as CCW rotation;
		iRobot Drive CCW covers this case, so a drive radius of 1mm is
		interpreted as the next smallest radius, 2mm */
	if(radius == 1){
		radius = 2;
	}

	packet[0] = OP_DRIVE;
	packet[1] = HO(velocity);
	packet[2] = LO(velocity);
	packet[3] = HO(radius);
	packet[4] = LO(radius);
	
	return irobotUARTWriteRaw(port, packet, OP_DRIVE_SIZE);
}

/* Change the state of the iRobot power, play, and advance LEDs. */
extern int32_t irobotLEDs(
	const irobotUARTPort_t	port,			/* (in)		UART port */
	const irobotLED_t		leds,			/* (in)		LEDs to turn on */
	const uint8_t			powerColor,		/* (in)		Power LED color (G[0] - R[255]) */
	const uint8_t			powerIntensity	/* (in)		Power LED intensiy (0-255) */
){											/* (ret)	Error / success code */
	uint8_t packet[OP_LEDS_SIZE];

	packet[0] = OP_LEDS;
	packet[1] = (uint8_t)leds;
	packet[2] = powerColor;
	packet[3] = powerIntensity;
	
	return irobotUARTWriteRaw(port, packet, OP_LEDS_SIZE);
}

/* Set the PWM duty cycle of the low-side drivers. */
extern int32_t irobotPWMLowSideDrivers(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	uint8_t					pwm0,		/* (in)		PWM for low-side driver 0 (0-128 duty cycle) */
	uint8_t					pwm1,		/* (in)		PWM for low-side driver 1 (0-128 duty cycle) */
	uint8_t					pwm2		/* (in)		PWM for low-side driver 2 (0-128 duty cycle) */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_PWM_LOW_SIDE_DRIVERS_SIZE];

	pwm0 = coerce(ACTUATOR_PWM_DUTY_MIN, pwm0, ACTUATOR_PWM_DUTY_MAX);
	pwm1 = coerce(ACTUATOR_PWM_DUTY_MIN, pwm1, ACTUATOR_PWM_DUTY_MAX);
	pwm2 = coerce(ACTUATOR_PWM_DUTY_MIN, pwm2, ACTUATOR_PWM_DUTY_MAX);

	packet[0] = OP_PWM_LOW_SIDE_DRIVERS;
	packet[1] = pwm0;
	packet[2] = pwm1;
	packet[3] = pwm2;
	
	return irobotUARTWriteRaw(port, packet, OP_PWM_LOW_SIDE_DRIVERS_SIZE);
}

/* opcode + song number + song length + n notes */
#define OP_SONG_MAX_LENGTH	(ACTUATOR_MAX_SONGS * ACTUATOR_MAX_NOTES_PER_SONG + 3)

/*	Define a song. Each song is alloted 16 notes, but a song can "spill over" into
	the next if so desired. The maximum number of notes that may be defined is
	(16 - SongNumber) * 16. */
extern int32_t irobotSong(
	const irobotUARTPort_t			port,		/* (in)		UART port */
	uint8_t							songNumber,	/* (in)		Song number */
	const irobotSongNote_t * const	songNotes,	/* (in)		Song notes */
	uint8_t							nNotes		/* (in)		Number of song notes */
){												/* (ret)	Error / success code */
	uint8_t packet[OP_SONG_MAX_LENGTH];
	uint8_t packetIndex = 0;
	uint8_t noteIndex = 0;

	if(!songNotes){
		return ERROR_INVALID_PARAMETER;
	}

	songNumber = fmin(songNumber, ACTUATOR_MAX_SONGS - 1);
	nNotes = fmin(nNotes, (ACTUATOR_MAX_SONGS - songNumber) * ACTUATOR_MAX_NOTES_PER_SONG);

	packet[packetIndex++] = OP_SONG;
	packet[packetIndex++] = songNumber;
	packet[packetIndex++] = nNotes;
	for(noteIndex = 0; noteIndex < nNotes; noteIndex++){
		packet[packetIndex++] = songNotes[noteIndex].midiNote;
		packet[packetIndex++] = songNotes[noteIndex].duration;
	}
	
	return irobotUARTWriteRaw(port, packet, packetIndex);
}

/* Play a song */
extern int32_t irobotPlaySong(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const uint8_t			songNumber	/* (in)		Song number */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_PLAY_SONG_SIZE];

	packet[0] = OP_PLAY_SONG;
	packet[1] = songNumber;
	
	return irobotUARTWriteRaw(port, packet, OP_PLAY_SONG_SIZE);
}

/* Stops the wheels. */
extern int32_t irobotStop(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	return irobotDriveDirect(port, 0, 0);
}
