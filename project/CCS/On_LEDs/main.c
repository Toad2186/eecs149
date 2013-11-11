#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1DIR = 0xFF;					// Set P1.0 to output direction
	for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization
		if (P1OUT) {
			P1OUT = P1OUT << 1;
		} else {
			P1OUT = 1;
		}
		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}
	return 0;
}
