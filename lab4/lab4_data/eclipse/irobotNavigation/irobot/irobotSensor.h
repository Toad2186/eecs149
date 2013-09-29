/*	Project:	iRobot Create
	
	Author:		Jeff C. Jensen
				National Instruments
  
	Abstract:	Functions to read sensors from a data stream

	Revised:	2011-12-20
*/

#ifndef _IROBOTSENSOR_H
#define _IROBOTSENSOR_H

#include "irobotSensorTypes.h"
#include "irobotError.h"
#include "xqueue.h"

/* read a sensor from a data queue */
extern int32_t irobotReadBumps_Wheeldrops(
	xqueue_t * const queue,									/* (i/o) */
	irobotBumps_WheelDrops_t * const bumps_wheelDrops		/* (out) */
);

/* read a sensor from a data queue */
extern int32_t irobotReadButtons(
	xqueue_t * const queue,			/* (i/o) */
	irobotButtons_t * const buttons	/* (out) */
);

/* read a sensor from a data queue */
extern int32_t irobotReadCargoBayDigitalInputs(
	xqueue_t * const queue,								/* (i/o) */
	irobotCargoBayDigitalInputs_t * const digitalInputs	/* (out) */
);

/* read a sensor from a data queue */
extern int32_t irobotReadChargingSourcesAvailable(
	xqueue_t * const queue,								/* (i/o) */
	irobotChargingSourcesAvailable_t * const sources	/* (out) */
);

/* read a sensor from a data queue */
extern int32_t irobotReadLowSideDriver_WheelOvercurrent(
	xqueue_t * const queue,										/* (i/o) */
	irobotLowSideDriver_WheelOvercurrent_t * const lsd_wo		/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup0(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup0_t * const sensorGroup0	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup1(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup1_t * const sensorGroup1	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup2(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup2_t * const sensorGroup2	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup3(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup3_t * const sensorGroup3	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup4(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup4_t * const sensorGroup4	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup5(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup5_t * const sensorGroup5	/* (out) */
);

/* read a sensor group from a data queue */
extern int32_t irobotReadSensorGroup6(
	xqueue_t * const queue,						/* (i/o) */
	irobotSensorGroup6_t * const sensorGroup6	/* (out) */
);

/* print all irobot sensors */
extern int32_t irobotPrintSensorGroup6(
	const irobotSensorGroup6_t * const sensors
);


#endif	/* _IROBOTSENSOR_H */
