/*
 * timer_mode.h
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */

#ifndef LIB_INC_TIMER_MODE_H_
#define LIB_INC_TIMER_MODE_H_

#include "main.h"
#include "g_var.h"


// Timer Setting Check Function
int getTimerState();
void setTimerState(int timer);

// Clock Mode Functions
int getMode();
void setMode(int setMode);

int getPos();
void setPos(int Pos);

// Calender Value Functions
int getnYear();
void setnYear(int s_year);

int getnMonth();
void setnMonth(int s_month);

int getnDay();
void setnDay(int s_day);


int getnHour();
void setnHour(int hour);

int getnMinute();
void setnMinute(int minute);

int getnSecond();
void setnSecond(int second);



// Timer and alarm State set&get Functions
int getTimerCompleted();
void setTimerCompleted(int completed);

// Functions about Timer Complete
int getAlarmCompleted();
void setAlarmCompleted(int completed);

void setCompleted(int mode);

int getAlarmState();
void setAlarmState(int State);

#endif /* LIB_INC_TIMER_MODE_H_ */
