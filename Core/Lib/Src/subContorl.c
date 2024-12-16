/*
 * subContorl.c
 *
 *  Created on: 2024. 7. 21.
 *      Author: ihg78
 */

#include <stdbool.h>
#include "subControl.h"
#include "Potentiometer.h"
#include "lcd_menu.h"
#include "timer_mode.h"
#include "timer_funs.h"
#include "RTC_Functions.h"
// t_Process_case 0 is minute, 1 is second, 2 is timer_value_update and Calculate second
static int t_Process_case = 0;
// a_Process_case 0 is check the alarm(if alarm State is On, Start the from step 0 ), 1 = second step .... n= n+1 Step
static int a_Process_case = 0;
// m_Process case is Modify the Clock's Hour and Minute Process_number, 0 is hour Modify, 1 is Minute Modify,
// i think Add a mode, year,month,day Modify Modes
static int m_Process_case = 0;


bool handleButtonPress(int *process_case, int increment) {
    if (select_btn) {
        select_btn = 0;  // 0은 false
        if(*process_case >99){
			*process_case = 0;
		}else{
			*process_case += increment;
		}
        return true;  // 1은 true
    }else if (cancel_btn){
    	cancel_btn = 0;
    	if(*process_case >99){
    		setMode(0);
    	}else{
    		*process_case -= increment;
    	}
    	if(*process_case < 0){
    		*process_case=0;
    		setMode(0);
    	}
    	return false;  // 0은 false
    }
}

void processTimerMinute() {
    set_Minute();
    if (handleButtonPress( &t_Process_case, 1)== true) {
        timer_value[1] = getnMinute();
    }
}

void processTimerSecond() {
    set_Second();
    if (handleButtonPress(&t_Process_case, 1) == true) {
        timer_value[0] = getnSecond();
    }
}

void processTimerReview() {
    check_timer_lcd();
    if (handleButtonPress(&t_Process_case, 1)== true) {
        cal_Second();
        t_Process_case = 0;
        setTimerState(1);
        setnMinute(0);
        setnSecond(0);
        setMode(-1);
    }
}


void processAlarmChangeCheck() {
	check_alarm_change_lcd();
    if (handleButtonPress(&a_Process_case, 1)== true) {
        setAlarmState(0);
        toggleScreen();
    }
}

void processAlarmHour(int *input_Process_case) {
    set_Hour();
    if (handleButtonPress(input_Process_case, 1) == true) {
    	int mode = getMode();
    	if(mode==2){
    		alarm_value[2] = getnHour();
    	}else if(mode==3){
    		clock_value[2] = getnHour();
    	}
    }
}

void processAlarmMinute(int *input_Process_case){
    set_Minute();
    if (handleButtonPress(input_Process_case, 1) == true) {
    	int mode = getMode();
    	if(mode == 2){
    		alarm_value[1] = getnMinute();
    	}else if(mode ==3){
    		clock_value[1] = getnMinute();
    	}
    }
}

void processAlarmReview() {
    check_alarm_lcd();
    handleButtonPress( &a_Process_case, 1);
}

void processAlarmFinalization() {
	setAlarmState(1);
	int aHour = getnHour();
	int aMin = getnMinute();
	set_Alarm(aHour,aMin);
    setnHour(0);
    setnMinute(0);
    n_alarm_show();
    setMode(-1);
    a_Process_case = 0;
}

void processModifyCalender(int *input_Process_case){
	set_Calender(*input_Process_case);
	handleButtonPress(input_Process_case, 1);
}
void processModifyCheck(int *input_Process_case){
	check_modify_lcd();
	handleButtonPress(input_Process_case, 1);
}

void processModifyFinalization(){
	set_tm_strut(getnYear(),getnMonth(),getnDay()+1,clock_value[2],clock_value[1]);
	set_RTC_Time_t();
	default_second = 0;
	setMode(-1);
	m_Process_case = 0;
}

void timer_Process() {
    switch (t_Process_case) {
        case 0:
            processTimerMinute();
            break;
        case 1:
            processTimerSecond();
            break;
        case 2:
            processTimerReview();
            break;
    }
}

void alarm_Process() {
    if (getAlarmState()) {
        a_Process_case = 100;
    }
    switch (a_Process_case) {
        case 0:
            processAlarmHour(&a_Process_case);
            break;
        case 1:
            processAlarmMinute(&a_Process_case);
            break;
        case 2:
            processAlarmReview();
            break;
        case 3:
            processAlarmFinalization();
            break;
        case 100: // if You Set a Alarm before, Process_Value bigger than All Phase
			processAlarmChangeCheck();
			break;
    }
}
void modify_Process(){
	switch(m_Process_case){
	case 0 :
		processModifyCalender(&m_Process_case);
		break;
	case 1:
		processModifyCalender(&m_Process_case);
		break;
	case 2:
		// show the Check the OLED
		processModifyCalender(&m_Process_case);
		break;
	case 3:
		processAlarmHour(&m_Process_case);
		break;
	case 4:
		processAlarmMinute(&m_Process_case);
		break;
	case 5:
		processModifyCheck(&m_Process_case);
		break;
	case 6:
		processModifyFinalization();
		break;
	}
}
