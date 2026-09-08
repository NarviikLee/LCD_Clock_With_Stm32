/*
 * timer_mode.c
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */


#include "timer_mode.h"
#include "lcd_menu.h"

//디바이스 모드 저장 변수(-1: 시간 디스플레이, 0: 메뉴 선택, 1: 타이머 설정, 2: 알람 설정, 3: 디바이스 시간 및 날짜 변경)
static int D_mode = -1;

// 선택 커서 위치 변수
static int sel_po = 0;

// 시간 변경 관련 변수
static int n_hour = 0;
static int n_minute = 0;
static int n_second = 0;

// 날짜 관련 변수
static int n_year = 0;
static int n_month = 0;
static int n_day = 1;

// 타이머 및 알람 기능 관련 변수
static int timer_on = 0;
static int com_timer = 0;
static int com_alarm = 0;
static int alarm_On = 0;

// Mode_Process_variable


// 디바이스 모드 업데이트 및 반환 함수
int getMode(){
	 return D_mode;
}
void setMode(int setMode){
	D_mode = setMode;
}

// 타이머 ON_OFF 상태 업데이트 및 반환 함수
int getTimerState(){
	 return timer_on;
}
void setTimerState(int timer){
	timer_on = timer;
}
// 알람이 설정 확인 및 업데이트 함수
int getAlarmState(){
	return alarm_On;
}
void setAlarmState(int State){
	alarm_On = State;
}

// 타이머 종료(반환) 및 시작(업데이트) 함수
int getTimerCompleted(){
	return com_timer;
}
void setTimerCompleted(int completed){
	com_timer = completed;
}
// 알람 상태 변수 업데이트 및 반환 함수
int getAlarmCompleted(){
	return com_alarm;
}
void setAlarmCompleted(int completed){
	com_alarm = completed;
}

// 알람 및 타이머 확인 업데이트 함수
void setCompleted(int mode){
	if(mode == 1){
		setTimerState(0);
		setTimerCompleted(0);
	}else{
		setAlarmCompleted(0);
	}
}


// 디바이스 및 추가 기능 시간 단위 업데이트 및 반환 함수
int getnHour(){
	return n_hour;
}

void setnHour(int hour){
	if(hour == 24){
		hour = 0;
	}
	n_hour = hour;
}
// 디바이스 및 추가 기능 분 단위 업데이트 및 반환 함수
int getnMinute(){
	return n_minute;
}
void setnMinute(int minute){
	n_minute = minute;
}
// 디바이스 및 추가 기능 초 단위 업데이트 및 반환 함수
int getnSecond(){
	return n_second;
}
void setnSecond(int second){
	n_second = second;
}

// 연도 단위 업데이트 및 반환 함수
int getnYear(){
	return n_year;
}

void setnYear(int s_year){
	n_year = s_year;
}

// 월 단위 업데이트 및 반환 함수
int getnMonth(){
	return n_month;
}
void setnMonth(int s_month){
	n_month = s_month;
}

//요일 업데이트 및 반환 함수
int getnDay(){
	return n_day;
}
void setnDay(int s_day){
	n_day = s_day;
}
// 선택 커서 현재 위치 반환 함수
int getPos(){
	return sel_po;
}
// 선택 커서 위치 업데이트 함수
void setPos(int Pos){
	if(Pos >2){
		Pos = 2;
	}
	else if (Pos <0){
		Pos = 0;
	}
	sel_po = Pos;
}
