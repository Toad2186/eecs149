#include <msp430g2231.h>
#include <stdint.h>

#define TRIGGER BIT6
#define ECHO BIT7

#define TIMER_PERIOD 25000
#define TRIGGER_PULSE 1500// (TIMER_PERIOD - 10)

#define BASE 2800
#define STEP 600

/* Length to wait before changing modes */
#define PROG_COUNTER 60
/* Number of different modes */
#define NUM_PROG 4

/***** FOR PROG2 ******/
/* Length of time between changing LEDs */
#define LENGTH 28000
/* Greater value => Greater difference between time each LED is on */
#define SPREAD 7

/* Exponent for waitD */
#define EXP 5

int i = 0;
int j = 3;
volatile unsigned int k, l;
volatile unsigned int *kPtr = &k, *lPtr = &l;

static uint16_t echoPulseCount = 0;

void setupTriggerPulse() {
	P2DIR |= TRIGGER;
	P2OUT &=  ~TRIGGER;
	P2SEL |= TRIGGER;
	CCR0 = TIMER_PERIOD;
	CCR1 = TRIGGER_PULSE;
	CCTL1 = OUTMOD_7;
	TACTL = TASSEL_2 + MC_1 ;
	BCSCTL3 |= 0x30;
	__enable_interrupt();
}

void setupGpioEchoInterrupt() {
	P2DIR &= ~ECHO;
	P2OUT &= ~ECHO;
	P2SEL &= ~ECHO;
	P2IE |= ECHO;
	P2IES |= ~ECHO;
	P2IFG  &=  ~ECHO;
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2() {
	echoPulseCount = TA0R;
	if (echoPulseCount < BASE) {
		++i;
	} else {
		i = 0;
	}
	P2IFG &= ~ECHO;
}

void blink() {
	volatile unsigned int c = 35000;
	int o = 0;
	for(; o < (j % NUM_PROG) + 1; ++o) {
		P1OUT = 0xFF;
		while(c--);
		P1OUT = 0;
		c = 35000;
		while(c--);
	}
}

void update() {
	if (i > PROG_COUNTER) {
		P2IE |= ~ECHO;
		blink();
		++j;
		i = 0;
		P2IE |= ECHO;
	}
}

void waitR() {
	k = *kPtr;
	l = *lPtr;
	volatile unsigned int bound_k, bound_l;
	bound_k = 10000 + (k % LENGTH);
	bound_l = (l % SPREAD);
	kPtr = (unsigned int *) k;
	lPtr = (unsigned int *) l;
	k = bound_k;
	while(k-- != 0) {
		l = bound_l;
		while(l-- != 0);
	}
}

char getExp() {
	if (echoPulseCount < BASE) {
		return 1;
	} else if (echoPulseCount < BASE + STEP){
		return 3;
	} else if (echoPulseCount < BASE + STEP * 2) {
		return 1 + 2 * 2;
	} else if (echoPulseCount < BASE + STEP * 3) {
		return 1 + 2 * 3;
	} else if (echoPulseCount < BASE + STEP * 4) {
		return 1 + 2 * 4;
	} else if (echoPulseCount < BASE + STEP * 5) {
		return 1 + 2 * 5;
	} else if (echoPulseCount < BASE + STEP * 6) {
		return 1 + 2 * 6;
	} else if (echoPulseCount < BASE + STEP * 7) {
		return 1 + 2 * 7;
	} else {
		return 1 + 2 * 8;
	}
}

uint16_t getBase() {
	if (echoPulseCount < BASE) {
		return BASE;
	} else if (echoPulseCount < BASE + STEP){
		return BASE + STEP;
	} else if (echoPulseCount < BASE + STEP * 2) {
		return BASE + STEP * 2;
	} else if (echoPulseCount < BASE + STEP * 3) {
		return BASE + STEP * 3;
	} else if (echoPulseCount < BASE + STEP * 4) {
		return BASE + STEP * 4;
	} else if (echoPulseCount < BASE + STEP * 5) {
		return BASE + STEP * 5;
	} else if (echoPulseCount < BASE + STEP * 6) {
		return BASE + STEP * 6;
	} else if (echoPulseCount < BASE + STEP * 7) {
		return BASE + STEP * 7;
	} else {
		return BASE + STEP * 8;
	}
}

void waitD() {
	uint16_t b = getBase();
	volatile uint16_t lb = b;
	char e = getExp();
	volatile char le = e;
	while(le-- != 0) {
		while(lb-- != 0);
		lb = b;
	}
}

void prog1() {
	if (echoPulseCount < BASE) {
		P1OUT = 0x0;
	} else if (echoPulseCount < BASE + STEP){
		P1OUT = 0x1;
	} else if (echoPulseCount < BASE + STEP * 2) {
		P1OUT = 0x3;
	} else if (echoPulseCount < BASE + STEP * 3) {
		P1OUT = 0x7;
	} else if (echoPulseCount < BASE + STEP * 4) {
		P1OUT = 0xF;
	} else if (echoPulseCount < BASE + STEP * 5) {
		P1OUT = 0x1F;
	} else if (echoPulseCount < BASE + STEP * 6) {
		P1OUT = 0x3F;
	} else if (echoPulseCount < BASE + STEP * 7) {
		P1OUT = 0x7F;
	} else {
		P1OUT = 0xFF;
	}
	update();
}

void prog2() {
	waitR();
	if (P1OUT == 0x80) {
		P1OUT = 0;
	} else if (P1OUT == 0) {
		P1OUT = 0x1;
	} else {
		P1OUT = P1OUT << 1;
	}
	update();
}

void prog3() {
	waitR();
	if (P1OUT == 0) {
		P1OUT = 0x81;
	} else if (P1OUT == 0x81) {
		P1OUT = 0x42;
	} else if (P1OUT == 0x42) {
		P1OUT = 0x24;
	} else if (P1OUT == 0x24) {
		P1OUT = 0x18;
	} else {
		P1OUT = 0;
	}
	update();
}

void prog4() {
	P1OUT = 0xFF;
	waitD();
	P1OUT = 0;
	waitD();
	update();
}

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    // Use 1 MHz DCO factory calibration
    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
	P1DIR = 0xFF;					// Set P1.0 to output direction

    setupTriggerPulse();
    setupGpioEchoInterrupt();

    while(1) {
    	switch(j % NUM_PROG) {
    	case 0: prog1();
    			break;
    	case 1: prog2();
    			break;
    	case 2: prog3();
    			break;
    	case 3: prog4();
    			break;
    	}
    }

}
