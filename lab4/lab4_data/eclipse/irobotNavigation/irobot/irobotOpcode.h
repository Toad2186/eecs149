/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	OpCodes for the iRobot Create Open Interface

	Revised:	2011-01-18
*/

#ifndef _IROBOTOPCODE_H
#define _IROBOTOPCODE_H

/* OpCodes for iRobot open interface. */
typedef enum{
	OP_START				= 128,
	OP_BAUD					= 129,
	OP_CONTROL				= 130,
	OP_SAFE					= 131,
	OP_FULL					= 132,
	OP_DEMO					= 136,
	OP_DEMO_COVER			= 135,
	OP_DEMO_COVER_DOCK		= 143,
	OP_DEMO_SPOT			= 134,
	OP_DRIVE				= 137,
	OP_DRIVE_DIRECT			= 145,
	OP_LEDS					= 139,
	OP_DIGITAL_OUTPUTS		= 147,
	OP_PWM_LOW_SIDE_DRIVERS	= 144,
	OP_LOW_SIDE_DRIVERS		= 138,
	OP_SEND_IR				= 151,
	OP_SONG					= 140,
	OP_PLAY_SONG			= 141,
	OP_SENSORS				= 142,
	OP_QUERY_LIST			= 149,
	OP_STREAM				= 148,
	OP_PAUSE_RESUME_STREAM	= 150,
	OP_SCRIPT				= 152,
	OP_PLAY_SCRIPT			= 153,
	OP_SHOW_SCRIPT			= 154,
	OP_WAIT_TIME			= 155,
	OP_WAIT_DISTANCE		= 156,
	OP_WAIT_ANGLE			= 157,
	OP_WAIT_EVENT			= 158
} irobotOpcode_t;

#define OP_START_SIZE					1
#define OP_BAUD_SIZE					2
#define OP_CONTROL_SIZE					1
#define OP_SAFE_SIZE					1
#define OP_FULL_SIZE					1
#define OP_DEMO_SIZE					2
#define OP_DEMO_COVER_SIZE				1
#define OP_DEMO_COVER_DOCK_SIZE			1
#define OP_DEMO_SPOT_SIZE				1
#define OP_DRIVE_SIZE					5
#define OP_DRIVE_DIRECT_SIZE			5
#define OP_LEDS_SIZE					4
#define OP_DIGITAL_OUTPUTS_SIZE			2
#define OP_PWM_LOW_SIDE_DRIVERS_SIZE	4
#define OP_LOW_SIDE_DRIVERS_SIZE		2
#define OP_SEND_IR_SIZE					2
/* OP_SONG size is variable */
#define OP_PLAY_SONG_SIZE				2
#define OP_SENSORS_SIZE					2
/* OP_QUERY_LIST size is variable */
/* OP_STREAM size is variable */
#define OP_PAUSE_RESUME_STREAM_SIZE		2
/* OP_SCRIPT size is variable */
#define OP_PLAY_SCRIPT_SIZE				1	
#define OP_SHOW_SCRIPT_SIZE				1
#define OP_WAIT_TIME_SIZE				2
#define OP_WAIT_DISTANCE_SIZE			3
#define OP_WAIT_ANGLE_SIZE				3
#define OP_WAIT_EVENT_SIZE				2

#endif	/* _IROBOTOPCODE_H */
