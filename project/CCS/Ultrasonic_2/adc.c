/*
 * adc.c
 *
 *  Created on: Nov 6, 2013
 *      Author: tvuong
 */

#include "msp430g2231.h"
#include "decl.h"

bool isReceiving;
bool hasReceived;

bool ADCDone;			// ADC Done flag
unsigned int ADCValue;	// Measured ADC Value
/**
* Reads ADC 'chan' once using AVCC as the reference.
**/
void Single_Measure(unsigned int chan)
{
	ADC10CTL0 &= ~ENC;				// Disable ADC
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;	// 16 clock ticks, ADC On, enable ADC interrupt
	ADC10CTL1 = ADC10SSEL_3 + chan;				// Set 'chan', SMCLK
	ADC10CTL0 |= ENC + ADC10SC;             	// Enable and start conversion
}

/**
* ADC interrupt routine. Pulls CPU out of sleep mode for the main loop.
**/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	ADCValue = ADC10MEM;			// Saves measured value.
	ADCDone = true;  			// Sets flag for main loop.
//	__bic_SR_register_on_exit(CPUOFF);	// Enable CPU so the main while loop continues
}
