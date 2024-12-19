/*
 * timer_mode.c
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */


#include "timer_mode.h"
#include "lcd_menu.h"

// -1 = show_Clock,   0= Menu_select
// if btn_state interrupt gMode set 1,
static int D_mode = -1;
// D_mode 1 is Timer_mode, 2 is Alarm Config Mode, 3 is Clock Modify Mode

// if Sel_Position_Variable
static int sel_po = 0;

// n_minute and n_second
// set time_variable
static int n_hour = 0;
static int n_minute = 0;
static int n_second = 0;

// calender variables
static int n_year = 0;
static int n_month = 0;
static int n_day = 1;

// mode_variable
static int timer_on = 0;
static int com_timer = 0;
static int com_alarm = 0;
static int alarm_On = 0;

// Mode_Process_variable


// functions about Sub menu or select_menu and main_menu Mode
int getMode(){
	 return D_mode;
}
void setMode(int setMode){
	D_mode = setMode;
}

// Functions About Timer_mode
int getTimerState(){
	 return timer_on;
}
void setTimerState(int timer){
	timer_on = timer;
}
// Check to set a Alarm Mode
int getAlarmState(){
	return alarm_On;
}
void setAlarmState(int State){
	alarm_On = State;
}

// Functions about Timer Complete
int getTimerCompleted(){
	return com_timer;
}
void setTimerCompleted(int completed){
	com_timer = completed;
}
// Functions About Alarm Complete
int getAlarmCompleted(){
	return com_alarm;
}
void setAlarmCompleted(int completed){
	com_alarm = completed;
}

void setCompleted(int mode){
	if(mode == 1){
		setTimerState(0);
		setTimerCompleted(0);
	}else{
		setAlarmCompleted(0);
	}
}

// Timer or Alarm set a Time
int getnHour(){
	return n_hour;
}

void setnHour(int hour){
	if(hour == 24){
		hour = 0;
	}
	n_hour = hour;
}

int getnMinute(){
	return n_minute;
}
void setnMinute(int minute){
	n_minute = minute;
}

int getnSecond(){
	return n_second;
}
void setnSecond(int second){
	n_second = second;
}

int getnYear(){
	return n_year;
}

void setnYear(int s_year){
	n_year = s_year;
}

int getnMonth(){
	return n_month;
}
void setnMonth(int s_month){
	n_month = s_month;
}
int getnDay(){
	return n_day;
}
void setnDay(int s_day){
	n_day = s_day;
}
// select_menu_Position Functions
int getPos(){
	return sel_po;
}
void setPos(int Pos){
	if(Pos >2){
		Pos = 2;
	}
	else if (Pos <0){
		Pos = 0;
	}
	sel_po = Pos;
}
