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


// 180 points on a circle of radius 2.000
const int32_t CircleXbuf[180] = { 2000, 1999, 1995, 1989, 1981, 1970, 1956, 1941, 1923, 1902, 1879, 1854, 1827, 1798, 1766, 1732, 1696, 1658, 1618, 1576, 1532, 1486, 1439, 1389, 1338, 1286, 1231, 1176, 1118, 1060, 1000, 939, 877, 813, 749, 684, 618, 551, 484, 416, 347, 278, 209, 140, 70, 0, -70, -140, -209, -278, -347, -416, -484, -551, -618, -684, -749, -813, -877, -939, -1000, -1060, -1118, -1176, -1231, -1286, -1338, -1389, -1439, -1486, -1532, -1576, -1618, -1658, -1696, -1732, -1766, -1798, -1827, -1854, -1879, -1902, -1923, -1941, -1956, -1970, -1981, -1989, -1995, -1999, -2000, -1999, -1995, -1989, -1981, -1970, -1956, -1941, -1923, -1902, -1879, -1854, -1827, -1798, -1766, -1732, -1696, -1658, -1618, -1576, -1532, -1486, -1439, -1389, -1338, -1286, -1231, -1176, -1118, -1060, -1000, -939, -877, -813, -749, -684, -618, -551, -484, -416, -347, -278, -209, -140, -70, 0, 70, 140, 209, 278, 347, 416, 484, 551, 618, 684, 749, 813, 877, 939, 1000, 1060, 1118, 1176, 1231, 1286, 1338, 1389, 1439, 1486, 1532, 1576, 1618, 1658, 1696, 1732, 1766, 1798, 1827, 1854, 1879, 1902, 1923, 1941, 1956, 1970, 1981, 1989, 1995, 1999
};
const int32_t CircleYbuf[180] = {0, 70, 140, 209, 278, 347, 416, 484, 551, 618, 684, 749, 813, 877, 939, 1000, 1060, 1118, 1176, 1231, 1286, 1338, 1389, 1439, 1486, 1532, 1576, 1618, 1658, 1696, 1732, 1766, 1798, 1827, 1854, 1879, 1902, 1923, 1941, 1956, 1970, 1981, 1989, 1995, 1999, 2000, 1999, 1995, 1989, 1981, 1970, 1956, 1941, 1923, 1902, 1879, 1854, 1827, 1798, 1766, 1732, 1696, 1658, 1618, 1576, 1532, 1486, 1439, 1389, 1338, 1286, 1231, 1176, 1118, 1060, 1000, 939, 877, 813, 749, 684, 618, 551, 484, 416, 347, 278, 209, 140, 70, 0, -70, -140, -209, -278, -347, -416, -484, -551, -618, -684, -749, -813, -877, -939, -1000, -1060, -1118, -1176, -1231, -1286, -1338, -1389, -1439, -1486, -1532, -1576, -1618, -1658, -1696, -1732, -1766, -1798, -1827, -1854, -1879, -1902, -1923, -1941, -1956, -1970, -1981, -1989, -1995, -1999, -2000, -1999, -1995, -1989, -1981, -1970, -1956, -1941, -1923, -1902, -1879, -1854, -1827, -1798, -1766, -1732, -1696, -1658, -1618, -1576, -1532, -1486, -1439, -1389, -1338, -1286, -1231, -1176, -1118, -1060, -1000, -939, -877, -813, -749, -684, -618, -551, -484, -416, -347, -278, -209, -140, -70
};

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


void CheckSwitches() {
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
					break;
			}
			break;
		case Digital:
			DigitalTimerDisplay(Select);
			break;
		case Analog:
			break;
		case SetTime:		// in SetTime
			UpdateSet();
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
			DigitalTimerDisplay(Down);
			break;
		case Analog:
			break;
		case SetTime:		// in SetTime
			DecreaseCurrent();
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
			DigitalTimerDisplay(Up);
			break;
		case Analog:
			break;
		case SetTime:
			IncreaseCurrent();
			break;
		case SetAlarm:
			break;
	}
}

void InitAnalogTimerDisplay(void){
	ST7735_SetCursor(0,0);
  ST7735_XYplotInit("",-2500, 2500, -2500, 2500);
  ST7735_XYplot(180,(int32_t *)CircleXbuf,(int32_t *)CircleYbuf);
	//12
	ST7735_DrawChar(53, 50, '1', ST7735_WHITE, ST7735_BLACK, 2);
	ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2);
	//1
	ST7735_DrawChar(81, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
	//2
	ST7735_DrawChar(95, 72, '2', ST7735_WHITE, ST7735_BLACK, 1);
	//3
	ST7735_DrawChar(100, 89, '3', ST7735_WHITE, ST7735_BLACK, 2);
	//4
	ST7735_DrawChar(95, 110, '4', ST7735_WHITE, ST7735_BLACK, 1);
	//5
	ST7735_DrawChar(81, 123, '5', ST7735_WHITE, ST7735_BLACK, 1);
	//6
	ST7735_DrawChar(58, 128, '6', ST7735_WHITE, ST7735_BLACK, 2);
	//7
	ST7735_DrawChar(41, 123, '7', ST7735_WHITE, ST7735_BLACK, 1);
	//8
	ST7735_DrawChar(28, 110, '8', ST7735_WHITE, ST7735_BLACK, 1);
	//9
	ST7735_DrawChar(18, 89, '9', ST7735_WHITE, ST7735_BLACK, 2);
	//10
	ST7735_DrawChar(23, 72, '1', ST7735_WHITE, ST7735_BLACK, 1);
	ST7735_DrawChar(29, 72, '0', ST7735_WHITE, ST7735_BLACK, 1);
	//11
	ST7735_DrawChar(36, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
	ST7735_DrawChar(42, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
	
//	//Grid
//	//V 9
//	ST7735_Line(23, 0, 23, 150, ST7735_WHITE);
//	//V 10-8
//	ST7735_Line(36, 0, 36, 150, ST7735_WHITE);
//	//V 11-7
//	ST7735_Line(49, 0, 49, 150, ST7735_WHITE);
//	//VMiddle
//	ST7735_Line(62, 0, 62, 150, ST7735_WHITE);
//	//V 1-5
//	ST7735_Line(76, 0, 76, 150, ST7735_WHITE);
//	//V 2-4
//	ST7735_Line(90, 0, 90, 150, ST7735_WHITE);
//	//V 3
//	ST7735_Line(105, 0, 105, 150, ST7735_WHITE);
//	
//	//H 12
//	ST7735_Line(0, 55, 120, 55, ST7735_WHITE);
//	//H 11-1
//	ST7735_Line(0, 68, 120, 68, ST7735_WHITE);
//	//H 10-2
//	ST7735_Line(0, 81, 120, 81, ST7735_WHITE);
//	//HMiddle
//	ST7735_Line(0, 94, 120, 94, ST7735_WHITE);
//	//H 8-4
//	ST7735_Line(0, 107, 120, 107, ST7735_WHITE);
//	//H 7-5
//	ST7735_Line(0, 120, 120, 120, ST7735_WHITE);
//	//H6
//	ST7735_Line(0, 133, 120, 133, ST7735_WHITE);
	
	
	
	
//	//Ticks
//	//1
//	ST7735_Line(85, 68, 93, 58, ST7735_WHITE);
//	//2
//	ST7735_Line(90, 68, 98, 58, ST7735_WHITE);
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
