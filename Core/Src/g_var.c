/*
 * g_var.c
 *
 *  Created on: Jul 12, 2024
 *      Author: ihg78
 */


#include "g_var.h"

// using button that interrupts
uint8_t cancel_btn = 0;
uint8_t up_btn = 0;
uint8_t down_btn = 0;
uint8_t select_btn = 0;


int calender_value[3] = {2024,11,15};
// index 0 = second, index 1 = minute, index 2 = hour
// Normal_Clock Value
int clock_value[3] = {0,25,20};
// Timer Value
int timer_value[3] = {0,0,0};
// Alarm Time Value
int alarm_value[3] = {0,0,0};
int default_second = 0;
int Timer_Second = 0;
 // interrupt count(second) and this integer be used update Clock
uint8_t alert_mode = 0;

time_t rawtime = 0;

 // mode 0 is normal_Clock, 1 = Timer Mode, 2 = config Clock
