/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Methods to poll iRobot sensors.
				NOTE: Polling requires both transmitting and receiving
				to the UART port, hence these functions are *not*
				thread safe with regard to other UART functions.

	Revised:	2011-01-18
*/

#include "irobotOpcode.h"
#include "irobotSensor.h"
#include "irobotSensorPoll.h"
#include "xqueue.h"

/* Request sensor packet from iRobot and wait for response */
extern int32_t irobotSensorPollSensorGroup6(
	const irobotUARTPort_t	port,				/* (in)		iRobot UART pot */
	irobotSensorGroup6_t *	const sensorGroup6	/* (out)	Sensor group */
){
	int32_t status = ERROR_SUCCESS;

	/* initialize communications buffer */
	uint8_t txBuffer[OP_SENSORS_SIZE];
	uint8_t rxQueueBuffer[SENSOR_SIZE_UPPER_BOUND] = {0x00};
	xqueue_t rxQueue;
	xqueue_init(&rxQueue, rxQueueBuffer, SENSOR_SIZE_UPPER_BOUND);

	/* check for NULL pointer */
	if(!sensorGroup6){
		return ERROR_INVALID_PARAMETER;
	}

	/* request packet */
	txBuffer[0] = OP_SENSORS;
	txBuffer[1] = SENSOR_GROUP6;
	irobot_StatusMerge(&status, irobotUARTWriteRaw(port, txBuffer, OP_SENSORS_SIZE));
	
	/* receive response */
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTRead(port, &rxQueue, SENSOR_GROUP6_SIZE));
	}

	/* read response */
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotReadSensorGroup6(&rxQueue, sensorGroup6));
	}

	return status;
}
