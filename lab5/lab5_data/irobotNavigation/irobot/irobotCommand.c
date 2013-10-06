/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	iRobot generic commands.

	Revised:	2011-01-18
*/

#include "irobotCommand.h"
#include "irobotTime.h"

/*	Set the iRobot baud rate; the serial port will be reconfigured to this new
	baud rate and restarted, which will clear communication buffers and may introduce a delay. 

	Note: Baud 115200 appears to be unstable. */
extern int32_t irobotBaudChange(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotBaud_t		baud		/* (in)		iRobot baud code */
){										/* (ret)	Error / success code */
	int32_t status = ERROR_SUCCESS;
	uint8_t packet[OP_BAUD_SIZE];

	packet[0] = OP_BAUD;
	packet[1] = (uint8_t)baud;
	
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTWriteRaw(port, packet, OP_BAUD_SIZE));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTClose(port));
	}
	if(!irobot_IsError(status)){
		irobot_StatusMerge(&status, irobotUARTOpen(port, baud));
		irobotDelayMs(50); /* delay 50ms */
	}

	return status;
}

/* Stop a running demo */
extern int32_t irobotDemoStop(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_DEMO_SIZE];

	packet[0] = OP_DEMO;
	packet[1] = 0xFF;		/* special case; stop all demos */
	
	return irobotUARTWriteRaw(port, packet, OP_DEMO_SIZE);
}

/* Run a demo */
extern int32_t irobotDemo(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotDemo_t		demo		/* (in)		demo to run */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_DEMO_SIZE];

	packet[0] = OP_DEMO;
	packet[1] = (uint8_t)demo;
	
	return irobotUARTWriteRaw(port, packet, OP_DEMO_SIZE);
}

/* Change to FULL mode */
extern int32_t irobotFull(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_FULL_SIZE];

	packet[0] = OP_FULL;
	
	return irobotUARTWriteRaw(port, packet, OP_FULL_SIZE);
}

/* Change to SAFE mode */
extern int32_t irobotSafe(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_SAFE_SIZE];

	packet[0] = OP_SAFE;
	
	return irobotUARTWriteRaw(port, packet, OP_SAFE_SIZE);
}

/* Change to START mode */
extern int32_t irobotStart(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	uint8_t packet[OP_START_SIZE];

	packet[0] = OP_START;
	
	return irobotUARTWriteRaw(port, packet, OP_START_SIZE);
}

