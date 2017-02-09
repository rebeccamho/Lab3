// filename ******** LCD.c ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include "LCD.h"
#include <stdint.h>
#include "Timer.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.h"

int16_t yellow;
uint32_t tensPlaceM;
uint32_t tensPlaceH;

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

void initDigitalTimerDisplay(void){
	yellow = ST7735_Color565(0xf4, 0xff, 0x87);
	tensPlaceM = 0;
	tensPlaceH = 0;
	ST7735_FillScreen(ST7735_BLACK); 
  ST7735_SetCursor(0,0);
	//ST7735_OutString("hi");
	ST7735_DrawChar(53, 0, ':', yellow, ST7735_BLACK, 5);
	ST7735_DrawChar(5, 0, '0', yellow, ST7735_BLACK, 5);//tens place hour
	ST7735_DrawChar(33, 0, '1', yellow, ST7735_BLACK, 5);//ones place hour
	ST7735_DrawChar(69, 0, '0', yellow, ST7735_BLACK, 5);//tens place minute
	ST7735_DrawChar(97, 0, '0', yellow, ST7735_BLACK, 5);//ones place minute
}

