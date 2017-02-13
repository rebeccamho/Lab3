// filename ******** AnalogDisplay.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>
#include "LCD.h"

struct AnalogDigitCenter {
	int16_t x;
	int16_t y;
};
typedef struct AnalogDigitCenter AnalogDigitCenter;

//----------InitDigitalTimerDisplay-----------
//Initializes screen for digital timer. Time starts at 1:00
//Input: none
//Output: none
void InitAnalogTimerDisplay(void);

void AnalogDisplayMinute(void);

void AnalogDisplayHour(void);

void AnalogTimerDisplay(SwitchStates state);