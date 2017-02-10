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

