// filename ******** DigitalDisplay.c ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "LCD.h"
#include "Timer.h"
#include "DigitalDisplay.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"

// TODO turn military off when return to main menu, change color of back/military according to currentSelect

struct TimeSet {
	int16_t x;
	int16_t y;
	char num;
	int16_t fontColor;
	int16_t backColor;
	uint8_t size;
};
typedef struct TimeSet TimeSet;

typedef enum  { Military,
								Back} digitalState;	

TimeSet timeSetting[4] = {{5,1,'0',ST7735_WHITE,ST7735_BLACK,5},{33,1,'1',ST7735_WHITE,ST7735_BLACK,5},
		{69,1,'0',ST7735_WHITE,ST7735_BLACK,5},{97,1,'0',ST7735_WHITE,ST7735_BLACK,5}};
		// index 0 is hour tens, 1 is hour ones, 2 is minute tens, 3 is minute ones

SetState currentlySetting = tensH;
digitalState currentSelect = Military;
bool AM = true; // true if AM, false if PM
bool	military = false;

		
void DigitalTimerDisplay(SwitchStates state){
	switch(state) {
		case None:
			Draw12hrTime();
			ST7735_DrawString(1, 14, "Military ON", ST7735_YELLOW);
			ST7735_DrawString(1, 15, "Back", ST7735_RED);		
			currentSelect = Military;
			military = false;
			break;
		case Select:
			switch(currentSelect) {
				case Military:
					if(military) { // currently in military time
						Draw12hrTime();
						military = false;
						ST7735_DrawString(1, 14, "Military ON", ST7735_YELLOW);
					} else {
						DrawMilitaryTime();
						military = true;
						ST7735_DrawString(1, 14, "Military OFF", ST7735_YELLOW);
					}
					ST7735_DrawString(1, 15, "Back", ST7735_RED);	
					break;
				case Back:
					military = false;
					DisplayMainMenu(1);
					break;
			}
			break;
		case Up:	
			if(currentSelect == Military) {
				if(military) { ST7735_DrawString(1, 14, "Military OFF", ST7735_RED); } 
				else { ST7735_DrawString(1, 14, "Military ON", ST7735_RED); }
				ST7735_DrawString(1, 15, "Back", ST7735_YELLOW);	
				currentSelect = Back;
			} else {
				if(military) { ST7735_DrawString(1, 14, "Military OFF", ST7735_YELLOW); } 
				else { ST7735_DrawString(1, 14, "Military ON", ST7735_YELLOW); }
				ST7735_DrawString(1, 15, "Back", ST7735_RED);	
				currentSelect = Military;
			}
			break;
		case Down:
			if(currentSelect == Military) {
				if(military) { ST7735_DrawString(1, 14, "Military OFF", ST7735_RED); } 
				else { ST7735_DrawString(1, 14, "Military ON", ST7735_RED); }
				ST7735_DrawString(1, 15, "Back", ST7735_YELLOW);	
				currentSelect = Back;
			} else {
				if(military) { ST7735_DrawString(1, 14, "Military OFF", ST7735_YELLOW); } 
				else { ST7735_DrawString(1, 14, "Military ON", ST7735_YELLOW); }
				ST7735_DrawString(1, 15, "Back", ST7735_RED);	
				currentSelect = Military;
			}
			break;
		case SetInit:
			ST7735_FillScreen(ST7735_BLACK); 
			ST7735_SetCursor(0,0);
			ST7735_DrawChar(53, 0, ':', ST7735_WHITE, ST7735_BLACK, 5);
			timeSetting[0].fontColor = ST7735_YELLOW;
			for(int i = 0; i < 4; i++) { // iterate through timeSettings
				TimeSet current = timeSetting[i];
				ST7735_DrawChar(current.x, current.y, current.num, current.fontColor, current.backColor, current.size);
			}			
			if(AM) { DrawAM(ST7735_WHITE); }
			else { DrawPM(ST7735_WHITE); }
			break;
	}
}

void DisplayHour(){
	//display hour on lcd
	uint32_t h = GetHour();
	if(h == 10){
		timeSetting[tensH].num = '1';
		if(GetCurrentState() == Digital && !military){
			DrawDigit(tensH);
		}
	}
	else if(h == 1){
		if(AM) {
			AM = false;
			if(!military) { DrawPM(ST7735_WHITE); }
		} else {
			AM = true;
			if(!military) { DrawAM(ST7735_WHITE); }
		}
		timeSetting[tensH].num = '0';
		if(GetCurrentState() == Digital && !military) {
			DrawDigit(tensH);
		}
	}
	h = h%10;
	timeSetting[onesH].num = h + '0';
	if(GetCurrentState() == Digital && !military) {
		DrawDigit(onesH);
	}
	if(military) {
		DrawMilitaryTime();
		if(currentSelect == Military) {
			ST7735_DrawString(1, 14, "Military OFF", ST7735_YELLOW);
			ST7735_DrawString(1, 15, "Back", ST7735_RED);	
		} else {
			ST7735_DrawString(1, 14, "Military OFF", ST7735_RED);
			ST7735_DrawString(1, 15, "Back", ST7735_YELLOW);			
		}
	}
}

void DisplayMinute(){
	//display minute on lcd
	uint32_t m = GetMinute();
	
	if(m % 10 == 0){ // minutes is multiple of 10
		timeSetting[onesM].num = '0';
		timeSetting[tensM].num = m/10 + '0';
		if(m == 0){
			timeSetting[tensM].num = '0';
			if(GetCurrentState() == Digital) {
				DrawDigit(tensM);
				DrawDigit(onesM);
			}
		}
		else if(GetCurrentState() == Digital){
			DrawDigit(tensM);
			DrawDigit(onesM);
		}
	}
	else{
		m = m%10;
		timeSetting[onesM].num = m + '0';
		if(GetCurrentState() == Digital) {
			DrawDigit(onesM);
		}
	}
	
}

void UpdateSet() {
	timeSetting[currentlySetting].fontColor = ST7735_WHITE;
	DrawDigit(currentlySetting);
	currentlySetting++;
	if(currentlySetting == 4) {
		if(AM) { DrawAM(ST7735_YELLOW); }
		else { DrawPM(ST7735_YELLOW); }
	} else if(currentlySetting > 4 ) { // done setting time, set timer settings and return to main
		currentlySetting = tensH;
		uint32_t hour = (timeSetting[tensH].num - '0')*10 + (timeSetting[onesH].num - '0');
		uint32_t minute = (timeSetting[tensM].num - '0')*10 + (timeSetting[onesM].num - '0');
		SetHour(hour);
		SetMinute(minute);
		SetSecond(0);		
		DisplayMainMenu(2);
	} else { 	// change color for next thing to set
		timeSetting[currentlySetting].fontColor = ST7735_YELLOW;
		DrawDigit(currentlySetting);	
	}
}

void IncreaseCurrent() {
	char currentVal = timeSetting[currentlySetting].num;
	currentVal = currentVal - '0';
	switch(currentlySetting) {
		case tensH:
			if(currentVal == 1) {
				currentVal = 0 + '0';
			} else {
				currentVal = currentVal + 1 + '0';
			}
			
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(tensH);
			break;
		case onesH:
			if(timeSetting[tensH].num == '1') { // don't want to exceed 12
				if(currentVal == 2) {	
					currentVal = 0 + '0';
				} else {
					currentVal = currentVal + 1 + '0';
				}
			} else if(currentVal == 9) { 
				currentVal = 0 + '0';
			} else {
				currentVal = currentVal + 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(onesH);
			break;
		case tensM:
			if(currentVal == 5) {
				currentVal = 0 + '0';
			} else {
				currentVal = currentVal + 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(tensM);
			break;
		case onesM:
			if(currentVal == 9) {
				currentVal = 0 + '0';
			} else {
				currentVal = currentVal + 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(onesM);
			break;
		case AMPM:
			if(AM) { 
				DrawPM(ST7735_YELLOW); 
				AM = false;
			}
			else { 
				DrawAM(ST7735_YELLOW);
				AM = true;
			}
			break;
	}
}

void DecreaseCurrent() {
	char currentVal = timeSetting[currentlySetting].num;
	currentVal = currentVal - '0';
	switch(currentlySetting) {
		case tensH:
			if(currentVal == 0) {
				currentVal = 1 + '0';
			} else {
				currentVal = currentVal - 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(tensM);
			break;
		case onesH:
			if(timeSetting[tensH].num == '1') { // don't want to exceed 12
				if(currentVal == 0) {	
					currentVal = 2 + '0';
				} else {
					currentVal = currentVal - 1 + '0';
				}
			} else if(currentVal == 0) { 
				currentVal = 9 + '0';
			} else {
				currentVal = currentVal - 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(onesH);
			break;
		case tensM:
			if(currentVal == 0) {
				currentVal = 5 + '0';
			} else {
				currentVal = currentVal - 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(tensM);
			break;
		case onesM:
			if(currentVal == 0) {
				currentVal = 9 + '0';
			} else {
				currentVal = currentVal - 1 + '0';
			}
			timeSetting[currentlySetting].num = currentVal;
			DrawDigit(onesM);
			break;
		case AMPM:
			if(AM) { 
				DrawPM(ST7735_YELLOW); 
				AM = false;
			}
			else { 
				DrawAM(ST7735_YELLOW);
				AM = true;
			}
			break;
	}
}


void DrawDigit(SetState s) {
	if(s > 3) { return; } // exceeds timeSetting array
	ST7735_DrawChar(timeSetting[s].x, timeSetting[s].y, timeSetting[s].num, timeSetting[s].fontColor, 
			timeSetting[s].backColor, timeSetting[s].size);
}

void DrawAM(int16_t color) {
	ST7735_DrawChar(75, 50, 'A', color, ST7735_BLACK, 4);
	ST7735_DrawChar(100, 50, 'M', color, ST7735_BLACK, 4);
}

void DrawPM(int16_t color) {
	ST7735_DrawChar(75, 50, 'P', color, ST7735_BLACK, 4);
	ST7735_DrawChar(100, 50, 'M', color, ST7735_BLACK, 4);
}

void Draw12hrTime() {
	ST7735_FillScreen(ST7735_BLACK); 
	ST7735_SetCursor(0,0);
	ST7735_DrawChar(53, 0, ':', ST7735_WHITE, ST7735_BLACK, 5);
	for(int i = 0; i < 4; i++) { // iterate through timeSettings
		TimeSet current = timeSetting[i];
		ST7735_DrawChar(current.x, current.y, current.num, current.fontColor, current.backColor, current.size);
	}
	if(AM) { DrawAM(ST7735_WHITE); }
	else { DrawPM(ST7735_WHITE); }
}

void DrawMilitaryTime() {
	ST7735_FillScreen(ST7735_BLACK); 
	ST7735_SetCursor(0,0);
	ST7735_DrawChar(53, 0, ':', ST7735_WHITE, ST7735_BLACK, 5);
	uint32_t hour = (timeSetting[tensH].num - '0')*10 + (timeSetting[onesH].num - '0');
	
	if(!AM) { // time of day is PM
		hour = hour + 11;
	} else {
		hour = hour - 1;
	}
		uint32_t hourTens = hour/10;
		uint32_t hourOnes = hour%10;

		ST7735_DrawChar(timeSetting[tensH].x, timeSetting[tensH].y, hourTens + '0', 
				timeSetting[tensH].fontColor, timeSetting[tensH].backColor, timeSetting[tensH].size);
		ST7735_DrawChar(timeSetting[onesH].x, timeSetting[onesH].y, hourOnes + '0', 
				timeSetting[onesH].fontColor, timeSetting[onesH].backColor, timeSetting[onesH].size);		
		for(int i = 2; i < 4; i++) { // draw minutes
			TimeSet current = timeSetting[i];
			ST7735_DrawChar(current.x, current.y, current.num, current.fontColor, current.backColor, current.size);
		}
}
