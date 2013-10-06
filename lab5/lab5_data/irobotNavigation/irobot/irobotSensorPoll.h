/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Methods to poll iRobot sensors.
				NOTE: Polling requires both transmitting and receiving
				to the UART port, hence these functions are *not*
				thread safe with regard to other UART functions.

	Revised:	2011-01-18
*/

#ifndef _IROBOT_SENSORPOLL_H
#define _IROBOT_SENSORPOLL_H

#include "irobotUART.h"
#include "irobotSensorTypes.h"

/* Request sensor packet from iRobot and wait for response */
extern int32_t irobotSensorPollSensorGroup6(
	const irobotUARTPort_t			port,				/* (in)		iRobot UART pot */
	irobotSensorGroup6_t * const	sensorGroup6		/* (out)	Sensor group */
);


#endif /* _IROBOT_SENSORPOLL_H  */
