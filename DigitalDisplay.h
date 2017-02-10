// filename ******** DigitalDisplay.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdbool.h>

//----------DigitalDisplayInit-----------
//Initializes variables used in DigitalDisplay
//Input: none
//Output: none
void DigitalDisplayInit(void);

//----------DigitalTimerDisplay-----------
//Initializes screen for digital timer. Time starts at 1:00
//Input: true if setting the time, false if only displaying the time
//Output: none
void DigitalTimerDisplay(SwitchStates);

//----------UpdateSet-----------
//Changes what part of the time you're setting to the next variable
//Input: none
//Output: none
void UpdateSet(void);

//----------IncreaseCurrent-----------
//Increases current variable that you're changing by 1. Displays variable
//Input: none
//Output: none
void IncreaseCurrent(void);

//----------DrawTensPlaceH-----------
//Draw tens place of hour
//Input: none
//Output: none
void DrawTensPlaceH(void);

//----------DrawOnesPlaceH-----------
//Draw ones place of hour
//Input: none
//Output: none
void DrawOnesPlaceH(void);

//----------DrawTensPlaceM-----------
//Draw tens place of minute
//Input: none
//Output: none
void DrawTensPlaceM(void);

//----------DrawOnesPlaceM-----------
//Draw ones place of minute
//Input: none
//Output: none
void DrawOnesPlaceM(void);

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

