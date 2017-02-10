// filename ******** Timer.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "LCD.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
#define PF2             (*((volatile uint32_t *)0x40025010))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

struct Alarm {
	uint16_t hour;
	uint16_t minute;
};
typedef struct Alarm Alarm;

static const uint32_t size = 100;

uint16_t second = 0;
uint16_t minute = 0;
uint16_t hour = 1;
Alarm alarmList[size];
uint32_t alarmEntries = 0;

// This debug function initializes Timer0A to request interrupts
// at a 100 Hz frequency.  It is similar to FreqMeasure.c.
void Timer0A_Init1HzInt(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = 79999999;         // start value for 1 Hz interrupts 79999999
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
}

bool newMinute = false;
bool newHour = false;
void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
	long sr = StartCritical();
  PF2 ^= 0x04;                   // heartbeat
	second++;
	newMinute = false;
	newHour = false;
	//if(second == 60) { // reached end of minute
	if(second == 1) { // reached end of minute
		minute++;
		newMinute = true;
		second = 0;
		if(minute == 60) { // reached end of hour
			minute = 0;
			hour++;
			newHour = true;
			if(hour == 13) { // reached end of 12-hr interval
				hour = 1;
			}
		}
	}
	
	EndCritical(sr);
	
//	if(newMinute)
//		DisplayMinute();
//	if(newHour)
//		DisplayHour();
}

uint32_t GetHour(){
	return hour;
}

uint32_t GetMinute(){
	return minute;
}


/* alarm search, put this somewhere else
	for(int i = 0; i < alarmEntries; i++) { // see if an alarm is set for this time
		if(hour == alarmList[i].hour && minute == alarmList[i].minute) {
			// alarm needs to go off
			break;
		}
	}
*/
