// filename ******** main.h ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/ST7735_4C123/ST7735.c"
#include "../Lab1/fixed.c"
#include "PLL.h"
#include <stdbool.h>
#include <stdint.h>
#include "Timer.h"
#include "Switch.h"
#include "LCD.h"
#include "Speaker.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int main(void){
	PLL_Init(Bus80MHz);                   // 80 MHz
	Output_Init();
	Timer0A_Init1HzInt();
	Timer1A_Init100HzInt();
	PortF_Init();
	ST7735_InitR(INITR_REDTAB);
	PortE_Init();
	EnableInterrupts();
//	int16_t yellow = ST7735_Color565(0xf4, 0xff, 0x87);
//	int16_t salmon = ST7735_Color565(0xFF, 0x87, 0x8F);
//	int16_t pink = ST7735_Color565(0xFF, 0x87, 0xDC);
//	int16_t purpleBlue = ST7735_Color565(0x87, 0x87, 0xFF);
//	int16_t cyan = ST7735_Color565(0x87, 0xFF, 0xFF);
//	ST7735_DrawChar(38, 0, ':', yellow, 0, 5);
//	ST7735_DrawChar(18, 0, '1', yellow, 0, 5);
//	ST7735_DrawChar(53, 0, '1', yellow, 0, 5);
//	ST7735_DrawChar(81, 0, '1', yellow, 0, 5);
	initDigitalTimerDisplay();
	//ST7735_FillRect(27, 0, 93, 5, yellow);
	while(1){}
}
