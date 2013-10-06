/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Revised:	2011-12-20
*/

/*	Author: 	Jeff C. Jensen
 				National Instruments

	Abstract:	Boolean and bit-level functions; common data types

	Revised:	2011-12-20
*/

#ifndef _IROBOTTYPES_H
#define _IROBOTTYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Byte-level operations - extract bytes from 16 and 32-bit numbers */
#define LO(x)					((x) & 0xFF)			/* Low order byte of a 16 bit number */
#define HO(x)					((x) >> 0x08)			/* High order byte of a 16 bit number */
#define LLO(x)					((x) & 0xFF)			/* Byte 0 (lowest order) byte of a 32-bit number */
#define LHO(x)					(((x) >> 0x08) & 0xFF)	/* Byte 1 of a 32-bit number */
#define HLO(x)					(((x) >> 0x10) & 0xFF)	/* Byte 2 of a 32-bit number */
#define HHO(x)					((x) >> 0x18)			/* Byte 3 (highest order) byte of a 32-bit number */

/* Byte-level operations - reconstruct 16 and 32-bit numbers from constituent bytes */
#define MLO(x)					((uint16_t)( ((uint8_t)(x)) & 0xFF ))	/* Convert a byte to Byte 0 of a 16-bit number */
#define MHO(x)					((uint16_t)( MLO(x) << 0x08 )		)	/* Convert a byte to Byte 1 of a 16-bit number */
#define MLLO(x)					((uint32_t)( MLO(x) )				)				/* Convert a byte to Byte 0 of a 32-bit number */
#define MLHO(x)					((uint32_t)(  (uint32_t)MHO(x) ) 				)	/* Convert a byte to Byte 1 of a 32-bit number */
#define MHLO(x)					((uint32_t)( ((uint32_t)MLO(x)) << 0x10 )		)	/* Convert a byte to Byte 2 of a 32-bit number */
#define MHHO(x)					((uint32_t)( ((uint32_t)MLO(x)) << 0x18 )		)	/* Convert a byte to Byte 3 of a 32-bit number */

/* Gives a byte-level checksum of a number */
#define CX8(x)					((uint8_t)x)
#define CX16(x)					((uint8_t)(HO(x) + LO(x))	)
#define CX32(x)					((uint8_t)(HHO(x) + HLO(x) + LHO(x) + LLO(x)))

#endif	/* _IROBOTTYPES_H  */
