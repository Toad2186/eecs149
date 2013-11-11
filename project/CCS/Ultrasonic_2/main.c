/*
 * main.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: tvuong
 */

#include "msp430g2231.h"
#include "decl.h"
#include "stdbool.h"

void setup(void) {
    // Disable watchdog
    WDTCTL = WDTPW + WDTHOLD;

    // Use 1 MHz DCO factory calibration
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Setup the serial port
    // Serial out: P1.1 (BIT1)
    // Serial in:  P1.2 (BIT2)
    // Bit rate:   9600 (CPU freq / bit rate)
    serial_setup(BIT1, BIT2, 1000000 / 9600);


    isReceiving = false;
    hasReceived = false;
    ADCDone = false;

	__bis_SR_register(GIE); // interrupts enabled
	Single_Measure(3);

}

void main(void)
{
	setup();
	while(1) {
		//while(getc() != 'a');
		if(ADCDone) {
			ADCDone = false;
			printf("%u\r\n", ADCValue);
			Single_Measure(INCH_3);
		}
	}
}


