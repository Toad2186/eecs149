/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	UART wrappers for the iRobot Create. This library is not architecture
				specific, so these are only wrappers for UART functions that must
				be defined for your architecture.

	Revised:	2011-01-18
*/

#ifndef _IROBOT_UART_H
#define _IROBOT_UART_H

#include "irobotTypes.h"
#include "irobotError.h"
#include "xqueue.h"
#include "../UART.h"

/* UART port wrapper */
/* Change for your UART API */
typedef MyRio_Uart * irobotUARTPort_t;

extern irobotUARTPort_t UART1;
extern irobotUARTPort_t UART2;

/* Baud rate codes */
typedef enum{
	IROBOT_BAUD_300		= 0,
	IROBOT_BAUD_600		= 1,
	IROBOT_BAUD_1200	= 2,
	IROBOT_BAUD_2400	= 3,
	IROBOT_BAUD_4800	= 4,
	IROBOT_BAUD_9600	= 5,
	IROBOT_BAUD_14400	= 6,
	IROBOT_BAUD_19200	= 7,
	IROBOT_BAUD_28800	= 8,
	IROBOT_BAUD_38400	= 9,
	IROBOT_BAUD_57600	= 10,
	IROBOT_BAUD_115200	= 11	/* NOTE: This may not be a stable baud. */
} irobotBaud_t;

/* Opens a UART session configured for the iRobot */
extern int32_t irobotUARTOpen(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotBaud_t		baud		/* (in)		baud rate of the port */
);										/* (ret)	Error / success code */

/* Closes the UART port connected to iRobot. The port must be reinitialized before reuse. */
extern int32_t irobotUARTClose(
	const irobotUARTPort_t	port		/* (in)		UART port */
);										/* (ret)	Error / success code */

/* Read data from the UART receive buffer until # have been
 * received, or until a timeout occurs. A negative timeout means wait indefinitely.
 * Read bytes are pushed to the queue; if the queue is full, its oldest bytes are dropped.
 */
extern int32_t irobotUARTRead(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	xqueue_t * const		queue,		/* (out)	Queue to receive read data */
	size_t					nData		/* (in)		Number of bytes to read */
);										/* (ret)	Error / success code */

/* Read data from the UART receive buffer until # have been
 * received, or until a timeout occurs. A negative timeout means wait indefinitely. */
extern int32_t irobotUARTReadRaw(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	uint8_t * const			data,		/* (out)	Buffer to receive read data */
	const size_t			nData		/* (in)		Number of bytes to read */
);										/* (ret)	Error / success code */

/* Writes a queue to the UART port. If not enough space is available in the FIFO,
  this function blocks until sufficient space is available or a timeout occurs.
  Elements written are popped from the queue.
  */
extern int32_t irobotUARTWrite(
	const irobotUARTPort_t	port,		/* (in)		UART port to access */
	xqueue_t * const		queue		/* (in)		Queue data to write; all will be written */
);										/* (ret)	Error / success code */

/* Writes data to the UART port. If not enough space is available in the FIFO,
  this function blocks until sufficient space is available or a timeout occurs. */
extern int32_t irobotUARTWriteRaw(
	const irobotUARTPort_t	port,		/* (in)		UART port to access */
	const uint8_t * const	data,		/* (in)		Array of data to write */
	const size_t			nData		/* (in)		Size of data array */
);										/* (ret)	Error / success code */

/* Clears the UART receive buffer. */
extern int32_t irobotUARTClear(
	const irobotUARTPort_t	port		/* (in)		UART port to access */
);										/* (ret)	Error / success code */

#endif	/* _IROBOT_UART_H */
