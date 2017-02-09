// filename ******** Switch.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "Switch.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF3							(*((volatile uint32_t *)0x40025020))
#define PF4   					(*((volatile uint32_t *)0x40025040))
	
//void DelayWait10ms(uint32_t);

uint16_t counter4 = 0;
uint16_t counter5 = 0;

void PortF_Init() {
	SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F clock
	while((SYSCTL_PRGPIO_R&0x20)==0){}; 	// allow time for clock to start

	GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x16;          // disable alt funct on PF4, PF2, PF1

  GPIO_PORTF_DEN_R |= 0x16;             // enable digital I/O on PF4, PF2, PF1
                                        // configure PF2 as GPIO
  //GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
	GPIO_PORTF_PUR_R |= 0x10;         // 5) pullup for PF4

  PF2 = 0;                  				    // turn off LED
	PF1 = 0;
}
//pf4 for speaker, switches on pf0-3

void PortD_Init() {
	SYSCTL_RCGCGPIO_R |= 0x08;            // activate port D clock
	while((SYSCTL_PRGPIO_R&0x08)==0){}; 	// allow time for clock to start

	GPIO_PORTD_DIR_R |= 0x02;             // make PD2 out 
  GPIO_PORTD_AFSEL_R &= ~0x02;          // disable alt funct on PD2
  GPIO_PORTD_DEN_R |= 0x02;             // enable digital I/O on PD2
                                        // configure PD2 as GPIO
  //GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTD_AMSEL_R = 0;               // disable analog functionality on PD

	//PF3 = 0;
}

void PortE_Init() { // switches are connected to PortE
	SYSCTL_RCGCGPIO_R |= 0x10;		// activate clock for Port E
	while((SYSCTL_PRGPIO_R&0x10)==0){}; 	// allow time for clock to start
	GPIO_PORTE_DIR_R &= ~0x30;		// make PE5-4 in
	GPIO_PORTE_DEN_R |= 0x30; 		// enable digital I/O on PE5-4
	GPIO_PORTE_IS_R &= ~0x30;			// PE5-4 is edge-sensitive
	GPIO_PORTE_IBE_R &= ~0x30;		// PE5-4 is not both edges
	GPIO_PORTE_IEV_R |= 0x30;			// PE5-4 rising edge event
	GPIO_PORTE_ICR_R = 0x30;			// clear flag5-4
	GPIO_PORTE_IM_R |= 0x30;			// arm interrupts on PE5-4
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000040;	// PortE=priority 2
	NVIC_EN0_R = 1<<4; 	// enable interrupt 4 in NVIC
}

void GPIOPortE_Handler(void) {
	if(GPIO_PORTE_RIS_R&0x10) {		// poll PE4
		GPIO_PORTE_ICR_R = 0x10;		// acknowledge flag4
		DelayWait10ms(10);
		if(GPIO_PORTE_DATA_R&0x10) {
			//PF2 ^= 0x04;
		}

	}
	if(GPIO_PORTE_RIS_R&0x20) {		// poll PE5
		GPIO_PORTE_ICR_R = 0x20;		// acknowledge flag5
		DelayWait10ms(10);
		if(GPIO_PORTE_DATA_R&0x20) {
			//PF1 ^= 0x02;
		}
	}
}


// Subroutine to wait 10 msec
// Inputs: None
// Outputs: None
// Notes: ...
void DelayWait10ms(uint32_t n){uint32_t volatile time;
	while(n){
    time = 727240*2/91;  // 10msec
    while(time){
	  	time--;
    }
    n--;
  }
}

