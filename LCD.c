// filename ******** LCD.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "LCD.h"
#include <stdint.h>
#include <stdbool.h>
#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"

struct MenuOptions {
	char* msg;
	int16_t color;
	uint16_t y;
};
typedef struct MenuOptions MenuOptions;

typedef enum  { MainMenu,
								Digital,
								Analog,
								SetTime,
								SetAlarm} LCDstate;							

LCDstate currentState;
bool up = false;	// up switch state
bool down = false;	// down switch state
bool select = false;	// select switch state
								
MenuOptions mainMenuState[4] = {{"Analog Clock",ST7735_YELLOW,2},{"Digital Clock",ST7735_RED,3},
		{"Set Time",ST7735_RED,4},{"Set Alarm",ST7735_RED,5}};
uint16_t currentMenuIndex = 0; // which index in array main menu is highlighting

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

void DisplaySetTime(SwitchStates state) {
	switch(state) {
		case None:
			//InitDigitalTimerDisplay();
			break;
		case Select:
			break;
		case Up:
			break;
		case Down:
			break;
	}

}

void CheckSwitches() {
	if(select) {
		ResetSwitches();
		
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
		case MainMenu:
			switch(currentMenuIndex) {
				case 0:		// analog clock
					break;
				case 1:		// digital clock
					break;
				case 2:		// set time
					break;
				case 3:		// set alarm
					break;
			}
			break;
		case Digital:
			break;
		case Analog:
			break;
		case SetTime:
			break;
		case SetAlarm:
			break;
	}
}

void DownFunction() {
	switch(currentState) {
		case MainMenu:
			DisplayMainMenu(currentMenuIndex+1);
			break;
		case Digital:
			break;
		case Analog:
			break;
		case SetTime:
			break;
		case SetAlarm:
			break;
	}
}

void UpFunction() {
	switch(currentState) {
		case MainMenu:
			DisplayMainMenu(currentMenuIndex-1);
			break;
		case Digital:
			break;
		case Analog:
			break;
		case SetTime:
			break;
		case SetAlarm:
			break;
	}
}

void SelectPressed() {
	select = true;
}

void DownPressed() {
	down = true;
}

void UpPressed() {
	up = true;
}

void ResetSwitches(){
	select = false;
	down = false;
	up = false;
}
