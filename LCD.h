// filename ******** LCD.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>


//----------DisplayHour-------------
//Displays digital hour of day. Used whenever switching to digital clock display,
//or whenever hour changes when digital timer is already displayed
//Input: none
//Output: Display hour of the day in digital timer
void DisplayHour(void);

//----------DisplayMinute-----------
//Displays digital minute of day. Used whenever switching to digital clock display,
//or whenever minute changes when digital timer is already displayed
//Input: none
//Output: Display minute of the hour in digital timer
void DisplayMinute(void);


void initDigitalTimerDisplay(void);
