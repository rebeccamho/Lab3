// filename ******** DigitalDisplay.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdbool.h>
#include "LCD.h"

struct TimeSet {
	int16_t x;
	int16_t y;
	char num;
	int16_t fontColor;
	int16_t backColor;
	uint8_t size;
};
typedef struct TimeSet TimeSet;

typedef enum  { tensH = 0,
								onesH = 1,
								tensM = 2,
								onesM = 3,
								AMPM = 4,
								AlarmPitch = 5} SetState;		

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
//void UpdateSet(void);
void UpdateSet(void);

//----------AlarmUpdateSet-----------
//Changes what part of the alarm you're setting to the next variable
//Input: none
//Output: none
//void UpdateSet(void);
void AlarmUpdateSet(void);								
								
//----------IncreaseCurrent-----------
//Increases current variable that you're changing by 1. Displays variable
//Input: none
//Output: none
void IncreaseCurrent(void);

//----------AlarmIncreaseCurrent-----------
//Increases current alarm variable that you're changing by 1. Displays variable
//Input: none
//Output: none
void AlarmIncreaseCurrent(void);

//----------DecreaseCurrent-----------
//Decreases current variable that you're changing by 1. Displays variable
//Input: none
//Output: none
void DecreaseCurrent(void);

//----------AlarmDecreaseCurrent-----------
//Decreases current alarm variable that you're changing by 1. Displays variable
//Input: none
//Output: none
void AlarmDecreaseCurrent(void);

//----------DrawTensPlaceH-----------
//Draw tens place of hour
//Input: none
//Output: none
void DrawDigit(SetState);

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

//----------DrawAM-----------
//Draws AM below time
//Input: none
//Output: none
void DrawAM(int16_t);

//----------DrawPM-----------
//Draws PM below time
//Input: none
//Output: none
void DrawPM(int16_t);

//----------Draw12hrTime-----------
//Draws current time in 12 hr format
//Input: none
//Output: none
void Draw12hrTime(void);

//----------DrawMilitaryTime-----------
//Draws current time in military format
//Input: none
//Output: none
void DrawMilitaryTime(void);

//----------ResetAlarmValues-----------
//Resets all alarm settings to 0 to make setting next alarm easier
//Input: none
//Output: none
void ResetAlarmValues(void);

//----------GetAM-----------
//Returns time of day (AM/PM)
//Input: none
//Output: true if AM, false if PM
bool GetAM(void);

//----------DigitalUpdateHour-----------
//Updates hour stored in DigitalDisplay if not setting time or alarm
//Input: none
//Output: none
void DigitalUpdateHour(void);

//----------DigitalUpdateMinute-----------
//Updates minute stored in DigitalDisplay if not setting time or alarm
//Input: none
//Output: none
void DigitalUpdateMinute(void);


