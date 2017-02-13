// filename ******** LCD.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "LCD.h"
#include <stdint.h>
#include <stdbool.h>
#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"
#include "../Lab1/fixed.h"
#include "DigitalDisplay.h"
#include "AnalogDisplay.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

struct MenuOptions {
	char* msg;
	int16_t color;
	uint16_t y;
};
typedef struct MenuOptions MenuOptions;


MenuOptions mainMenuState[4] = {{"Analog Clock",ST7735_YELLOW,2},{"Digital Clock",ST7735_RED,3},
		{"Set Time",ST7735_RED,4},{"Set Alarm",ST7735_RED,5}};
		// index 0 is analog, 1 is digital, 2 is settime, 3 is setalarm
		
bool up = false;	// up switch state
bool down = false;	// down switch state
bool select = false;	// select switch state
bool newMinute = false;
bool newHour = false;
LCDstate currentState;	
int16_t currentMenuIndex = 0; // which index in array main menu is highlighting

				
void DisplayMainMenu(int16_t n) {
	currentState = MainMenu;
	if(n > 3) { n = 0; } // n exceeds array indices
	if(n < 0) { n = 3; }
	mainMenuState[currentMenuIndex].color = ST7735_RED; // reset color of currently highlighted option
	currentMenuIndex = n;
	mainMenuState[currentMenuIndex].color = ST7735_YELLOW; // highlight newly selected option
	
	ST7735_FillScreen(ST7735_BLACK); 
  ST7735_SetCursor(0,0);
	ST7735_DrawString(1, 0, "Main Menu", ST7735_RED);
	for(int i = 0; i < 4; i++) {
		MenuOptions current = mainMenuState[i];
		ST7735_DrawString(1, current.y, current.msg, current.color);
	}	
}


void CheckFlags() {
	long sr = StartCritical();
	if(newMinute && GetCurrentState() != SetTime){
		switch(GetCurrentState()){
			case Digital:
				DisplayMinute();
				break;
			case Analog:
				DigitalUpdateMinute();
				AnalogDisplayMinute();
				AnalogDisplayHour();
				break;
			case MainMenu:
				DigitalUpdateMinute();
				break;
			default:
				break;
		}
	}
		
	if(newHour && GetCurrentState() != SetTime){
		switch(GetCurrentState()){
			case Digital:
				DisplayHour();
				break;
			case Analog:
				DigitalUpdateHour();
				AnalogDisplayHour();
				break;
			case MainMenu:
				DigitalUpdateHour();
				break;
			default:
				break;
		}
	}
		
	if(newMinute | newHour) {
		CheckAlarms();
	}
	
	newMinute = false;
	newHour = false;
	
	EndCritical(sr);
	
	if(GetAlarmOn() && (select | down | up)) { // if alarm is on and any switch is pressed, turn off alarm
		TurnAlarmOff();
		ResetSwitches();
		return;
	}
	if(select) {
		ResetSwitches();
		SelectFunction();
		
	} else if(down) {
		ResetSwitches();
		DownFunction();
		
	} else if(up) {
		ResetSwitches();
		UpFunction();
	}
}

void SelectFunction() {
	switch(currentState) {
		case MainMenu:		// in main menu
			switch(currentMenuIndex) {
				case 0:		// analog clock
					currentState = Analog;
					AnalogTimerDisplay(None);
					break;
				case 1:		// digital clock
					currentState = Digital;
					DigitalTimerDisplay(None);
					break;
				case 2:		// set time
					currentState = SetTime;
					DigitalTimerDisplay(SetInit);
					break;
				case 3:		// set alarm
					currentState = SetAlarm;
					DigitalTimerDisplay(AlarmInit);
					break;
			}
			break;
		case Digital:
			DigitalTimerDisplay(Select);
			break;
		case Analog:
			AnalogTimerDisplay(Select);
			break;
		case SetTime:		// in SetTime
			UpdateSet();
			break;
		case SetAlarm:
			AlarmUpdateSet();
			break;
	}
}

void DownFunction() {
	switch(currentState) {
		case MainMenu:
			DisplayMainMenu(currentMenuIndex+1);
			break;
		case Digital:
			DigitalTimerDisplay(Down);
			break;
		case Analog:
			break;
		case SetTime:		// in SetTime
			DecreaseCurrent();
			break;
		case SetAlarm:
			AlarmDecreaseCurrent();
			break;
	}
}

void UpFunction() {
	switch(currentState) {
		case MainMenu:
			DisplayMainMenu(currentMenuIndex-1);
			break;
		case Digital:
			DigitalTimerDisplay(Up);
			break;
		case Analog:
			break;
		case SetTime:
			IncreaseCurrent();
			break;
		case SetAlarm:
			AlarmIncreaseCurrent();
			break;
	}
}

void UpPressed() {
	up = true;
}

void ResetSwitches(){
	select = false;
	down = false;
	up = false;
}

void SelectPressed() {
	select = true;
}

void DownPressed() {
	down = true;
}

LCDstate GetCurrentState() {
	return currentState;
}

void UpdateMinute() {
	newMinute = true;
}

void UpdateHour() {
	newHour = true;
}
