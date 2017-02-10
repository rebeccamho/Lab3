// filename ******** LCD.h ************** 
// Lab 1 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>

typedef enum  { Select,
								Up,
								Down,
								None} SwitchStates;	

//----------DisplayMainMenu-----------
//Displays main menu with clock setting options
//Input: n, the index in main menu array of options that should be highlighted
//red
//Output: none
void DisplayMainMenu(int16_t);

//----------CheckSwitches-----------
//Checks if any switches have been pressed and calls appropriate functions
//if one has been pressed
//Input: none
//Output: none
void CheckSwitches(void);

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
