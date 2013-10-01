/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Functions for reading iRobot sensor streams.

	Revised:	2011-02-04
*/

#ifndef _IROBOTSTREAM_H
#define _IROBOTSTREAM_H

#include "irobotUART.h"
#include "irobotSensorTypes.h"

/* configure a sensors stream */
extern int32_t irobotSensorStreamConfigure(
	const irobotUARTPort_t			port,			/* (in)		irobot UART port */
	const irobotSensorCode * const	sensorCodes,	/* (in)		array of sensor codes (must be nSensorCodes in size) */
	const uint8_t					nSensorCodes	/* (in)		number of sensors in each stream packet */
);													/* (ret)	error / success code */

/* pause or resume a sensor stream */
extern int32_t irobotSensorStreamPause(
	const irobotUARTPort_t port,					/* (in)		irobot UART port */
	const bool pause								/* (in)		TRUE if set to pause */
);

/* begin a sensor stream containing all sensors (SensorGroup6)
	
	NOTE: Do not use this to measure distance and angle,
	as these measurements are subject to roundoff
	error in each packet; less frequent packets (polling)
	are needed.
*/
extern int32_t irobotSensorStreamStartAll(
	const irobotUARTPort_t			port			/* (in)		irobot UART port */
);

/* process a sensors stream that has been configured
   to transmit SensorGroup6 (all sensors) */
extern int32_t irobotSensorStreamProcessAll(
	xqueue_t * const queue,							/* (in/out)	raw byte stream */
	irobotSensorGroup6_t * const sensors,			/* (out)	sensors			*/
	bool * const packetFound						/* (out)	packet found	*/
);


#endif /* _IROBOTSTREAM_H */
