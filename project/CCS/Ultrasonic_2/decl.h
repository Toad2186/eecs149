/*
 * decl.h
 *
 *  Created on: Nov 6, 2013
 *      Author: tvuong
 */

#ifndef DECL_H_
#define DECL_H_
#include "stdbool.h"

void serial_setup(unsigned out_mask, unsigned in_mask, unsigned duration);
void printf(char *, ...);
void putc(unsigned);
void puts(char *);
char getc();
void Single_Measure(unsigned int);

extern bool isReceiving;
extern bool hasReceived;

extern bool ADCDone;			// ADC Done flag
extern unsigned int ADCValue;	// Measured ADC Value

#endif /* DECL_H_ */
