// filename ******** DigitalDisplay.c ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

// TODO: DecreaseCurrent, AM/PM functionality, testing, going from main to this screen, going from this screen to main,
// making sure set time can be displayed and also *UNINTERRUPTED* -- create bool for settime so display hour and minute 
// not called in this case

#include "LCD.h"
#include "Timer.h"
#include "DigitalDisplay.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"

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
								AMPM = 4} SetState;		

TimeSet timeSetting[4] = {{5,1,'0',ST7735_WHITE,ST7735_BLACK,5},{33,1,'1',ST7735_WHITE,ST7735_BLACK,5},
		{69,1,'0',ST7735_WHITE,ST7735_BLACK,5},{97,1,'0',ST7735_WHITE,ST7735_BLACK,5}};
		// index 0 is hour tens, 1 is hour ones, 2 is minute tens, 3 is minute ones

TimeSet tensPlaceM;
TimeSet onesPlaceM;
TimeSet tensPlaceH;
TimeSet onesPlaceH;
		
SetState currentlySetting = tensH;

void DigitalDisplayInit() {
	tensPlaceH = timeSetting[0];
	onesPlaceH = timeSetting[1];
	tensPlaceM = timeSetting[2];
	onesPlaceM = timeSetting[3];
}	
		
void DigitalTimerDisplay(SwitchStates state){
	switch(state) {
		case None:
			ST7735_FillScreen(ST7735_BLACK); 
			ST7735_SetCursor(0,0);
			ST7735_DrawChar(53, 0, ':', ST7735_WHITE, ST7735_BLACK, 5);
			for(int i = 0; i < 4; i++) { // iterate through timeSettings
				TimeSet current = timeSetting[i];
				ST7735_DrawChar(current.x, current.y, current.num, current.fontColor, current.backColor, current.size);
			}
			break;
		case Select:
			UpdateSet();
			break;
		case Up:
			break;
		case Down:
			break;
	}
}

void DisplayHour(){
	//display hour on lcd
	char h = (char)GetHour();
	if(h == 10){
		//tensPlaceH = 1;
		tensPlaceH.num = '1';
		DrawTensPlaceH();
	}
	else if(h == 1){
		tensPlaceH.num = '0';
		DrawTensPlaceH();
	}
	h = h%10;
	onesPlaceH.num = h + '0';
	DrawOnesPlaceH();
}

void DisplayMinute(){
	//display minute on lcd
	uint32_t m = GetMinute();
	
	if(m % 10 == 0){ // minutes is multiple of 10
		onesPlaceM.num = '0';
		tensPlaceM.num = m/10 + '0';
		if(m == 0){
			tensPlaceM.num = '0';
			DrawTensPlaceM();
			DrawOnesPlaceM();
		}
		else{
			DrawTensPlaceM();			
			DrawOnesPlaceM();
			//ST7735_DrawChar(69, 0, tensPlaceM + '0', ST7735_WHITE, 0, 5);
		}
	}
	else{
		m = m%10;
		onesPlaceM.num = m + '0';
		DrawOnesPlaceM();
	}
	
}

void UpdateSet() {
	timeSetting[currentlySetting].fontColor = ST7735_WHITE;
	currentlySetting++;
	if(currentlySetting == 4) {
		// do something for AM/PM
	} else if(currentlySetting > 4 ) {
		// done setting time, return to main
	} else { 	// change color for next thing to set
		timeSetting[currentlySetting].fontColor = ST7735_YELLOW;
	}
}

void IncreaseCurrent() {
	char currentVal = timeSetting[currentlySetting].num;
	currentVal = currentVal - '0';
	switch(currentlySetting) {
		case tensH:
			if(currentVal == 1) {
				currentVal = 0 + '0';
			}
			DrawTensPlaceH();
			break;
		case onesH:
			if(currentVal == 9) {
				currentVal = 0 + '0';
			}
			DrawOnesPlaceH();
			break;
		case tensM:
			if(currentVal == 5) {
				currentVal = 0 + '0';
			}
			DrawTensPlaceM();
			break;
		case onesM:
			if(currentVal == 9) {
				currentVal = 0 + '0';
			}
			DrawOnesPlaceM();
			break;
		case AMPM:
			break;
	}
}

void DrawTensPlaceH() {
	ST7735_DrawChar(tensPlaceH.x, tensPlaceH.y, tensPlaceH.num, tensPlaceH.fontColor, tensPlaceH.backColor, 
			tensPlaceH.size);
}

void DrawOnesPlaceH() {
	ST7735_DrawChar(onesPlaceH.x, onesPlaceH.y, onesPlaceH.num, onesPlaceH.fontColor, onesPlaceH.backColor,
			onesPlaceH.size);
}

void DrawTensPlaceM() {
	ST7735_DrawChar(tensPlaceM.x, tensPlaceM.y, tensPlaceM.num, tensPlaceM.fontColor, tensPlaceM.backColor,
			tensPlaceM.size);
}

void DrawOnesPlaceM() {
	ST7735_DrawChar(onesPlaceM.x, onesPlaceM.y, onesPlaceM.num, onesPlaceM.fontColor, onesPlaceM.backColor,
			onesPlaceM.size);
}