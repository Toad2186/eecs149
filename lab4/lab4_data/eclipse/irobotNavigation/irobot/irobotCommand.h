/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	iRobot generic commands.

	Revised:	2011-01-18
*/

#ifndef _IROBOTCOMMAND_H
#define _IROBOTCOMMAND_H

#include "irobotOpcode.h"
#include "irobotUART.h"
#include "irobotError.h"

typedef enum{
	DEMO_COVER				= 0,
	DEMO_COVER_DUCK			= 1,
	DEMO_SPOT_COVER			= 2,
	DEMO_MOUSE				= 3,
	DEMO_DRIVE_FIGURE_EIGHT	= 4,
	DEMO_WIMP				= 5,
	DEMO_HOME				= 6,
	DEMO_TAG				= 7,
	DEMO_PACHELBEL			= 8,
	DEMO_BANJO				= 9
} irobotDemo_t;

/*	Set the iRobot baud rate; the serial port will be reconfigured to this new
	baud rate and restarted, which will clear communication buffers and may introduce a delay. 

	Note: Baud 115200 appears to be unstable. */
extern int32_t irobotBaudChange(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotBaud_t		baud		/* (in)		iRobot baud code */
);										/* (ret)	Error / success code */

/* Stop a running demo */
extern int32_t irobotDemoStop(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success code */

/* Run a demo */
extern int32_t irobotDemo(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotDemo_t		demo		/* (in)		demo to run */
);										/* (ret)	Error / success code */

/* Change to FULL mode */
extern int32_t irobotFull(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success code */

/* Change to SAFE mode */
extern int32_t irobotSafe(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success code */

/* Change to START mode */
extern int32_t irobotStart(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success code */


#endif /* _IROBOTCOMMAND_H */
