// filename ******** AnalogDisplay.c ************** 
// Lab 1 Spring 2017
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

// 180 points on a circle of radius 2.000
const int32_t CircleXbuf[180] = { 2000, 1999, 1995, 1989, 1981, 1970, 1956, 1941, 1923, 1902, 1879, 1854, 1827, 1798, 1766, 1732, 1696, 1658, 1618, 1576, 1532, 1486, 1439, 1389, 1338, 1286, 1231, 1176, 1118, 1060, 1000, 939, 877, 813, 749, 684, 618, 551, 484, 416, 347, 278, 209, 140, 70, 0, -70, -140, -209, -278, -347, -416, -484, -551, -618, -684, -749, -813, -877, -939, -1000, -1060, -1118, -1176, -1231, -1286, -1338, -1389, -1439, -1486, -1532, -1576, -1618, -1658, -1696, -1732, -1766, -1798, -1827, -1854, -1879, -1902, -1923, -1941, -1956, -1970, -1981, -1989, -1995, -1999, -2000, -1999, -1995, -1989, -1981, -1970, -1956, -1941, -1923, -1902, -1879, -1854, -1827, -1798, -1766, -1732, -1696, -1658, -1618, -1576, -1532, -1486, -1439, -1389, -1338, -1286, -1231, -1176, -1118, -1060, -1000, -939, -877, -813, -749, -684, -618, -551, -484, -416, -347, -278, -209, -140, -70, 0, 70, 140, 209, 278, 347, 416, 484, 551, 618, 684, 749, 813, 877, 939, 1000, 1060, 1118, 1176, 1231, 1286, 1338, 1389, 1439, 1486, 1532, 1576, 1618, 1658, 1696, 1732, 1766, 1798, 1827, 1854, 1879, 1902, 1923, 1941, 1956, 1970, 1981, 1989, 1995, 1999
};
const int32_t CircleYbuf[180] = {0, 70, 140, 209, 278, 347, 416, 484, 551, 618, 684, 749, 813, 877, 939, 1000, 1060, 1118, 1176, 1231, 1286, 1338, 1389, 1439, 1486, 1532, 1576, 1618, 1658, 1696, 1732, 1766, 1798, 1827, 1854, 1879, 1902, 1923, 1941, 1956, 1970, 1981, 1989, 1995, 1999, 2000, 1999, 1995, 1989, 1981, 1970, 1956, 1941, 1923, 1902, 1879, 1854, 1827, 1798, 1766, 1732, 1696, 1658, 1618, 1576, 1532, 1486, 1439, 1389, 1338, 1286, 1231, 1176, 1118, 1060, 1000, 939, 877, 813, 749, 684, 618, 551, 484, 416, 347, 278, 209, 140, 70, 0, -70, -140, -209, -278, -347, -416, -484, -551, -618, -684, -749, -813, -877, -939, -1000, -1060, -1118, -1176, -1231, -1286, -1338, -1389, -1439, -1486, -1532, -1576, -1618, -1658, -1696, -1732, -1766, -1798, -1827, -1854, -1879, -1902, -1923, -1941, -1956, -1970, -1981, -1989, -1995, -1999, -2000, -1999, -1995, -1989, -1981, -1970, -1956, -1941, -1923, -1902, -1879, -1854, -1827, -1798, -1766, -1732, -1696, -1658, -1618, -1576, -1532, -1486, -1439, -1389, -1338, -1286, -1231, -1176, -1118, -1060, -1000, -939, -877, -813, -749, -684, -618, -551, -484, -416, -347, -278, -209, -140, -70
};

AnalogDigitCenter analogDigits[12] = {{63, 50}, {83,61}, {97,74}, {105,94}, {97,112}, {83,125}, {63,128}, {43,125}, {30,112}, {18,94}, {25,74}, {38,61}};

	
void DrawAnalogTimerDisplay(void){
	ST7735_FillScreen(ST7735_BLACK); 
	ST7735_SetCursor(0,0);
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
	
	long sr = StartCritical();
	AnalogDisplayMinute();
	AnalogDisplayHour();
	EndCritical(sr);
	ST7735_DrawString(1, 15, "Back", ST7735_YELLOW);
	
}

void AnalogTimerDisplay(SwitchStates state){
	switch(state){
		case Select:
			DisplayMainMenu(1);
			break;
		default:
			DrawAnalogTimerDisplay();
			break;
	}
}

void AnalogDisplayMinute(void){
	uint32_t m = GetMinute();
	if(m <= 5){
		switch(m){
			//0-5
			case 0: // redraw 12	
				ST7735_Line(63, 94, 58, 53, ST7735_BLACK);
				ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2); // redraw 2 of 12
				ST7735_Line(63, 94, 63, 50, ST7735_YELLOW);
				
				break;
			case 1:	
				ST7735_Line(63, 94, 63, 50, ST7735_BLACK);
				ST7735_DrawChar(53, 50, '1', ST7735_WHITE, ST7735_BLACK, 2); // redraw 1 of 12
				ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2); // redraw 2 of 12
				ST7735_Line(63, 94, 69, 54, ST7735_YELLOW);
				
				break;
			case 2:				
				ST7735_Line(63, 94, 69, 54, ST7735_BLACK);
				ST7735_DrawChar(53, 50, '1', ST7735_WHITE, ST7735_BLACK, 2); // redraw 1 of 12
				ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2); // redraw 2 of 12
				ST7735_Line(63, 94, 71, 55, ST7735_YELLOW);
				
				break;
			case 3:				
				ST7735_Line(63, 94, 71, 55, ST7735_BLACK);
				ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2); // redraw 2 of 12
				ST7735_Line(63, 94, 75, 57, ST7735_YELLOW);
				
				break;
			case 4:
				//ST7735_DrawChar(63, 50, '2', ST7735_WHITE, ST7735_BLACK, 2); // redraw 2 of 12
				ST7735_Line(63, 94, 75, 57, ST7735_BLACK);
				ST7735_Line(63, 94, 79, 59, ST7735_YELLOW);
				ST7735_DrawChar(81, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				break;
			case 5: // redraw 1				
				ST7735_Line(63, 94, 79, 59, ST7735_BLACK);
				ST7735_DrawChar(81, 59, '1', ST7735_WHITE, ST7735_BLACK, 1); // redraw 1
				ST7735_Line(63, 94, 83, 61, ST7735_YELLOW);
				
				break;
		}
	}
	else if(m <= 10){
		switch(m){
			case 6:				
				ST7735_Line(63, 94, 83, 61, ST7735_BLACK);
				ST7735_DrawChar(81, 59, '1', ST7735_WHITE, ST7735_BLACK, 1); // redraw 1
				ST7735_Line(63, 94, 85, 63, ST7735_YELLOW);
				
				break;
			case 7:
				ST7735_Line(63, 94, 85, 63, ST7735_BLACK);
				ST7735_DrawChar(81, 59, '1', ST7735_WHITE, ST7735_BLACK, 1); // redraw 1
				ST7735_Line(63, 94, 89, 66, ST7735_YELLOW);
				break;
			case 8:
				ST7735_Line(63, 94, 89, 66, ST7735_BLACK);
				ST7735_Line(63, 94, 91, 69, ST7735_YELLOW);
				break;
			case 9:
				ST7735_Line(63, 94, 91, 69, ST7735_BLACK);
				ST7735_Line(63, 94, 94, 71, ST7735_YELLOW);
				break;
			case 10:
				ST7735_Line(63, 94, 94, 71, ST7735_BLACK);
				ST7735_DrawChar(95, 72, '2', ST7735_WHITE, ST7735_BLACK, 1); // redraw 2
				ST7735_Line(63, 94, 97, 74, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 15){
		switch(m){
			case 11:
				ST7735_Line(63, 94, 97, 74, ST7735_BLACK);
				ST7735_DrawChar(95, 72, '2', ST7735_WHITE, ST7735_BLACK, 1); // redraw 2
				ST7735_Line(63, 94, 98, 78, ST7735_YELLOW);
				break;
			case 12:
				ST7735_Line(63, 94, 98, 78, ST7735_BLACK);
				ST7735_DrawChar(95, 72, '2', ST7735_WHITE, ST7735_BLACK, 1); // redraw 2
				ST7735_Line(63, 94, 100, 82, ST7735_YELLOW);
				break;
			case 13:
				ST7735_Line(63, 94, 100, 82, ST7735_BLACK);
				ST7735_Line(63, 94, 101, 86, ST7735_YELLOW);
				break;
			case 14:
				ST7735_Line(63, 94, 101, 86, ST7735_BLACK);
				ST7735_Line(63, 94, 103, 90, ST7735_YELLOW);
				break;
			case 15:
				ST7735_Line(63, 94, 103, 90, ST7735_BLACK);		
				ST7735_DrawChar(100, 89, '3', ST7735_WHITE, ST7735_BLACK, 2); // redraw 3
				ST7735_Line(63, 94, 105, 94, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 20){
		switch(m){
			case 16:
				ST7735_Line(63, 94, 105, 94, ST7735_BLACK);
				ST7735_DrawChar(100, 89, '3', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 104, 97, ST7735_YELLOW);
				break;
			case 17:
				ST7735_Line(63, 94, 104, 97, ST7735_BLACK);
				ST7735_DrawChar(100, 89, '3', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 103, 100, ST7735_YELLOW);
				break;
			case 18:
				ST7735_Line(63, 94, 103, 100, ST7735_BLACK);
				ST7735_Line(63, 94, 101, 104, ST7735_YELLOW);
				break;
			case 19:
				ST7735_Line(63, 94, 101, 104, ST7735_BLACK);
				ST7735_Line(63, 94, 99, 108, ST7735_YELLOW);
				break;
			case 20:
				ST7735_Line(63, 94, 99, 108, ST7735_BLACK);
				ST7735_DrawChar(95, 110, '4', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 97, 112, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 25){
		switch(m){
			case 21:
				ST7735_Line(63, 94, 97, 112, ST7735_BLACK);
				ST7735_DrawChar(95, 110, '4', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 95, 114, ST7735_YELLOW);
				break;
			case 22:
				ST7735_Line(63, 94, 95, 114, ST7735_BLACK);
				ST7735_DrawChar(95, 110, '4', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 92, 117, ST7735_YELLOW);
				break;
			case 23:
				ST7735_Line(63, 94, 92, 117, ST7735_BLACK);
				ST7735_Line(63, 94, 89, 120, ST7735_YELLOW);
				break;
			case 24:
				ST7735_Line(63, 94, 89, 120, ST7735_BLACK);
				ST7735_Line(63, 94, 86, 123, ST7735_YELLOW);
				break;
			case 25:
				ST7735_Line(63, 94, 86, 123, ST7735_BLACK);
				ST7735_DrawChar(81, 123, '5', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 83, 125, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 30){
		switch(m){
			case 26:
				ST7735_Line(63, 94, 83, 124, ST7735_BLACK);
				ST7735_DrawChar(81, 123, '5', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 79, 125, ST7735_YELLOW);
				break;
			case 27:
				ST7735_Line(63, 94, 79, 125, ST7735_BLACK);
				ST7735_DrawChar(81, 123, '5', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 75, 126, ST7735_YELLOW);
				break;
			case 28:
				ST7735_Line(63, 94, 75, 126, ST7735_BLACK);
				ST7735_Line(63, 94, 71, 126, ST7735_YELLOW);
				break;
			case 29:
				ST7735_Line(63, 94, 71, 126, ST7735_BLACK);
				ST7735_Line(63, 94, 67, 127, ST7735_YELLOW);
				break;
			case 30:
				ST7735_Line(63, 94, 67, 127, ST7735_BLACK);
				ST7735_DrawChar(58, 128, '6', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 63, 128, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 35){
		switch(m){
			case 31:
				ST7735_Line(63, 94, 63, 128, ST7735_BLACK);
				ST7735_DrawChar(58, 128, '6', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 59, 128, ST7735_YELLOW);
				break;
			case 32:
				ST7735_Line(63, 94, 59, 128, ST7735_BLACK);
				ST7735_DrawChar(58, 128, '6', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 55, 127, ST7735_YELLOW);
				break;
			case 33:
				ST7735_Line(63, 94, 55, 127, ST7735_BLACK);
				ST7735_Line(63, 94, 51, 127, ST7735_YELLOW);
				break;
			case 34:
				ST7735_Line(63, 94, 51, 127, ST7735_BLACK);
				ST7735_Line(63, 94, 47, 126, ST7735_YELLOW);
				break;
			case 35:
				ST7735_Line(63, 94, 47, 126, ST7735_BLACK);
				ST7735_DrawChar(41, 123, '7', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 43, 125, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 40){
		switch(m){
			case 36:
				ST7735_Line(63, 94, 43, 125, ST7735_BLACK);
				ST7735_DrawChar(41, 123, '7', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 41, 123, ST7735_YELLOW);
				break;
			case 37:
				ST7735_Line(63, 94, 41, 123, ST7735_BLACK);
				ST7735_DrawChar(41, 123, '7', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 38, 121, ST7735_YELLOW);
				break;
			case 38:
				ST7735_Line(63, 94, 38, 121, ST7735_BLACK);
				ST7735_Line(63, 94, 35, 118, ST7735_YELLOW);
				break;
			case 39:
				ST7735_Line(63, 94, 35, 118, ST7735_BLACK);
				ST7735_Line(63, 94, 33, 115, ST7735_YELLOW);
				break;
			case 40:
				ST7735_Line(63, 94, 33, 115, ST7735_BLACK);
				ST7735_DrawChar(28, 110, '8', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 96, 30, 112, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 45){
		switch(m){
			case 41:
				ST7735_Line(63, 96, 30, 112, ST7735_BLACK);
				ST7735_DrawChar(28, 110, '8', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 28, 109, ST7735_YELLOW);
				break;
			case 42:
				ST7735_Line(63, 94, 28, 109, ST7735_BLACK);
				ST7735_DrawChar(28, 110, '8', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 26, 106, ST7735_YELLOW);
				break;
			case 43:
				ST7735_Line(63, 94, 26, 106, ST7735_BLACK);
				ST7735_Line(63, 94, 23, 102, ST7735_YELLOW);
				break;
			case 44:
				ST7735_Line(63, 94, 23, 102, ST7735_BLACK);
				ST7735_Line(63, 94, 20, 98, ST7735_YELLOW);
				break;
			case 45:
				ST7735_Line(63, 94, 20, 98, ST7735_BLACK);
				ST7735_DrawChar(18, 89, '9', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 18, 94, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 50){
		switch(m){
			case 46:
				ST7735_Line(63, 94, 18, 94, ST7735_BLACK);
				ST7735_DrawChar(18, 89, '9', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 19, 90, ST7735_YELLOW);
				break;
			case 47:
				ST7735_Line(63, 94, 19, 90, ST7735_BLACK);
				ST7735_DrawChar(18, 89, '9', ST7735_WHITE, ST7735_BLACK, 2);
				ST7735_Line(63, 94, 20, 86, ST7735_YELLOW);
				break;
			case 48:
				ST7735_Line(63, 94, 20, 86, ST7735_BLACK);
				ST7735_Line(63, 94, 22, 82, ST7735_YELLOW);
				break;
			case 49:
				ST7735_Line(63, 94, 22, 82, ST7735_BLACK);
				ST7735_Line(63, 94, 23, 78, ST7735_YELLOW);
				break;
			case 50:
				ST7735_Line(63, 94, 23, 78, ST7735_BLACK);
				ST7735_DrawChar(23, 72, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(29, 72, '0', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 25, 74, ST7735_YELLOW);
				break;
		}
	}
	else if(m <= 55){
		switch(m){
			case 51:
				ST7735_Line(63, 94, 25, 74, ST7735_BLACK);
				ST7735_DrawChar(23, 72, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(29, 72, '0', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 27, 71, ST7735_YELLOW);
				break;
			case 52:
				ST7735_Line(63, 94, 27, 71, ST7735_BLACK);
				ST7735_DrawChar(23, 72, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(29, 72, '0', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 30, 69, ST7735_YELLOW);
				break;
			case 53:
				ST7735_Line(63, 94, 30, 69, ST7735_BLACK);
				ST7735_Line(63, 94, 32, 66, ST7735_YELLOW);
				break;
			case 54:
				ST7735_Line(63, 94, 32, 66, ST7735_BLACK);
				ST7735_Line(63, 94, 35, 63, ST7735_YELLOW);
				break;
			case 55:
				ST7735_Line(63, 94, 35, 63, ST7735_BLACK);
				ST7735_DrawChar(36, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(42, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 38, 61, ST7735_YELLOW);
				break;
		}
	}
	else if(m <60){
		switch(m){
			case 56:
				ST7735_Line(63, 94, 38, 61, ST7735_BLACK);
				ST7735_DrawChar(36, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(42, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 43, 59, ST7735_YELLOW);
				break;
			case 57:
				ST7735_Line(63, 94, 43, 59, ST7735_BLACK);
				ST7735_DrawChar(36, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_DrawChar(42, 59, '1', ST7735_WHITE, ST7735_BLACK, 1);
				ST7735_Line(63, 94, 48, 57, ST7735_YELLOW);
				break;
			case 58:
				ST7735_Line(63, 94, 48, 57, ST7735_BLACK);
				ST7735_Line(63, 94, 53, 55, ST7735_YELLOW);
				break;
			case 59:
				ST7735_Line(63, 94, 53, 55, ST7735_BLACK);
				ST7735_DrawChar(53, 50, '1', ST7735_WHITE, ST7735_BLACK, 2); // redraw 1 of 12
				ST7735_Line(63, 94, 58, 53, ST7735_YELLOW);
				break;
		}
	}
}

void AnalogDisplayHour(void){
	uint32_t h = GetHour();
	h = h % 12;
	uint32_t prev = h-1; // previous hour value
	if(prev == -1) { // current hour is 12
		prev = 11;
	}
	ST7735_Line(63, 94, analogDigits[prev].x, analogDigits[prev].y, ST7735_BLACK); // erase old hour line
	ST7735_Line(63, 94, analogDigits[h].x, analogDigits[h].y, ST7735_YELLOW);
}

//	//Grid code for positioning numbers
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



