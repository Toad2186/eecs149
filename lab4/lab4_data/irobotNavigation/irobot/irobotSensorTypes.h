/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Sensor packet IDs and structures for the iRobot Create Open Interface

	Revised:	2011-01-18
*/

#ifndef _IROBOT_SENSORTYPES_H
#define _IROBOT_SENSORTYPES_H

#include "irobotTypes.h"

/* iRobot sensor packet IDs. */
typedef enum{
	SENSOR_GROUP0							= 0,
	SENSOR_GROUP1							= 1,
	SENSOR_GROUP2							= 2,
	SENSOR_GROUP3							= 3,
	SENSOR_GROUP4							= 4,
	SENSOR_GROUP5							= 5,
	SENSOR_GROUP6							= 6,
	SENSOR_BUMPS_WHEELDROPS					= 7,
	SENSOR_WALL								= 8,
	SENSOR_CLIFF_LEFT						= 9,
	SENSOR_CLIFF_FRONT_LEFT					= 10,
	SENSOR_CLIFF_FRONT_RIGHT				= 11,
	SENSOR_CLIFF_RIGHT						= 12,
	SENSOR_VIRTUAL_WALL						= 13,
	SENSOR_LOW_SIDE_DRIVER_WHEEL_OVERDRIVE	= 14,
	SENSOR_UNUSED0							= 15,
	SENSOR_UNUSED1							= 16,
	SENSOR_INFRARED							= 17,
	SENSOR_BUTTONS							= 18,
	SENSOR_DISTANCE							= 19,
	SENSOR_ANGLE							= 20,
	SENSOR_CHARGING_STATE					= 21,
	SENSOR_VOLTAGE							= 22,
	SENSOR_CURRENT							= 23,
	SENSOR_BATTERY_TEMPERATURE				= 24,
	SENSOR_BATTERY_CHARGE					= 25,
	SENSOR_BATTERY_CAPACITY					= 26,
	SENSOR_WALL_SIGNAL						= 27,
	SENSOR_CLIFF_LEFT_SIGNAL				= 28,
	SENSOR_CLIFF_FRONT_LEFT_SIGNAL			= 29,
	SENSOR_CLIFF_FRONT_RIGHT_SIGNAL			= 30,
	SENSOR_CLIFF_RIGHT_SIGNAL				= 31,
	SENSOR_CARGO_BAY_DIGITAL_INPUTS			= 32,
	SENSOR_CARGO_BAY_ANALOG_SIGNAL			= 33,
	SENSOR_CHARGING_SOURCES_AVAILABLE		= 34,
	SENSOR_OI_MODE							= 35,
	SENSOR_SONG_NUMBER						= 36,
	SENSOR_SONG_PLAYING						= 37,
	SENSOR_NUMBER_OF_STREAM_PACKETS			= 38,
	SENSOR_REQUESTED_VELOCITY				= 39,
	SENSOR_REQUESTED_RADIUS					= 40,
	SENSOR_REQUESTED_RIGHT_VELOCITY			= 41,
	SENSOR_REQUESTED_LEFT_VELOCITY			= 42
} irobotSensorCode;

/* iRobot sensor packet sizes */
#define SENSOR_GROUP0_SIZE							26
#define SENSOR_GROUP1_SIZE							10
#define SENSOR_GROUP2_SIZE							6
#define SENSOR_GROUP3_SIZE							10
#define SENSOR_GROUP4_SIZE							14
#define SENSOR_GROUP5_SIZE							12
#define SENSOR_GROUP6_SIZE							52
#define SENSOR_BUMPS_WHEELDROPS_SIZE				1
#define SENSOR_WALL_SIZE							1
#define SENSOR_CLIFF_LEFT_SIZE						1
#define SENSOR_CLIFF_FRONT_LEFT_SIZE				1
#define SENSOR_CLIFF_FRONT_RIGHT_SIZE				1 
#define SENSOR_CLIFF_RIGHT_SIZE						1 
#define SENSOR_VIRTUAL_WALL_SIZE					1 
#define SENSOR_LOW_SIDE_DRIVER_WHEEL_OVERDRIVE_SIZE	1 
#define SENSOR_UNUSED0_SIZE							1 
#define SENSOR_UNUSED1_SIZE							1 
#define SENSOR_INFRARED_SIZE						1 
#define SENSOR_BUTTONS_SIZE							1 
#define SENSOR_DISTANCE_SIZE						2 
#define SENSOR_ANGLE_SIZE							2 
#define SENSOR_CHARGING_STATE_SIZE					1 
#define SENSOR_VOLTAGE_SIZE							2 
#define SENSOR_CURRENT_SIZE							2 
#define SENSOR_BATTERY_TEMPERATURE_SIZE				1 
#define SENSOR_BATTERY_CHARGE_SIZE					2 
#define SENSOR_BATTERY_CAPACITY_SIZE				2 
#define SENSOR_WALL_SIGNAL_SIZE						2 
#define SENSOR_CLIFF_LEFT_SIGNAL_SIZE				2 
#define SENSOR_CLIFF_FRONT_LEFT_SIGNAL_SIZE			2 
#define SENSOR_CLIFF_FRONT_RIGHT_SIGNAL_SIZE		2 
#define SENSOR_CLIFF_RIGHT_SIGNAL_SIZE				2 
#define SENSOR_CARGO_BAY_DIGITAL_INPUTS_SIZE		1 
#define SENSOR_CARGO_BAY_ANALOG_SIGNAL_SIZE			2 
#define SENSOR_CHARGING_SOURCES_AVAILABLE_SIZE		1 
#define SENSOR_OI_MODE_SIZE							1 
#define SENSOR_SONG_NUMBER_SIZE						1 
#define SENSOR_SONG_PLAYING_SIZE					1 
#define SENSOR_NUMBER_OF_STREAM_PACKETS_SIZE		1 
#define SENSOR_REQUESTED_VELOCITY_SIZE				2 
#define SENSOR_REQUESTED_RADIUS_SIZE				2 
#define SENSOR_REQUESTED_RIGHT_VELOCITY_SIZE		2 
#define SENSOR_REQUESTED_LEFT_VELOCITY_SIZE			2 

/* Minimum sensor update period */
#define SENSOR_MIN_UPDATE_PERIOD	15	/* in ms */

/* next highest power of 2 that is greater than any iRobot packet size */
#define SENSOR_SIZE_UPPER_BOUND		64

/* iRobot bump and wheel-drop sensors. */
typedef struct{
	bool	wheeldropCaster;	/* State of the caster wheeldrop sensor; when true, indicates the wheel is not in contact with the ground. */
	bool	wheeldropLeft;		/* State of the left wheeldrop sensor; when true, indicates the wheel is not in contact with the ground. */
	bool	wheeldropRight;		/* State of the right wheeldrop sensor; when true, indicates the wheel is not in contact with the ground. */
	bool	bumpLeft;			/* State of the left bump sensor; if true, the left side of the robot is in contact with an object. */
	bool	bumpRight;			/* State of the right bump sensor; if true, the right side of the robot is in contact with an object. */
} irobotBumps_WheelDrops_t;

/* iRobot button sensors. */
typedef struct{
	bool	advance;			/* advance button */
	bool	play;				/* play button */
} irobotButtons_t;

/* iRobot cargo bay digital inputs. */
typedef struct{
	bool	digitalInput0;		/* digital input pin 0 */
	bool	digitalInput1;		/* digital input pin 1 */
	bool	digitalInput2;		/* digital input pin 2 */
	bool	digitalInput3;		/* digital input pin 3 */
	bool	deviceDetect;		/* device detect pin */
} irobotCargoBayDigitalInputs_t;

/* iRobot charging source sensors. */
typedef struct{
	bool	internalCharger;	/* internal charger */
	bool	homeBase;			/* home docking station */
} irobotChargingSourcesAvailable_t;

/* iRobot charging state sensor. */
typedef enum{
	CHARGING_STATE_NOT_CHARGING				= 0,
	CHARGING_STATE_RECONDITION_CHARGING		= 1,
	CHARGING_STATE_FULL_CHARGING			= 2,
	CHARGING_STATE_TRICKLE_CHARGING			= 3,
	CHARGING_STATE_WAITING					= 4,
	CHARGING_STATE_CHARGING_FAULT_CONDITION	= 5
} irobotChargingState_t;

/* iRobot low-side driver and wheel overcurrent sensors. */
typedef struct{
	bool	lowSideDriver0;		/* Overcurrent sensor for low-side driver 0; if true, the device has drawn too much current and has been shut down. */
	bool	lowSideDriver1;		/* Overcurrent sensor for low-side driver 1; if true, the device has drawn too much current and has been shut down. */
	bool	lowSideDriver2;		/* Overcurrent sensor for low-side driver 2; if true, the device has drawn too much current and has been shut down. */
	bool	leftWheel;			/* Overcurrent sensor for the left wheel; if true, the device has drawn too much current and has been shut down. */
	bool	rightWheel;			/* Overcurrent sensor for the right wheel; if true, the device has drawn too much current and has been shut down. */
} irobotLowSideDriver_WheelOvercurrent_t;

/* Mode (full, safe, passive) of the iRobot. */
typedef enum{
	OISTATE_OFF		= 0,
	OISTATE_PASSIVE	= 1,
	OISTATE_SAFE	= 2,
	OISTATE_FULL	= 3
} irobotOIState_t;

/* Sensor Group 0 */
typedef struct{
	/* iRobot bump and wheel-drop sensors. */
	irobotBumps_WheelDrops_t bumps_wheelDrops;

	/* Binary interpretation of the infrared wall sensor; if true, the sensor has read above a predefined threshold and indicates a wall (or object) is in	front of the robot. */
	bool wall;

	/* Binary interpretation of the cliff sensors; if true, the sensor has read below a predefined threshold and indicates the sensor is not immediately above ground. */
	bool cliffLeft;
	bool cliffFrontLeft;
	bool cliffFrontRight;
	bool cliffRight;

	/* Virtual Wall sensor is a particular infrared packet omitted by a virtual wall device, and received by the IR on top of the robot. If the signal is received, the value is true. */
	bool virtualWall;

	/* iRobot low-side driver and wheel overcurrent sensors. */
	irobotLowSideDriver_WheelOvercurrent_t lowSideDriver_WheelOvercurrent;

	/* Most recently received byte from the IR receiver. A value of 0xFF (255) indicates no byte is being received. */
	uint8_t infrared;

	/* iRobot button sensors. */
	irobotButtons_t buttons;

	/* Distance (in mm) the robot has traveled since the last sensor packet. */
	int16_t distance;

	/* Angle (in degrees) through which the robot has rotated since the last sensor packet. */
	int16_t angle;

	/* iRobot charging state sensor. */
	irobotChargingState_t chargingState;
	
	/* Voltage of the iRobot battery, in mV. */
	uint16_t voltage;

	/* Current (mA) flowing into or out of the battery. Negative currents indicate current is leaving the battery; positive currents (present in charging) indicate current is entering the battery. */
	int16_t current;
	
	/* Temperature of the battery, in degrees Celcius. */
	int8_t batteryTemperature;

	/* Current charge of the create battery, in mAh. */
	uint16_t batteryCharge;
	
	/* Estimated charging capacity of the battery, in mAh. */
	uint16_t batteryCapacity;
} irobotSensorGroup0_t;

/* Sensor Group 1 */
typedef struct{
	/* iRobot bump and wheel-drop sensors. */
	irobotBumps_WheelDrops_t bumps_wheelDrops;

	/* Binary interpretation of the infrared wall sensor; if true, the sensor has read above a predefined threshold and indicates a wall (or object) is in	front of the robot. */
	bool wall;

	/* Binary interpretation of the cliff sensors; if true, the sensor has read below a predefined threshold and indicates the sensor is not immediately above ground. */
	bool cliffLeft;
	bool cliffFrontLeft;
	bool cliffFrontRight;
	bool cliffRight;

	/* Virtual Wall sensor is a particular infrared packet omitted by a virtual wall device, and received by the IR on top of the robot. If the signal is received, the value is true. */
	bool virtualWall;

	/* iRobot low-side driver and wheel overcurrent sensors. */
	irobotLowSideDriver_WheelOvercurrent_t lowSideDriver_wheelovercurrent;
} irobotSensorGroup1_t;

/* Sensor Group 2 */
typedef struct{
	/* Most recently received byte from the IR receiver. A value of 0xFF (255) indicates no byte is being received. */
	uint8_t infrared;

	/* iRobot button sensors. */
	irobotButtons_t buttons;

	/* Distance (in mm) the robot has traveled since the last sensor packet. */
	int16_t distance;

	/* Angle (in degrees) through which the robot has rotated since the last sensor packet. */
	int16_t angle;
} irobotSensorGroup2_t;

/* Sensor Group 3 */
typedef struct{
	/* iRobot charging state sensor. */
	irobotChargingState_t chargingState;
	
	/* Voltage of the iRobot battery, in mV. */
	uint16_t voltage;

	/* Current (mA) flowing into or out of the battery. Negative currents indicate current is leaving the battery; positive currents (present in charging) indicate current is entering the battery. */
	int16_t current;
	
	/* Temperature of the battery, in degrees Celcius. */
	int8_t batteryTemperature;

	/* Current charge of the create battery, in mAh. */
	uint16_t batteryCharge;
	
	/* Estimated charging capacity of the battery, in mAh. */
	uint16_t batteryCapacity;
} irobotSensorGroup3_t;

/* Sensor Group 4 */
typedef struct{
	/* Sampled value of an analog sensor, range 0-4095. */
	uint16_t	wallSignal;
	uint16_t	cliffLeftSignal;
	uint16_t	cliffFrontLeftSignal;
	uint16_t	cliffFrontRightSignal;
	uint16_t	cliffRightSignal;

	/* digital inputs */
	irobotCargoBayDigitalInputs_t	cargoBayDigitalInputs;

	/* sampled cargo bay analog line; range 0-1023 */
	uint16_t	cargoBayAnalogSignal;

	/* charging sources available */
	irobotChargingSourcesAvailable_t	chargingSourcesAvailable;
} irobotSensorGroup4_t;

/* Sensor Group 5 */
typedef struct{
	/* irobot OI mode */
	irobotOIState_t	oiState;

	/* index of the song that is loaded or is playing */
	uint8_t			songNumber;
	bool			songPlaying;

	/* number of packets in each stream broadcast */
	uint8_t			nStreamPackets;

	/* requested velocity, in mm/s for DRIVE mode */
	int16_t			requestedVelocity;
	int16_t			requestedRadius;

	/* requested velocity in mm/s for DRIVE_DIRECT mode */
	int16_t			requestedRightWheelVelocity;
	int16_t			requestedLeftWheelVelocity;
} irobotSensorGroup5_t;

/* Sensor Group 6 */
typedef struct{
	/* iRobot bump and wheel-drop sensors. */
	irobotBumps_WheelDrops_t bumps_wheelDrops;

	/* Binary interpretation of the infrared wall sensor; if true, the sensor has read above a predefined threshold and indicates a wall (or object) is in	front of the robot. */
	bool wall;

	/* Binary interpretation of the cliff sensors; if true, the sensor has read below a predefined threshold and indicates the sensor is not immediately above ground. */
	bool cliffLeft;
	bool cliffFrontLeft;
	bool cliffFrontRight;
	bool cliffRight;

	/* Virtual Wall sensor is a particular infrared packet omitted by a virtual wall device, and received by the IR on top of the robot. If the signal is received, the value is true. */
	bool virtualWall;

	/* iRobot low-side driver and wheel overcurrent sensors. */
	irobotLowSideDriver_WheelOvercurrent_t lowSideDriver_WheelOvercurrent;

	/* Most recently received byte from the IR receiver. A value of 0xFF (255) indicates no byte is being received. */
	uint8_t infrared;

	/* iRobot button sensors. */
	irobotButtons_t buttons;

	/* Distance (in mm) the robot has traveled since the last sensor packet. */
	int16_t distance;

	/* Angle (in degrees) through which the robot has rotated since the last sensor packet. */
	int16_t angle;

	/* iRobot charging state sensor. */
	irobotChargingState_t chargingState;
	
	/* Voltage of the iRobot battery, in mV. */
	uint16_t voltage;

	/* Current (mA) flowing into or out of the battery. Negative currents indicate current is leaving the battery; positive currents (present in charging) indicate current is entering the battery. */
	int16_t current;
	
	/* Temperature of the battery, in degrees Celcius. */
	int8_t batteryTemperature;

	/* Current charge of the create battery, in mAh. */
	uint16_t batteryCharge;
	
	/* Estimated charging capacity of the battery, in mAh. */
	uint16_t batteryCapacity;

	/* Sampled value of an analog sensor, range 0-4095. */
	uint16_t	wallSignal;
	uint16_t	cliffLeftSignal;
	uint16_t	cliffFrontLeftSignal;
	uint16_t	cliffFrontRightSignal;
	uint16_t	cliffRightSignal;

	/* digital inputs */
	irobotCargoBayDigitalInputs_t	cargoBayDigitalInputs;

	/* sampled cargo bay analog line; range 0-1023 */
	uint16_t	cargoBayAnalogSignal;

	/* charging sources available */
	irobotChargingSourcesAvailable_t	chargingSourcesAvailable;

	/* irobot OI mode */
	irobotOIState_t	oiState;

	/* index of the song that is loaded or is playing */
	uint8_t			songNumber;
	bool			songPlaying;

	/* number of packets in each stream broadcast */
	uint8_t			nStreamPackets;

	/* requested velocity, in mm/s for DRIVE mode */
	int16_t			requestedVelocity;
	int16_t			requestedRadius;

	/* requested velocity in mm/s for DRIVE_DIRECT mode */
	int16_t			requestedRightWheelVelocity;
	int16_t			requestedLeftWheelVelocity;
} irobotSensorGroup6_t;


#endif /* _IROBOT_SENSORTYPES_H */
