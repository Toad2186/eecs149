/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Functions for reading iRobot sensor streams.

	Revised:	2011-02-04
*/

#include "irobotSensor.h"
#include "irobotSensorStream.h"
#include "irobotOpcode.h"
#include "irobotError.h"
#include "irobotUART.h"
#include <math.h>

/* Including all sensor IDs in a sensor packet (bad idea) is the limit for this packet size */
#define OP_SENSOR_STREAM_MAX_CODES	43
#define OP_SENSOR_STREAM_MAX_SIZE	OP_SENSOR_STREAM_MAX_CODES + 2	/* maximum number of sensors, plus header and size bytes */

/* header of a sensor stream packet */
#define SENSOR_STREAM_HEADER		19

/* configure a sensors stream */
extern int32_t irobotSensorStreamConfigure(
	const irobotUARTPort_t			port,			/* (in)		irobot UART port */
	const irobotSensorCode * const	sensorCodes,	/* (in)		array of sensor codes (must be nSensorCodes in size) */
	const uint8_t					nSensorCodes	/* (in)		number of sensors in each stream packet */
){													/* (ret)	error / success code */
	uint8_t packet[OP_SENSOR_STREAM_MAX_SIZE];
	uint8_t packetIndex = 0;
	uint8_t sensorCodeIndex = 0;

	/* check for NULL pointers */
	if(nSensorCodes && !sensorCodes){
		return ERROR_INVALID_PARAMETER;
	}

	packet[packetIndex++] = OP_STREAM;
	packet[packetIndex++] =  fminl(nSensorCodes, OP_SENSOR_STREAM_MAX_CODES);
	for(sensorCodeIndex = 0; sensorCodeIndex < fminl(nSensorCodes, OP_SENSOR_STREAM_MAX_CODES); sensorCodeIndex++){
		packet[packetIndex++] = sensorCodes[sensorCodeIndex];
	}

	return irobotUARTWriteRaw(port, packet, packetIndex);
}

/* pause or resume a sensor stream */
extern int32_t irobotSensorStreamPause(
	const irobotUARTPort_t port,			/* (in)		irobot UART port */
	const bool pause						/* (in)		TRUE if set to pause */
){
	uint8_t packet[OP_PAUSE_RESUME_STREAM_SIZE];

	packet[0] = OP_PAUSE_RESUME_STREAM;
	packet[1] = !pause;

	return irobotUARTWriteRaw(port, packet, OP_PAUSE_RESUME_STREAM_SIZE);
}

/* begin a sensor stream containing all sensors (SensorGroup6)
	
	NOTE: Do not use this to measure distance and angle,
   as these measurements are subject to roundoff
   error in each packet; less frequent packets (polling)
   are needed.
*/
extern int32_t irobotSensorStreamStartAll(
	const irobotUARTPort_t			port			/* (in)		irobot UART port */
){
	int32_t status = ERROR_SUCCESS;
	const irobotSensorCode allSensors = SENSOR_GROUP6;

	irobot_IfIsNotError(status, irobotSensorStreamConfigure(port, &allSensors, 1));
	irobot_IfIsNotError(status, irobotSensorStreamPause(port, false));

	return status;
}

/* process a sensors stream that has been configured
   to transmit SensorGroup6 (all sensors).  */
extern int32_t irobotSensorStreamProcessAll(
	xqueue_t * const queue,							/* (in/out)	raw byte stream */
	irobotSensorGroup6_t * const sensors,			/* (out)	sensors			*/
	bool * const packetFound						/* (out)	packet found	*/
){
	int32_t status = ERROR_SUCCESS;

	/* check for NULL pointers */
	if(!queue || !sensors || !packetFound){
		return ERROR_INVALID_PARAMETER;
	}

	*packetFound = false;

	/*	Align buffer with iRobot sensor stream, according to format:
		[Header:19] [Len:27] [Packet ID:0] [SenGroup0 (26 bytes)] [CxSum] */
	while(!xqueue_empty(queue) && xqueue_front(queue) != SENSOR_STREAM_HEADER){
		xqueue_drop(queue);
	}

	/*	Check for properly formatted header;
		NOTE: iRobot OI spec incorrectly omits the header from the checksum */
	if( xqueue_count(queue) >= SENSOR_GROUP6_SIZE + 4	/* size of entire packet		*/
	 && xqueue_pop(queue) == SENSOR_STREAM_HEADER		/* sensor stream packet			*/
	 && xqueue_pop(queue) == SENSOR_GROUP6_SIZE + 1		/* size of payload + checksum	*/
	 && xqueue_pop(queue) == SENSOR_GROUP6){			/* payload is sensor group 6	*/
		 /* Checksum: cxsum = [Header:19] + [n-bytes:Sen6Size+1=53] + [packet ID:6] + [data (Sen6Size)] */
		 uint8_t cxsum = 0;
		 cxsum += SENSOR_STREAM_HEADER;
		 cxsum += SENSOR_GROUP6_SIZE + 1;
		 cxsum += SENSOR_GROUP6;
		 cxsum += xqueue_checksum(queue, SENSOR_GROUP6_SIZE + 1, 0);	/* payload and encoded checksum */

		 /* checksum passed */
		 if(cxsum == 0){
			 irobot_StatusMerge(&status, irobotReadSensorGroup6(queue, sensors));
			 xqueue_pop(queue);		/* clear checksum */
			 if(!irobot_IsError(status)){
				 *packetFound = true;
			 }
		 }
	}

	return status;
}
