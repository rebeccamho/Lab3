// filename ******** LCD.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

typedef enum  { Select,
								Up,
								Down,
								None,
								SetInit,
								AlarmInit} SwitchStates;	

typedef enum  { MainMenu,
								Digital,
								Analog,
								SetTime,
								SetAlarm} LCDstate;										

//----------DisplayMainMenu-----------
//Displays main menu with clock setting options
//Input: n, the index in main menu array of options that should be highlighted
//red
//Output: none
void DisplayMainMenu(int16_t);

//----------CheckFlags-----------
//Checks if any switches have been pressed and calls appropriate functions
//if one has been pressed
//Input: none
//Output: none
void CheckFlags(void);

//----------SelectFunction-----------
//Calls appropriate function depending on current LCD state
//Input: none
//Output: none
void SelectFunction(void);

//----------DownFunction-----------
//Calls appropriate function depending on current LCD state
//Input: none
//Output: none
void DownFunction(void);

//----------UpFunction-----------
//Calls appropriate function depending on current LCD state
//Input: none
//Output: none
void UpFunction(void);

//----------SelectPressed-----------
//Sets flag that select (PF4) switch has been pressed
//Input: none
//Output: none
void SelectPressed(void);

//----------DownPressed-----------
//Sets flag that down (PE5) switch has been pressed
//Input: none
//Output: none
void DownPressed(void);

//----------UpPressed-----------
//Sets flag that up (PE4) switch has been pressed
//Input: none
//Output: none
void UpPressed(void);

//----------ResetSwitches-----------
//Clears all switch flags
//Input: none
//Output: none
void ResetSwitches(void);

//----------GetCurrentState-----------
//Returns current state of LCD
//Input: none
//Output: state of LCD
LCDstate GetCurrentState(void);

//----------UpdateMinute-----------
//Sets flag to update minute
//Input: none
//Output: none
void UpdateMinute(void);

//----------UpdateHour-----------
//Sets flag to update hour
//Input: none
//Output: none
void UpdateHour(void);

//----------IncreaseIdleCount-----------
//Increase count of seconds user has been idle
//Input: none
//Output: none
void IncreaseIdleCount(void);

#endif

