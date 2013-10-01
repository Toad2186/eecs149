/*  Author: 	Jeff C. Jensen
 *				National Instruments
 *  
 *  Project:	EECS 149, University of California Berkeley
 *  
 *  Abstract:	Definition and prototypes for xqueue data structure. xqueue is designed for use
 * 				in communication systems and concurrent environments where two processes may
 * 				access the queue, though exclusively one will read and one will write. Read and
 * 				write counts are tracked separately for this reason.
 * 
 * 				xqueues are initialized with the address of a buffer and its size, which must
 * 				be a power of two. This is to allow for simple circular access to the buffer
 * 				via masking, instead using a costly modulo operator.
 * 
 *  Revised:	2011-01-22
 */

#ifndef _XQUEUE_H
#define _XQUEUE_H

#include "irobotTypes.h"

/* xqueue_t structure: queue with arbitrary length
 * 	Separation of write/read count allows for use in concurrent environments */
typedef struct{
	uint8_t		*data;			/* Assigned on initialization to existing buffer */
	size_t		head;			/* Buffer write index */
	size_t		tail;			/* Buffer read index */
	size_t		rCount;			/* Read count */
	size_t		wCount;			/* Write count */
	size_t		capacity;		/* Maximum size of the data buffer (must be a power of 2, <= 0x8000) */
	size_t		capacityMask;	/* Mask used instead of costly modulo operator */
} xqueue_t;

/* Initialize a queue */
extern void xqueue_init(xqueue_t * const queue,			/* (out)	Queue struct to initialize */
						uint8_t * const dataBuffer,		/* (out)	Raw buffer to which queue will attach */
						const size_t size				/* (in)		Size of the raw buffer */
);														/* (ret)	(void) */

/* Return the number of used elements in the queue */
extern size_t xqueue_count(const xqueue_t * const queue);

/* Return whether or not the queue is empty */
extern bool xqueue_empty(const xqueue_t * const queue);

/* Return whether or not the queue is full */
extern bool xqueue_full(const xqueue_t * const queue);

/* Return the number of free elements in the queue  */
extern size_t xqueue_space(const xqueue_t * const queue);

/* Return the front element of the queue */
extern uint8_t xqueue_front(const xqueue_t * const queue);

/* Return the back (most recently added) element of the queue */
extern uint8_t xqueue_back(const xqueue_t * const queue);

/* Index an element of the queue */
extern uint8_t xqueue_at(const xqueue_t * const queue, const size_t index);

/* Clears a queue; retains buffer address and maximum size */
extern void xqueue_clear(xqueue_t * const queue);

/* Push a single element on to a queue */
extern uint8_t xqueue_push(xqueue_t * const queue,	/* (i/o)	Target queue */
				 const uint8_t value				/* (in)		byte to add to queue */
);													/* (ret)	Value pushed (for chaining) */

/* Push 8 bits (one element) to a queue */
#define xqueue_push8 xqueue_push

/* Push a 16-bit number to the queue (2 elements) */
extern void xqueue_push16(xqueue_t * const queue, const uint16_t value);

/* Push a 32-bit number to the queue (4 elements) */
extern void xqueue_push32(xqueue_t * const queue, const uint32_t value);

/* Push a stream on to a queue (faster than push_string) */
extern void xqueue_push_buffer(	xqueue_t * const queue,		/* (i/o)	Target queue */
								const uint8_t * values,		/* (in)		Stream to push to queue */
								const size_t nvalues		/* (in)		Number of elements to push */
);															/* (ret)	(void) */

/* Push a (null-terminated) string on to a queue */
extern void xqueue_push_string(	xqueue_t * const queue,		/* (i/o)	Target queue */
								const unsigned char * str	/* (in)		String to push to queue (NULL is not pushed) */
);															/* (ret)	(void) */

/* Pop an element from a queue */
extern uint8_t xqueue_pop(xqueue_t * const queue);

#define xqueue_pop8	xqueue_pop						/* Pop an 8-bit value from a queue */

/* Pop 16 bits (two elements) from a queue */
extern uint16_t xqueue_pop16(xqueue_t * const queue);

/* Pop 32 bits (four elements) from a queue  */
extern uint32_t xqueue_pop32(xqueue_t * const queue);

/* Pop a sequence of elements from a queue */
extern void xqueue_pop_buffer(	xqueue_t * const queue,		/* (i/o)	Source queue */
								uint8_t * values,			/* (out)	Stream to fill with values */
								const size_t nvalues		/* (in)		Number of elements to pop */
);															/* (ret)	(void) */

/* Pop an element from a queue; do not return value (fast) */
extern void xqueue_drop(xqueue_t * const queue);

/* Pops many elements from a queue (fast) */
extern void xqueue_drop_many(xqueue_t * const queue, size_t nvalues);

/* Returns the checksum of n elements currently in the queue */
extern uint8_t xqueue_checksum(	const xqueue_t * const queue,	/* (in)	Source queue */
								size_t nvalues,					/* (in)	Number of values over which to sum */
								const size_t nAdvance			/* (in)	Number of elements to advance before calculating checksum */
);																/* (ret)	Checksum of queue[fromCount] to queue[fromCount + nvalues] */


#endif	/* _XQUEUE_H */
