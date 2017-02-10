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
								SetAlarm } LCDstate;

int16_t yellow;
uint32_t tensPlaceM;
uint32_t tensPlaceH;
LCDstate currentState;
bool up = false;	// up switch state
bool down = false;	// down switch state
bool select = false;	// select switch state
MenuOptions mainMenuState[4] = {{"Analog Clock",ST7735_YELLOW,2},{"Digital Clock",ST7735_RED,3},
		{"Set Time",ST7735_RED,4},{"Set Alarm",ST7735_RED,5}};
uint16_t currentMenuIndex = 0; // which index in array main menu is highlighting

void DisplayHour(){
	//display hour on lcd
	char h = (char)GetHour();
	if(h == 10){
		tensPlaceH = 1;
		ST7735_DrawChar(5, 0, '1', yellow, 0, 5);
	}
	else if(h == 1){
		tensPlaceH = 0;
		ST7735_DrawChar(5, 0, '0', yellow, 0, 5);
	}
	h = h%10;
	ST7735_DrawChar(33, 0, h + '0', yellow, 0, 5);
}

void DisplayMinute(){
	//display minute on lcd
	char m = (char)GetMinute();
	
	if(m % 10 == 0){
		tensPlaceM++;
		if(m == 0){
			tensPlaceM = 0;
			ST7735_DrawChar(69, 0, '0', yellow, 0, 5);
			ST7735_DrawChar(97, 0, '0', yellow, 0, 5);
		}
		else{
			ST7735_DrawChar(69, 0, tensPlaceM + '0', yellow, 0, 5);
			ST7735_DrawChar(97, 0, '0', yellow, 0, 5);
		}
	}
	else{
		m = m%10;
		ST7735_DrawChar(97, 0, m + '0', yellow, 0, 5);
	}
	
}

void InitDigitalTimerDisplay(void){
	yellow = ST7735_Color565(0xf4, 0xff, 0x87);
	tensPlaceM = 0;
	tensPlaceH = 0;
	ST7735_FillScreen(ST7735_BLACK); 
  ST7735_SetCursor(0,0);
	ST7735_DrawChar(53, 0, ':', yellow, ST7735_BLACK, 5);
	ST7735_DrawChar(5, 0, '0', yellow, ST7735_BLACK, 5);//tens place hour
	ST7735_DrawChar(33, 0, '1', yellow, ST7735_BLACK, 5);//ones place hour
	ST7735_DrawChar(69, 0, '0', yellow, ST7735_BLACK, 5);//tens place minute
	ST7735_DrawChar(97, 0, '0', yellow, ST7735_BLACK, 5);//ones place minute
}

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
