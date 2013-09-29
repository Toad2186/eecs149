/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Revised:	2011-01-18
*/

#include "irobotUART.h"

static MyRio_Uart _UART1 = {"ASRL1::INSTR", 0, 0};
static MyRio_Uart _UART2 = {"ASRL2::INSTR", 0, 0};

irobotUARTPort_t UART1 = &_UART1;
irobotUARTPort_t UART2 = &_UART2;

/*********************/
/* Private Functions */
/*********************/

/* Convert a baud code into its actual rate */
static int32_t irobotUARTBaudCodeToRate(
	const irobotBaud_t	baud,		/* (in)		baud code */
	uint32_t * const	rate		/* (out)	baud rate */
){									/* (ret)	Error / success code */
	if(!rate){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		switch(baud){
		case IROBOT_BAUD_300:	*rate = 300;	break;
		case IROBOT_BAUD_600:	*rate = 600;	break;
		case IROBOT_BAUD_1200:	*rate = 1200;	break;
		case IROBOT_BAUD_2400:	*rate = 2400;	break;
		case IROBOT_BAUD_4800:	*rate = 4800;	break;
		case IROBOT_BAUD_9600:	*rate = 9600;	break;
		case IROBOT_BAUD_14400:	*rate = 14400;	break;
		case IROBOT_BAUD_19200:	*rate = 19200;	break;
		case IROBOT_BAUD_28800:	*rate = 28800;	break;
		case IROBOT_BAUD_38400:	*rate = 38400;	break;
		case IROBOT_BAUD_57600:	*rate = 57600;	break;
		case IROBOT_BAUD_115200:*rate = 115200;	break;	/* WARNING: UNSTABLE */
		default:
			*rate = 0;
			return ERROR_INVALID_PARAMETER;
			break;
		}

		return ERROR_SUCCESS;
	}
}

/* Opens a UART session configured for the iRobot */
extern int32_t irobotUARTOpen(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	const irobotBaud_t		baud		/* (in)		baud code of the port */
){										/* (ret)	Error / success code */
	int32_t status = ERROR_SUCCESS;
	uint32_t baudRate = 0;
	
	irobot_StatusMerge(&status, irobotUARTBaudCodeToRate(baud, &baudRate));

	if(!irobot_IsError(status)){
		irobot_StatusMerge(
			&status,
			Uart_Open(
				port,
				baudRate,
				8,
				Uart_StopBits1_0,
				Uart_ParityNone
			)
		);
	}
	/**
	 * Opens a UART session.
	 */
	int32_t Uart_Open(MyRio_Uart* port, const uint32_t baud,
	                  const uint8_t dataBits, const Uart_StopBits stopBits,
	                  const Uart_Parity parity);
	return status;
}

/* Closes the UART port connected to iRobot. The port must be reinitialized before reuse. */
extern int32_t irobotUARTClose(
	const irobotUARTPort_t	port		/* (in)		UART port */
){										/* (ret)	Error / success code */
	return Uart_Close(port);
}

/* Read data from the UART receive buffer until # have been
 * received, or until a timeout occurs. A negative timeout means wait indefinitely.
 * Read bytes are pushed to the queue; if the queue is full, its oldest bytes are dropped.
 */
extern int32_t irobotUARTRead(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	xqueue_t * const		queue,		/* (out)	Queue to receive read data */
	size_t					nData		/* (in)		Number of bytes to read */
){										/* (ret)	Error / success code */
	int32_t status = ERROR_SUCCESS;

	/* catch NULL pointers */
	if(!queue){
		irobot_StatusMerge(&status, ERROR_INVALID_PARAMETER);
	}
	
	/* read */
	while(!irobot_IsError(status) && nData--){
		uint8_t rxByte = 0;
		irobot_StatusMerge(&status, irobotUARTReadRaw(port, &rxByte, 1));
		if(!irobot_IsError(status)){
			xqueue_push8(queue, rxByte);
		}
	}

	return status;
}

/* Read data from the UART receive buffer until # have been
 * received, or until a timeout occurs. A negative timeout means wait indefinitely. */
extern int32_t irobotUARTReadRaw(
	const irobotUARTPort_t	port,		/* (in)		UART port */
	uint8_t * const			data,		/* (out)	Buffer to receive read data */
	const size_t			nData		/* (in)		Number of bytes to read */
){										/* (ret)	Error / success code */
	/* catch NULL pointers */
	if(!data){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		return Uart_Read(port, data, nData);
	}
}

/* Writes a queue to the UART port. If not enough space is available in the FIFO,
  this function blocks until sufficient space is available or a timeout occurs.
  Elements written are popped from the queue.
  */
extern int32_t irobotUARTWrite(
	const irobotUARTPort_t	port,		/* (in)		UART port to access */
	xqueue_t * const		queue		/* (in)		Queue data to write; all will be written */
){										/* (ret)	Error / success code */
	int32_t status = ERROR_SUCCESS;

	/* catch NULL pointers */
	if(!queue){
		irobot_StatusMerge(&status, ERROR_INVALID_PARAMETER);
	}
	
	/* write */
	while(!irobot_IsError(status) && !xqueue_empty(queue)){
		uint8_t txByte = xqueue_front(queue);
		irobot_StatusMerge(&status, irobotUARTWriteRaw(port, &txByte, 1));
		if(!irobot_IsError(status)){
			xqueue_drop(queue);
		}
	}

	return status;
}

/* Writes data to the UART port. If not enough space is available in the FIFO,
  this function blocks until sufficient space is available or a timeout occurs. */
extern int32_t irobotUARTWriteRaw(
	const irobotUARTPort_t	port,		/* (in)		UART port to access */
	const uint8_t * const	data,		/* (in)		Array of data to write */
	const size_t			nData		/* (in)		Size of data array */
){										/* (ret)	Error / success code */
	/* catch NULL pointers */
	if(!data){
		return ERROR_INVALID_PARAMETER;
	}
	else{
		return Uart_Write(port, data, nData);
	}
}

/* Clears the UART receive buffer. */
extern int32_t irobotUARTClear(
	const irobotUARTPort_t	port		/* (in)		UART port to access */
){										/* (ret)	Error / success code */
	return Uart_Clear(port);
}

