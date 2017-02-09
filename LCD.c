// filename ******** LCD.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "LCD.h"
#include <stdint.h>
#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"

int16_t yellow;

void DisplayHour(){
	//display hour on lcd
	char h = (char)GetHour() + '0';
	ST7735_DrawChar(18, 0, h, yellow, 0, 5);
}

void DisplayMinute(){
	//display minute on lcd
	char m = (char)GetMinute() + 48;
	ST7735_DrawChar(81, 0, m, yellow, 0, 5);
}

void initDigitalTimerDisplay(void){
	yellow = ST7735_Color565(0xf4, 0xff, 0x87);
	ST7735_FillScreen(ST7735_BLACK); 
  ST7735_SetCursor(0,0);
	//ST7735_OutString("hi");
	ST7735_DrawChar(38, 0, ':', yellow, ST7735_BLACK, 5);
	ST7735_DrawChar(18, 0, '0', yellow, ST7735_BLACK, 5);
	ST7735_DrawChar(53, 0, '0', yellow, ST7735_BLACK, 5);
	ST7735_DrawChar(81, 0, '0', yellow, ST7735_BLACK, 5);
}

