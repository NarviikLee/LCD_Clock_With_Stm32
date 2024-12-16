/*
 * timer_funs.c
 *
 *  Created on: Aug 9, 2024
 *      Author: ihg78
 */

#include "timer_funs.h"
#include "timer_mode.h"
#include "RTC_Functions.h"
#include "g_var.h"
#include "esp32_dht11.h"

static time_t sec_con;
static struct tm current_time;

void init_timer_funs(){
	get_RTC_Time_t();
	convert_tm();
	update_clock_value();
	set_send_cnt(current_time.tm_hour);
	set_RTC_Time_t();
}
void update_clock_value(){
	clock_value[2] = current_time.tm_hour;
	clock_value[1] = current_time.tm_min;
	//  여기서 온도데이터 업데이트를 진행핼까?
	if(clock_value[1] == 0){
		check_send();
	}
}

void set_tm_strut(int year,int month, int mday, int hour, int minute){
	current_time.tm_year= year+100;
	current_time.tm_mon = month;
	current_time.tm_mday = mday;
	current_time.tm_hour = hour;
	current_time.tm_min = minute;
	set_send_cnt(hour);
	convert_time_t();
}

void get_RTC_Time_t(){
	sec_con = RestoreTimeFromRTC();
}

void set_RTC_Time_t(){
	BackupTimeToRTC(sec_con);
}

void convert_time_t(){
	sec_con = mktime(&current_time);
}

void convert_tm(){
	current_time = *localtime(&sec_con);
}

void set_struct_tm(struct tm * calender){
	current_time = *calender;
}
struct tm get_struct_tm(){
	return current_time;
}

void set_time_t(){
	sec_con += minute_cnt;
	convert_tm();
	update_clock_value();
	set_RTC_Time_t();
}

time_t get_time_t(){
	return sec_con;
}

