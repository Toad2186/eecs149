/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Initialization and deinitialization procedures for the iRobot Create.

	Revised:	2011-01-18
*/

#include "irobotUART.h"
#include "irobotSensor.h"
#include "irobotSensorPoll.h"
#include "irobotSensorStream.h"
#include "irobotActuator.h"
#include "irobotCommand.h"
#include "irobotTime.h"

/* Open UART serial port and initialize iRobot. */
extern int32_t irobotOpen(
	const irobotUARTPort_t	port		/* (in)		UART port					*/
){										/* (ret)	Error / success code		*/
	int32_t status = ERROR_SUCCESS;
	
	irobot_IfIsNotError(status, irobotUARTOpen(port, IROBOT_BAUD_57600));

	/* in case iRobot was just powered on, wait for it to start up */
	if(!irobot_IsError(status)){
		irobotDelayMs(5000);
	}
	
	/* put robot into start mode; delay for startup */
	irobot_IfIsNotError(status, irobotStart(port));
	if(!irobot_IsError(status)){
		irobotDelayMs(1000);
	}

	irobot_IfIsNotError(status, irobotFull(port));

	irobot_IfIsNotError(status, irobotStop(port));

	/* clear receive queue, which may have old sensor stream data */
	irobot_IfIsNotError(status, irobotSensorStreamPause(port, true));
	if(!irobot_IsError(status)){
		irobotDelayMs(250);
	}
	irobot_IfIsNotError(status, irobotUARTClear(port));

	/* set status LEDs */
	irobot_IfIsNotError(status, irobotLEDs(port, LED_ADVANCE_PLAY, 0, 255));

	return status;
}

/* Close a session with an iRobot */
extern int32_t irobotClose(
	const irobotUARTPort_t	port		/* (in)		UART port					*/
){										/* (ret)	Error / success code		*/
	int32_t status = ERROR_SUCCESS;

	/* Always attempt to stop, even if an error has occurred */
	irobot_StatusMerge(&status, irobotStop(port));

	/* Clear sensor stream */
	irobot_IfIsNotError(status, irobotSensorStreamPause(port, true));
	if(!irobot_IsError(status)){
		irobotDelayMs(150);
	}

	/* Clear UART */
	irobot_IfIsNotError(status, irobotUARTClear(port));

	/* reset LED state */
	irobot_IfIsNotError(status, irobotLEDs(port, LED_NONE, 255, 255));

	/* restore baud */
	irobot_IfIsNotError(status, irobotBaudChange(port, IROBOT_BAUD_57600));

	/* always close UART, even if an error has occurred */
	irobot_StatusMerge(&status, irobotUARTClose(port));

	return status;
}
