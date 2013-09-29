/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Initialization and deinitialization procedures for the iRobot Create.

	Revised:	2011-12-20
*/

#ifndef _IROBOT_H
#define _IROBOT_H

#include "irobotUART.h"
#include "irobotSensor.h"
#include "irobotSensorPoll.h"
#include "irobotSensorStream.h"
#include "irobotActuator.h"
#include "irobotCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Open UART serial port and initilize iRobot. */
extern int32_t irobotOpen(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success status */

/* Close a session with an iRobot */
extern int32_t irobotClose(
	const irobotUARTPort_t	port		/* (in)		UART port					*/
);


#endif	/* _IROBOT_H */
