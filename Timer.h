// filename ******** Timer.h ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>

//------------Timer0A_Init1HzInt------------
// Initializing of Timer with 1 Hz interrupts
// Input: none
// Output: none
void Timer0A_Init1HzInt(void);

//------------Timer0A_Handler------------
// Handler for Timer0A interrupts
// Input: none
// Output: none
void Timer0A_Handler(void);

//------------GetHour----------------------
//Returns the current hour of the timer
// Input: none
// Output: The current hour of the timer
uint32_t GetHour(void);

//------------GetHour----------------------
//Returns the current minute of the timer
// Input: none
// Output: The current minute of the timer
uint32_t GetMinute(void);
