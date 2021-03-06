// filename ******** main.h ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.c"
#include "../Lab1/fixed.c"
#include "PLL.h"
#include <stdbool.h>
#include <stdint.h>
#include "Timer.h"
#include "Switch.h"
#include "LCD.h"
#include "Speaker.h"
#include "DigitalDisplay.h"
#include "AnalogDisplay.h"

#define PF1             (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void DelayWait10ms(uint32_t);

bool AlarmOn = false;

int main(void){

	PLL_Init(Bus80MHz);                   // 80 MHz
	Output_Init();
	Timer0A_Init1HzInt();
	//Timer1A_Init100HzInt();
	PortF_Init();
	PortE_Init();
	//InitAnalogTimerDisplay();
	DisplayMainMenu(0);
	EnableInterrupts();
	while(1){
		if(GetAlarmOn()) { // if an alarm is on
			OutputSound(GetAlarmPitch()); // toggles PF1 every 1 ms
		}
		CheckFlags();
	}
}


