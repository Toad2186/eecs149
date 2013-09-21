#include <stdio.h>
#include <stdint.h>
#include "xparameters.h"
#include "mb_interface.h"

// printf() from stdlib is too big; use the Xilinx xil_printf() function instead
#define printf xil_printf

// Associate memory-mapped registers with register names used in Xilinx documentation
#define TIMER0_INTR_MASK	XPAR_TIMER0_INTERRUPT_MASK
#define ADC_INTR_MASK 		XPAR_ADC_0_ADCINT_MASK

///************************************************************************************************
//Interrupt Controller Registers
#define INTC_IPR 	(*((volatile unsigned long *)(XPAR_INTC_0_BASEADDR + 0x04)))
#define INTC_IER 	(*((volatile unsigned long *)(XPAR_INTC_0_BASEADDR + 0x08)))
#define INTC_IAR 	(*((volatile unsigned long *)(XPAR_INTC_0_BASEADDR + 0x0C)))
#define INTC_MER 	(*((volatile unsigned long *)(XPAR_INTC_0_BASEADDR + 0x1C)))

///*************************************************************************************************
///Analog to Digital Converter(ADC) Registers
#define ADC_CTRL 	(*((volatile unsigned long *)(XPAR_ADC_0_BASEADDR)))
#define ADC_STATUS 	(*((volatile unsigned long *)(XPAR_ADC_0_BASEADDR + 0x004)))
#define ADC_IAR 	(*((volatile unsigned long *)(XPAR_ADC_0_BASEADDR + 0x008)))

//***************************************************************************************************
//TIMER Registers
#define TCSR0  		(*((volatile unsigned long *)(XPAR_TIMER0_BASEADDR + 0x00)))
#define TLR0  		(*((volatile unsigned long *)(XPAR_TIMER0_BASEADDR + 0x04)))
#define TCR0		(*((volatile unsigned long *)(XPAR_TIMER0_BASEADDR + 0x08)))

///***************************************************************************************************
//Digital IO Registers
// DIOB_70IN   = digital inputs myRIO MXP B/DIO0-7;  bit 0 corresponds to B/DIO0 and bit 7 to B/BIO7
// DIOB_158OUT = digital output myRIO MXP B/DIO8-15; bit 0 corresponds to B/DIO8 and bit 7 to B/BIO15
#define DIOB_158IN	(*((volatile unsigned long *)(XPAR_PORTDI_BASEADDR)))
#define DIOB_70OUT	(*((volatile unsigned long *)(XPAR_PORTDO_BASEADDR)))

//Global variables for debugging purposes; incremented when interrupts fire
volatile uint32_t	primaryIsrCount = 0;
volatile uint32_t	adcIsrCount = 0;
volatile uint32_t	timerIsrCount = 0;

//Global variables to hold ADC conversion results
volatile uint32_t	channel0 = 0;
volatile uint32_t 	channel1 = 0;
volatile uint32_t	channel2 = 0;

volatile char flag = 0;


// Function prototypes
// TODO: For interrupt exercises, signal the compiler that primary_ISR is an interrupt handler
void primary_ISR (void) __attribute__((interrupt_handler));
void timer_ISR(void) ;
void ADC_ISR(void);

// Primary ISR: call interrupt handlers for active interrupts
void primary_ISR (void){
	primaryIsrCount++;

	// TODO: Determine which interrupt fired and call appropriate ISR
	timer_ISR();
	// Acknowledge master interrupts
	INTC_IAR = INTC_IPR;
 }

// Timer ISR
void timer_ISR(void){
	timerIsrCount++;
	ADC_CTRL = 0x00020001;
//	asm("nop");
//	asm("nop");
//	asm("nop");
//	asm("nop");
	while(ADC_STATUS & 1);
	channel2 = (ADC_STATUS & 0x0FFF0000) >> 16;
	//ADC_IAR = 0;
	ADC_CTRL = 0x00020000;
	//flag = !flag;
	//DIOB_70OUT = flag; // Flip DIO line to drive speakers
	TCSR0 = TCSR0 | 0x00000100; // Acknowledge interrupt
 	// TODO: the body of your timer ISR goes here

	// TODO: Acknowledge the timer interrupt
	// Without this acknowledgment, MicroBlaze processor will remain
	// interrupted by the Timer. The program will halt and the debugger
	// will not be able to connect until MicroBlaze is restarted.
	// If this occurs:
	//     1. Close Xilinx SDK
	//     2. Disconnect and reconnect the JTAG debugger from the computer.
	//     3. Restart SDK.
	
 }

// ADC ISR: fires when ADC conversion complete
void ADC_ISR(void){
	adcIsrCount++;

	//TODO: The body of your ADC ISR lives here.

	//TODO: Acknowledge the ADC interrupt
}

// Main program loop
int main(void){
	// Clock is 50 MHz
	// TODO: Configure timer
	 			///TODO: Load the value for timer to count down.
						//Hint : read Xilinx documentation(DS764) on AXI Timer IP  .
	TLR0 = 250000;
	//TLR0 = 1;
	TCSR0 = 0b10000;
	// 0b0000 1110 0010
	TCSR0 = 0x000000D2;		///TODO: Setup timer with interrupt enable and start to count continuously
						//Hint : read Xilinx documentation(DS764) on AXI Timer IP  .

	// TODO: Enable interrupts
	INTC_IER = TIMER0_INTR_MASK; ///TODO: Turn on correct interrupts in order to enable them.
	               //Hint : read Xilinx documentation(DS747) on AXI INTC IP  .
	//INTC_IER = ADC_INTR_MASK;
	INTC_MER = 0b11; ///TODO: Enable Master and Hardware interrupt of the system.
	               //Hint : read Xilinx documentation(DS747) on AXI INTC IP  .

	// This call will allow event to interrupt MicroBlaze core
	microblaze_enable_interrupts();

	for(;;){
		// Print a debug message to the console
		printf(
			"channel0 = %05d\t"
			"channel1 = %05d\t"
			"channel2 = %05d\t"
			"primaryIsrCount = %03d\t"
			"timerIsrCount = %03d\t"
			"adcIsrCount = %03d\n",
			channel0,
			channel1,
			channel2,
			primaryIsrCount,
			timerIsrCount,
			adcIsrCount
		);
	}

    return 0;
}
