// filename ******** Timer.h ************** 
// Lab 3 Spring 2017
// Matt Owens & Rebecca Ho
// 2/8/17

#include <stdint.h>
#include <stdbool.h>

//------------Timer0A_Init1HzInt------------
// Initializing of Timer with 1 Hz interrupts
// Input: none
// Output: none
void Timer0A_Init1HzInt(void);

//------------Timer0A_Handler------------
// Handler for Timer0A interrupts
// Input: none
// Output: none
void Timer0A_Handler(void);

//------------GetHour----------------------
// Returns the current hour of the timer
// Input: none
// Output: The current hour of the timer
uint32_t GetHour(void);

//------------GetHour----------------------
// Returns the current minute of the timer
// Input: none
// Output: The current minute of the timer
uint32_t GetMinute(void);

//------------SetHour----------------------
// Set the current hour value
// Input: hour value to set
// Output: none
void SetHour(uint32_t);

//------------SetMinute----------------------
// Set the current minute value
// Input: minute value to set
// Output: none
void SetMinute(uint32_t);

//------------SetSecond----------------------
// Set the current second value
// Input: second value to set
// Output: none
void SetSecond(uint32_t);

//------------CheckAlarms----------------------
// Check if any alarm has been set for this time
// Input: none
// Output: none
void CheckAlarms(void);

//------------AddAlarm----------------------
// Add alarm to list of alarms
// Input: hour, minute, and AM/PM of alarm
// Output: none
void AddAlarm(uint16_t, uint16_t, bool);

//------------GetAlarmOn----------------------
// Returns if an alarm should be on
// Input: none
// Output: true is alarm is on, false otherwise
bool GetAlarmOn(void);

//------------TurnAlarmOff----------------------
// Sets alarmOn to false
// Input: none
// Output: none
void TurnAlarmOff(void);
